default: build 

build: demo.c
	clear
	gcc demo.c -lraylib -lgdi32 -lwinmm -o demo
	./demo
	make clean


logo: logo.c
	clear
	gcc logo.c -lraylib -lgdi32 -lwinmm -o logo
	./logo
	make clean

clean:
	$(RM) *.exe
