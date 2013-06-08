#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "alphacool/simple_data_provider.hpp"
#include "alphacool/lcd_command.hpp"
#include "alphacool/std_data_visualizer.hpp"
#include "alphacool/current_time_data_provider.hpp"
#include <QDateTime>
#include <QMessageBox>
#include <unistd.h>
#include <algorithm>
#include <time.h>
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (getuid()) {
        QMessageBox msg_box;
        msg_box.setText("You must start program as root!");
        msg_box.exec();
        exit(EXIT_FAILURE);
    }

    initialize_components();
}

void MainWindow::initialize_components()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(display_current_time()));
    display_current_time();
    ui->tabWidget->setCurrentIndex(0);
}

static const QString get_limited_string(const QString &str, int font_height)
{
    static std::vector<size_t> max_chars_at_line = { 40, 20, 14, 10, 8, 6, 5, 5 };
    static std::vector<size_t> max_lines         = {  8,  4,  2,  2, 1, 1, 1, 1 };
    const size_t max_font_lines = max_lines[font_height];
    const size_t max_line_size = max_chars_at_line[font_height];
    auto lines = str.split('\n');
    const int permitted_lines_count = std::min(static_cast<size_t>(lines.size()), max_font_lines);
    QString res = "";

    for (int i = 0; i < permitted_lines_count; ++i)
        res += lines[i].left(max_line_size) + (i == permitted_lines_count - 1 ? "" : "\n");

    return res;
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::send_text(const QString &str, const Lcd::Point &begin, size_t font_height, Lcd::LcdFontType font_type)
{
    std::shared_ptr<LcdApp::DataProvider> provider(new LcdApp::SimpleDataProvider(str.toStdString()));
    std::shared_ptr<LcdApp::DataVisualizer> visualizer(new LcdApp::StdDataVisualizer(begin, font_height, font_type));
    auto simple_command = application.construct_command(provider, visualizer, std::chrono::milliseconds::zero());
    application.push_command(simple_command);
}

void MainWindow::send_text(const QString &str)
{
    std::shared_ptr<LcdApp::DataProvider> provider(new LcdApp::SimpleDataProvider(str.toStdString()));
    std::shared_ptr<LcdApp::DataVisualizer> visualizer(new LcdApp::StdDataVisualizer());
    auto simple_command = application.construct_command(provider, visualizer, std::chrono::milliseconds::zero());
    application.push_command(simple_command);
}

void MainWindow::send_time_command()
{
    std::shared_ptr<LcdApp::DataProvider> provider(new LcdApp::CurrentTimeDataProvider());
    std::shared_ptr<LcdApp::DataVisualizer> visualizer(new LcdApp::StdDataVisualizer());
    auto time_command = application.construct_command(provider, visualizer, std::chrono::milliseconds(1000));
    application.push_command(time_command);
}

void MainWindow::display_current_time()
{
	char time_buf[128];
	time_t now;
	time(&now);
	strftime(time_buf, sizeof(time_buf), "%H:%M:%S", gmtime(&now));
    ui->lcdNumber->display(QString(time_buf));
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 1) { // time tab
        display_current_time();
        timer->start(1000);
        send_time_command();
    } else {
        timer->stop();
        send_textedit_text();
    }
}

void MainWindow::on_textEdit_textChanged()
{
    static bool text_changed_programmly = false;
    if (text_changed_programmly)
        return;

    const size_t current_font_height = ui->spinBoxFontHeight->value() - 1;
    const QString limited_string = get_limited_string(ui->textEdit->toPlainText(), current_font_height);
    text_changed_programmly = true;
    ui->textEdit->setText(limited_string);
    text_changed_programmly = false;
    auto cursor = ui->textEdit->textCursor();
    cursor.setPosition(limited_string.size());
    ui->textEdit->setTextCursor(cursor);
    send_textedit_text();
}

void MainWindow::send_textedit_text()
{
    send_text(ui->textEdit->toPlainText(), Lcd::Point(0, 0), ui->spinBoxFontHeight->value(), Lcd::LFT_NORMAL);
}


void MainWindow::on_spinBoxFontHeight_valueChanged(int)
{
    on_textEdit_textChanged();
    send_textedit_text();
}
