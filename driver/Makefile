TARGET = alphacool
alphacool-objs := alphacool_main.o alphacool_fops.o alphacool_device.o alphacool_cmd.o alphacool_probe.o
prefix =
BUILD_DIR = $(prefix)/lib/modules/$(shell uname -r)/build
INSTALL_DIR = $(prefix)/lib/modules/$(shell uname -r)
PWD := $(shell pwd)

obj-m += $(TARGET).o

all:
	make -C $(BUILD_DIR) M=$(PWD) modules

INSTMODE         = 755
INSTOWNER        = root
INSTGROUP        = root
MODULE_NAME      = $(TARGET).ko
MODULE_CONF_DIR  = $(prefix)/etc/modules-load.d
MODULE_CONF_NAME = $(MODULE_CONF_DIR)/$(TARGET).conf

ifeq ($(prefix),)
	DEPMOD_COMMAND   = depmod
	MODPROBE_COMMAND = modprobe $(TARGET)
else
	DEPMOD_COMMAND   =
	MODPROBE_COMMAND =
endif

install:
	install -d $(INSTALL_DIR)
	install -m $(INSTMODE) -o $(INSTOWNER) -g $(INSTGROUP) $(MODULE_NAME) $(INSTALL_DIR)
	$(DEPMOD_COMMAND)
	$(MODPROBE_COMMAND)
	install -d $(MODULE_CONF_DIR)
	echo $(TARGET) >$(MODULE_CONF_NAME)

MODULE_PATH = $(INSTALL_DIR)/$(MODULE_NAME)

uninstall:
	modprobe -r $(TARGET)
	rm -f $(MODULE_PATH) $(MODULE_CONF_NAME)

clean:
	make -C $(BUILD_DIR) M=$(PWD) clean
	rm -f *.ko *.o
