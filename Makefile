DIR_GUI = demo_app
DIR_APP = driver
prefix =

all:
	$(MAKE) -C $(DIR_APP) all
	$(MAKE) -C $(DIR_GUI) all


install:
	$(MAKE) prefix=$(prefix) -C $(DIR_APP) install
	$(MAKE) prefix=$(prefix) -C $(DIR_GUI) install

uninstall:
	$(MAKE) prefix=$(prefix) -C $(DIR_APP) uninstall
	$(MAKE) prefix=$(prefix) -C $(DIR_GUI) uninstall

PKGDIR = ./package

clean:
	$(MAKE) -C $(DIR_APP) clean
	$(MAKE) -C $(DIR_GUI) clean
	rm -rf $(PKGDIR) *.tar.[gx]z

PKGVER = 0.11
PKGNAME = alphacool-$(PKGVER)

package: $(wildcard *.tar.xz)
	rm -rf *.tar.[gx]z $(PKGDIR)
	mkdir $(PKGDIR)
	tar -zcvf $(PKGNAME).tar.gz demo_app driver Makefile
	cp PKGBUILD $(PKGDIR)/
	makepkg -g >>$(PKGDIR)/PKGBUILD
	makepkg -p $(PKGDIR)/PKGBUILD
	rm -rf $(PKGDIR) *.tar.gz


