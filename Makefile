CC = gcc
CFLAGS = -Wall -g
TARGET = mkp
OBJECTS = mkp.o main.o
TEST_OBJECTS = tests.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

mkp.o: mkp.c mkp.h
	$(CC) $(CFLAGS) -c $^

main.o: main.c mkp.h
	$(CC) $(CFLAGS) -c $^

test: $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

tests.o: tests.c util.h
	$(CC) $(CFLAGS) -c $^

.PHONY: clean
clean:
	rm -f *.h.gch $(TARGET) $(OBJECTS) test $(TEST_OBJECTS)
