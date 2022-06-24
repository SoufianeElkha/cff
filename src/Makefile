TARGET=cff
CC=gcc
FLAGS=-g -Wall -Wextra -pedantic -fsanitize=address -fno-omit-frame-pointer
LIBS=-lm -lSDL2
OBJECTS=cff.o lire_file.o file.o cellule.o matrice.o gfx.o drawing.o
HEADERS = $(wildcard *.h)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ $(FLAGS) $(LIBS) -o $@

$(OBJECTS): %.o: %.c $(HEADERS)
	$(CC) -c $(FLAGS) $<

run:
	clear && ./cff

clean:
	rm -rf *.o $(TARGET)

.PHONY: clean all
