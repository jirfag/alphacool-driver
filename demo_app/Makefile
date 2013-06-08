DIR_GUI = gui
DIR_APP = app
prefix  =

all:
	$(MAKE) -C $(DIR_APP) all
	$(MAKE) -C $(DIR_GUI) all


install:
	$(MAKE) prefix=$(prefix) -C $(DIR_APP) install
	$(MAKE) prefix=$(prefix) -C $(DIR_GUI) install

uninstall:
	$(MAKE) prefix=$(prefix) -C $(DIR_APP) uninstall
	$(MAKE) prefix=$(prefix) -C $(DIR_GUI) uninstall

clean:
	$(MAKE) -C $(DIR_APP) clean
	$(MAKE) -C $(DIR_GUI) clean
