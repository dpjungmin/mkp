CC = gcc
CFLAGS = -Wall -g
TARGET = mkp
OBJECTS = mkp.o main.o
HEADERS = $(wildcard *.h.gch)
TEST_OBJECTS = tests.o

define gen_target
	$(CC) $(CFLAGS) $^ -o $@
endef

define gen_obj
	$(CC) $(CFLAGS) -c $^
endef

# RULES

.DELETE_ON_ERROR: $(TARGET)

all: $(TARGET)

$(TARGET): $(OBJECTS) ; $(gen_target)

mkp.o: mkp.c mkp.h ; $(gen_obj)

main.o: main.c mkp.h ; $(gen_obj)

test: $(TEST_OBJECTS) ; $(gen_target)

tests.o: tests.c util.h ; $(gen_obj)

# CLEANUP

.PHONY: clean cleanobj cleanh cleantest

clean: cleanobj cleanh cleantest ; -rm -f $(TARGET)

cleanobj: ; -rm -f $(OBJECTS)

cleanh: ; -rm -f $(HEADERS)

cleantest: ; -rm -f test $(TEST_OBJECTS)

