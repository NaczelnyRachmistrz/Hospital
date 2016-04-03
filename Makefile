all: structure.o parse.o hospital.o
	gcc -o hospital hospital.o parse.o structure.o
debug: debug_structure.o debug_parse.o debug_hospital.o
	gcc -o hospital.dbg debug_hospital.o debug_structure.o debug_parse.o
structure.o: structure.c structure.h
	gcc -c structure.c
parse.o: parse.c parse.h
	gcc -c parse.c
hospital.o: hospital.c
	gcc -c hospital.c
debug_structure.o: structure.c structure.h
	gcc -g -c structure.c -o debug_structure.o
debug_parse.o: parse.c parse.h
	gcc -g -c parse.c -o debug_parse.o
debug_hospital.o: hospital.c 
	gcc -g -c hospital.c -o debug_hospital.o
debug_clean:
	rm -f hospital.dbg debug_structure.o debug_parse.o debug_hospital.o
clean: 
	make debug_clean
	rm -f structure.o parse.o hospital.o hospital
