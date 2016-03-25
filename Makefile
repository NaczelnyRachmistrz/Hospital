all: structure.c structure.h parse.c parse.h hospital.c
	gcc -g -c structure.c
	gcc -g -c parse.c
	gcc -g -c hospital.c
	gcc -o hospital hospital.o parse.o structure.o
debug:
	make
	gcc hospital.c structure.c parse.c -g -o hospital.dbg
clean: 
	rm -f structure.o parse.o hospital.o hospital.dbg hospital
	
