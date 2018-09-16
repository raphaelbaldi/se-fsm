CC      = gcc
CFLAGS  = -O2

.PHONY : all
.DEFAULT_GOAL := all

all: doors car-lock ejection-seat

doors:
	$(CC) $(CFLAGS) kbhit.c double_door.c -o doors

car-lock:
	$(CC) $(CFLAGS) kbhit.c car_lock.c -o car

ejection-seat:
	$(CC) $(CFLAGS) kbhit.c ejection_seat.c -o ejection

clean:
	-rm -f *.o *~ doors car ejection
