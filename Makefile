VPATH = src:include

CC = gcc
CFLAGS = -Wall -g
TARGET = mkp
DEPS = main.o mkp.o

define create_obj
	$(CC) $(CFLAGS) -I include -c $^
endef

.DELETE_ON_ERROR: $(TARGET)

all: $(TARGET)

$(TARGET): $(DEPS)
	$(CC) $(CFLAGS) $^ -o $@ -pthread

mkp.o: mkp.c mkp.h
	$(create_obj)

main.o: main.c mkp.h
	$(create_obj)

test: test.o
	$(CC) $(CFLAGS) $^ -o $@ -pthread

test.o: test.c util.h
	$(create_obj)

.PHONY: clean

clean:
	-rm -f $(TARGET)
	-rm -f *.o
	-rm -f ./include/*.gch
	-rm -f test
