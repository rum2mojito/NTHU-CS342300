CC := gcc
OPS := -pthread
TARGET := hw3.c

all: hw3.o

.PHONY: clean all run

hw3.o: $(TARGET)
	$(CC) $< $(OPS) -o $@

run:
	./hw3.o ../data/testcase.txt output.txt

clean:
	rm *.o output.txt