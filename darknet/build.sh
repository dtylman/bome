#!/bin/sh

make EXEC=../bin/darknet -j 4
make EXEC=../bin/darknet.exe CC=i686-w64-mingw32-gcc -j 4

