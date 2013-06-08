Alphacool LCD driver
=========

This is a kernel-space driver for Alphacool LCD device for GNU/Linux. Driver supports only 200x64 resolution.
Software includes the kernel-space driver and demo application, allowing to print any text on the screen and show current time.
Driver is tested on 3.8 kernel. Also there is a package for Arch Linux, i am planning to add it to AUR soon.

Screenshots:

![Demo application](/readme-content/alphacool_demo.png)

![Demo application](/readme-content/device.png)

Installation
-------

To install do
```bash
make && sudo make install
```

To uninstall do
```bash
sudo make uninstall
```

To make Arch package do
```bash
make package
```
