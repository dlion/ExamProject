VERSION = 1.1

CC = g++
LFLAGS = `pkg-config --cflags --libs opencv`
LIB = lib/funzioni.h
EXTRA = -pthread
STANDARD = --std=gnu++11

all: Bubbles/bubbles.c Draw/draw.c Head/head.c Movement/movement.c config/calibra.c $(LIB)
	$(CC) $(LFLAGS) $(EXTRA) Bubbles/bubbles.c -o Bubbles/bubbles
	$(CC) $(LFLAGS) Draw/draw.c -o Draw/draw
	$(CC) $(LFLAGS) Head/head.c -o Head/head
	$(CC) $(LFLAGS) Movement/movement.c -o Movement/movement
	$(CC) $(LFLAGS) $(STANDARD) config/calibra.c -o config/calibra
bubbles: Bubbles/bubbles.c $(LIB)
	$(CC) $(LFLAGS) $(EXTRA) Bubbles/bubbles.c -o Bubbles/bubbles
draw: Draw/draw.c $(LIB)
	$(CC) $(LFLAGS) Draw/draw.c -o Draw/draw
head: Head/head.c $(LIB)
	$(CC) $(LFLAGS) Head/head.c -o Head/head
movement: Movement/movement.c $(LIB)
	$(CC) $(LFLAGS) Movement/movement.c -o Movement/movement
calibra: config/calibra.c $(LIB)
	$(CC) $(LFLAGS) $(STANDARD) config/calibra.c -o config/calibra

#By Domenico Luciani <domenico.luciani@email.it>

