Read Me File
Qt compile steps
1. Add source

2. Use the export path command: export PATH=/ad/eng/courses/ec/ec535/gumstix/oe/cross/bin:$PATH

3. qmake -project

4. qmake

5. Change the INCPATH in Makefile into
INCPATH = -I/ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/include/c++ \
              -I/ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/include/c++/arm-angstrom-linux-gnueabi \
              -I/ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/include/c++/backward \
              -I/ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/include/c++/bits \
              -I/ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/include/c++/debug \
              -I/ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/include/c++/ext \
              -I/ad/eng/courses/ec/ec535/gumstix/oe/qt/include/QtCore \
              -I/ad/eng/courses/ec/ec535/gumstix/oe/qt/include/QtGui \
              -I/ad/eng/courses/ec/ec535/gumstix/oe/qt/include/QtNetwork \
              -I/ad/eng/courses/ec/ec535/gumstix/oe/qt/include \
              -I/ad/eng/courses/ec/ec535/gumstix/oe/qt/mkspecs/qws/linux-arm-g++ -I. -I. -I. -I.

6. Open command code, find the correct file directory and use make command

7. Turn on minicom 
create library links in gumstix:
	cd /usr/lib
	ln -s /media/card/lib/libQtCore.so.4 libQtCore.so.4
	ln -s /media/card/lib/libQtGui.so.4 libQtGui.so.4
	ln -s /media/card/lib/libQtNetwork.so.4 libQtNetwork.so.4
	ln -s /media/card/lib/ld-uClibc.so.0 ld-uClibc.so.0
	ln -s /media/card/lib/libc.so.0 libc.so.0
	ln -s /media/card/lib/libm.so.0 libm.so.0
	ln -s /media/card/lib/libstdc\+\+.so.6 libstdc\+\+.so.6

8. Export under home/root directory
export some variables in gumstix:
	export QWS_MOUSE_PROTO='tslib:/dev/input/touchscreen0'
	export TSLIB_CONFFILE=/etc/ts.conf
	export TSLIB_PLUGINDIR=/usr/lib
	export TSLIB_TSDEVICE=/dev/input/event0
	export TSLIB_FBDEVICE=/dev/fb0
	export TSLIB_CONSOLEDEVICE=/dev/tty
	export QT_QWS_FONTDIR=/media/card/lib/fonts
	export TSLIB_PLUGINDIR=/usr/lib/ts

9. Upload Qt file in to gumstix under root directory

10. Run Qt file by using ./filename -qws
