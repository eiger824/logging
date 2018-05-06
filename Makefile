CFLAGS  := -c -Wall -Wextra -Wpedantic -std=c17
LDFLAGS := -Wall -Wextra -Wpedantic -std=c17 -pthread

all: test

test: log.o main.o
	gcc  $^ -o $@ $(LDFLAGS)

%.o: %.c %.h
	gcc $< -o $@ $(CFLAGS)

%.o: %.c
	gcc $< -o $@ $(CFLAGS)

clean:
	rm -f test *.o *~
