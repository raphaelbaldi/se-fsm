#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef void *(*state_func)();
int kbhit(void);

#define SPEED_UP 1
#define SPEED_DOWN 2
#define OPEN_DOORS 3
#define LOCK_DOORS_SPEED 30
#define MAX_SPEED 100

int door_lock = 0, speed = 0;
int car_action = 0, c;

void *speed_up();
void *speed_down();
void *auto_door_lock();
void *idle();

// Controls the car's slow down state.
void *speed_down() {
  fprintf(stderr, "SPEED DOWN ");
  speed -= 0;
  if (speed < 0) {
    speed = 0;
  }
  return idle;
}

// Controls the car's speeding up state.
void *speed_up() {
  fprintf(stderr, "SPEED UP ");
  speed += 5;
  if (speed > MAX_SPEED) {
    speed = MAX_SPEED;
  }
  return idle;
}

// Controls the automatic locking mechanism of the doors.
void *auto_door_lock() {
  fprintf(stderr, "CHECK AUTO LOCK DOORS ");
  if (door_lock || speed < LOCK_DOORS_SPEED) {
    return idle;
  }
  door_lock = 1;
  return idle;
}

// Car is idling.
void *idle() {
  fprintf(stderr, "IDLE ");
    switch (car_action) {
      case SPEED_UP: return speed_up;
      case SPEED_DOWN: return speed_down;
    }

    if (!door_lock) {
      return auto_door_lock;
    }

    return idle;
}

int main() {
	state_func curr_state = idle;

	while(1) {
		curr_state = (state_func)(*curr_state)();
		fprintf(stderr, "(speed: %d | door lock: %d)\n", speed, door_lock);
		sleep(1);
    car_action = 0;
		if (kbhit()){
			c = getchar();
			if (c == '8') {
        car_action = SPEED_UP;
      } else if (c == '2') {
        car_action = SPEED_DOWN;
      } else if (c == '4') {
        car_action = OPEN_DOORS;
      }
		}
	}

	return 0;
}
