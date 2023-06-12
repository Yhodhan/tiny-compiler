compile:
	gcc -g -o compiler $(shell find . -name  '*.c') 

run: 
	./compiler 

valgrind:
	valgrind ./compiler

debug:
	gdb ./compiler
	
clean:
	rm compiler 




	