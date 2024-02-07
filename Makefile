CFLAGS = -g -Wall -Werror -Wextra -Wuninitialized -Winit-self -Wmaybe-uninitialized

compile:
	gcc $(CFLAGS) -o compiler $(shell find . -name  '*.c') 

run: 
	./compiler test/case2.pcc

valgrind:
	valgrind ./compiler test/case2.pcc

debug:
	gdb --args ./compiler test/case2.pcc
	
clean:
	rm compiler 




	