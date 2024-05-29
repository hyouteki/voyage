default: build 

build: demo.c
	clear
	gcc demo.c -lraylib -lgdi32 -lwinmm -o demo
	./demo
	make clean

clean:
	$(RM) *.exe
