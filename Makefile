all:
	make structure
	make parse
	make hospital
	gcc -o hospital hospital.o parse.o structure.o
debug:
	make
	gcc hospital.c structure.c parse.c -g -o hospital.dbg
structure: structure.c structure.h
	gcc -g -c structure.c
parse: parse.c parse.h
	gcc -g -c parse.c
hospital: hospital.c
	gcc -g -c hospital.c
clean: 
	rm -f structure.o parse.o hospital.o hospital.dbg hospital
	
