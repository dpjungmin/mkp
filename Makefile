CC = gcc
CFLAGS = -Wall -g
TARGET = mkp

all: $(TARGET)

$(TARGET): mkp.o main.o
	$(CC) $(CFLAGS) -o $@ $^

mkp.o: mkp.c
	$(CC) $(CFLAGS) -c $^

main.o: main.c
	$(CC) $(CFLAGS) -c $^

test: tests.o
	$(CC) $(CFLAGS) -o $@ $^

tests.o: tests.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.o *.so $(TARGET) test
