#!/bin/bash

CFLAGS="-Wall -Wextra"

if [[ "$OS" == "Windows_NT" ]]; then
    LFLAGS="-lraylib -lgdi32 -lwinmm"
else
    UNAME_S=$(uname -s)
    if [[ "$UNAME_S" == "Linux" ]]; then
        LFLAGS="-I./raylib/raylib-5.0_linux_amd64/include/"
        LFLAGS+=" -L./raylib/raylib-5.0_linux_amd64/lib -l:libraylib.a -lm"
    else
        echo "Unsupported OS; Supported OS (Windows, GNU/Linux)"
        exit 1
    fi
fi

FILENAME="demo_xml"

if [ $# -eq 1 ]; then
  FILENAME=$1
fi

gcc $FILENAME.c -o $FILENAME $CFLAGS $LFLAGS

if [[ $? -eq 0 ]]; then
    ./$FILENAME
    rm -f $FILENAME $FILENAME.exe
else
    echo "Compilation failed"
    exit 1
fi
