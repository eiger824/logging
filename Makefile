test: main.o log.o
	gcc -Wall -Wextra -Wpedantic --std=c11 -lpthread $^ -o $@

%.o: %.c
	gcc -c -Wall -Wextra -Wpedantic --std=c11 $^ -o $@ 

clean:
	rm -f print *~
