#!/bin/sh
./configure \
--prefix=/mnt/jeston/opt/qt5.9.1 \
-opensource -release -shared \
-Declarative \
-no-sse2 \
-sysroot /mnt/jeston \
-qt-zlib  -qt-libpng \
-qt-libjpeg -make libs -make tools -nomake examples \
-no-cups \
-xplatform linux-aarch64-gnu-g++  \
-qt-freetype \
-feature-library \
-v \
-qt-xcb 