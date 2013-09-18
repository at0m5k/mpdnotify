# Maintainer: at0m5k <at0m5k@outlook.com>

pkgname=mpdnotify-git
_gitname=mpdnotify
pkgver=2013.07.31
pkgrel=1
pkgdesc="MPD song notifications"
arch=('any')
license=('GPL3')
groups=('custom')
depends=('libnotify' 'libmpdclient')
makedepends=('git')
source=('git://github.com/at0m5k/mpdnotify.git')
md5sums=('SKIP')

pkgver() {
    cd $_gitname
    git log -1 --format="%cd" --date=short | sed 's|-|.|g'
}

build() {
    cd $_gitname
    make
}

package() {
    cd $_gitname
    make PREFIX=/usr DESTDIR="$pkgdir" install
}
