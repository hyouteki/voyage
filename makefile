default: build 

CFLAGS = -Wall -Wextra

ifeq ($(OS),Windows_NT)
	LIBS = -lraylib -lgdi32 -lwinmm
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LIBS = -I./raylib/raylib-5.0_linux_amd64/include/ -L./raylib/raylib-5.0_linux_amd64/lib -l:libraylib.a -lm

    else
        $(error "Unsupported OS; Supported OS (Windows, GNU/Linux)")
    endif
endif

build: demo.c clean
	gcc demo.c -o demo $(CFLAGS) $(LIBS)
	./demo

clean:
	clear
	$(RM) demo demo.exe
