compile:
	gcc -g -Werror -W -o compiler $(shell find . -name  '*.c') 

run: 
	./compiler test/case2.pcc

valgrind:
	valgrind ./compiler test/case2.pcc

debug:
	gdb --args ./compiler test/case2.pcc
	
clean:
	rm compiler 




	