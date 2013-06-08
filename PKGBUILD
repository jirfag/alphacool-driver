pkgname=alphacool
pkgver=0.11
pkgrel=2
pkgdesc="Driver for Alphacool LCD display and demo util"
arch=('x86_64' 'i686')
license=('GPLv3')
depends=()
optdepends=()
makedepends=()
conflicts=()
replaces=()
backup=()
install=alphacool.install
source=("./${pkgname}-${pkgver}.tar.gz")
 
build() {
  make
}
 
package() {
  make prefix="${pkgdir}" install
}

