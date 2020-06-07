CC := gcc
OPS := -pthread
TARGET := hw4.c

all: hw4.o

.PHONY: clean all run style

hw4.o: $(TARGET)
	$(CC) $< $(OPS) -o $@

run:
	./hw4.o

clean:
	rm *.o

style:
	clang-format-6.0 -style=google -i *.c
