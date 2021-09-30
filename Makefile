VPATH = src:include:tests

CC = gcc
CFLAGS = -Wall -g
TARGET = mkp
DEPS = main.o mkp.o list.o

.DELETE_ON_ERROR: $(TARGET)

all: $(TARGET)

$(TARGET): $(DEPS)
	$(CC) $(CFLAGS) $^ -o $@

test: test.o test_list.o list.o
	$(CC) $(CFLAGS) $^ -o $@ -pthread

%.o: %.c
	$(CC) $(CFLAGS) -I include -c $^

.PHONY: clean

clean:
	-rm -f $(TARGET)
	-rm -f test
	-rm -f *.o
	-rm -f ./include/*.gch
	-rm -f ./tests/*.gch