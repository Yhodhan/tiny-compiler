CFLAGS = -g -Wall -Wformat -Werror -Wextra -Wuninitialized -Winit-self -Wmaybe-uninitialized

compile:
	gcc $(CFLAGS) -o compiler $(shell find . -name  '*.c') 

run: 
	./compiler test/case.pcc

valgrind:
	valgrind ./compiler test/case.pcc

debug:
	gdb --args ./compiler test/case.pcc
	
clean:
	rm compiler 




	