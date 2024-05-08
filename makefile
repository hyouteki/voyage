default: build 

build: demo.c
	clear
	gcc demo.c -lraylib -lgdi32 -lwinmm -o demo -I./voyage
	./demo

clean:
	$(RM) *.exe
