pkgname=dwm
pkgver=6.2
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="https://github.com/glandogear/dwm"
arch=('x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft' 'freetype2' 'st' 'dmenu')
source=(
    http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz
    https://dwm.suckless.org/patches/fullgaps/dwm-fullgaps-6.2.diff
    https://raw.githubusercontent.com/ashish-yadav11/dwmblocks/master/patches/dwm-dwmblocks-6.2.diff
)
sha256sums=(
    'SKIP'
    'SKIP'
    'SKIP'
)

prepare() {
    patch --directory="$pkgname-$pkgver" < dwm-fullgaps-6.2.diff
    patch --directory="$pkgname-$pkgver" < dwm-dwmblocks-6.2.diff

    if [ -e $BUILDDIR/config.h ]; then
        cp "$BUILDDIR/config.h" "$pkgname-$pkgver"
    elif [ ! -e $BUILDDIR/config.def.h ]; then
        msg='This package can be configured in config.h. Copy the config.def.h '
        msg+='that was just placed into the package directory to config.h and '
        msg+='modify it to change the configuration. Or just leave it alone to '
        msg+='continue to use default values.'
        warning "$msg"
        cp "$pkgname-$pkgver/config.def.h" "$BUILDDIR"
    fi
}

build() {
  cd "$srcdir/$pkgname-$pkgver"
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
  cd "$srcdir/$pkgname-$pkgver"
  make PREFIX=/usr DESTDIR="$pkgdir" install
  install -m644 -D LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
  install -m644 -D README "$pkgdir/usr/share/doc/$pkgname/README"
}
