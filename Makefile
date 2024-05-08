CFLAGS = -g -Wall -Wformat -Werror -Wextra -Wuninitialized -Winit-self -Wmaybe-uninitialized

compile:
	gcc $(CFLAGS) -o compiler $(shell find . -name  '*.c') 

run: 
	./compiler test/case.pcc

format:
	find . -iname *.h -o -iname *.cpp | xargs clang-format -style=llvm -i

valgrind:
	valgrind ./compiler test/case.pcc

debug:
	gdb --args ./compiler test/case.pcc
	
clean:
	rm compiler 
	rm emit.c




	
