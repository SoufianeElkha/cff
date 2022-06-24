TARGET=cff
CC=gcc
FLAGS=-g -Wall -Wextra -pedantic -fsanitize=address -fno-omit-frame-pointer
LIBS=-lm
OBJECTS=cff.o lire_file.o file.o cellule.o matrice.o
HEADERS = $(wildcard *.h)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ $(FLAGS) $(LIBS) -o $@

$(OBJECTS): %.o: %.c $(HEADERS)
	$(CC) -c $(FLAGS) $<

run:
	./cff

clean:
	rm -rf *.o $(TARGET)

.PHONY: clean all
