PROG_BIN = alphacool_demo
QMAKEFILE = qMakefile
all: $(PROG_BIN)

$(PROG_BIN):
	qmake -Wall -o $(QMAKEFILE) AlphacoolGui.pro
	make -f $(QMAKEFILE)

prefix         =
prefix_local   = $(prefix)/usr
BIN_INSTDIR    = $(prefix_local)/bin
INSTMODE       = 755
INSTOWNER      = root
INSTGROUP      = root
PROG_BIN_PATH  = $(BIN_INSTDIR)/$(PROG_BIN)

install: $(PROG_BIN)
	install -d $(BIN_INSTDIR)
	install -m $(INSTMODE) -o $(INSTOWNER) -g $(INSTGROUP) $(PROG_BIN) $(BIN_INSTDIR)

uninstall: $(PROG_BIN_PATH)
	rm -f $^

clean:
	make -f $(QMAKEFILE) clean
	rm -f $(QMAKEFILE) $(PROG_BIN)
