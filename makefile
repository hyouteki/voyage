default: build 

CFLAGS = -Wall -Wextra
VOYAGE_FILES = $(wildcard $(PROJECT_BEING_TESTED_PATH)/voyage/*.h)

ifeq ($(OS),Windows_NT)
	LFLAGS = -lraylib -lgdi32 -lwinmm
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LFLAGS += -I./raylib/raylib-5.0_linux_amd64/include/
		LFLAGS += -L./raylib/raylib-5.0_linux_amd64/lib -l:libraylib.a
		LFLAGS += -lm
    else
        $(error "Unsupported OS; Supported OS (Windows, GNU/Linux)")
    endif
endif

build: demo.c $(VOYAGE_FILES) clean
	gcc demo.c -o demo $(CFLAGS) $(LFLAGS)
	./demo

clean:
	clear
	$(RM) demo demo.exe
