#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "alphacool/lcd_application.hpp"
#include "alphacool/lcd_string.hpp"
#include <QTimer>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    LcdApp::LcdApplication application;
    QTimer *timer;

    void initialize_components();
    void send_text(const QString &str, const Lcd::Point &begin, size_t font_height, Lcd::LcdFontType font_type);
    void send_text(const QString &str);
    void send_time_command();

    void send_textedit_text();

private slots:
    void display_current_time();
    void on_textEdit_textChanged();
    void on_spinBoxFontHeight_valueChanged(int arg1);
};

#endif // MAINWINDOW_H
