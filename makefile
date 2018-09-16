CC      = gcc
CFLAGS  = -O2

.PHONY : all
.DEFAULT_GOAL := all

all: doors

doors:
	$(CC) $(CFLAGS) kbhit.c double_door.c -o doors

clean:
	-rm -f *.o *~ doors
