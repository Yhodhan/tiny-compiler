compile:
	gcc -g -o compiler *.c 

run: 
	./compiler 

valgrind:
	valgrind ./compiler

debug:
	gdb ./compiler
	
clean:
	rm compiler 




	