#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef void *(*state_func)();

#define EJECT 1
#define SPEED_DOWN 2
#define SPEED_UP 3
#define ROLL_LEFT 4
#define ROLL_RIGHT 5
#define MIN_SAFE_ROOL -90
#define MAX_SAFE_ROOL 90
#define ANGLE_DELTA 15
#define SPEED_DELTA 100
#define MIN_FLIGHT_SPEED 330
#define MAX_FLIGHT_SPEED 2450
#define MAX_EJECT_SPEED 1225


int req = 0, current_angle = 0, current_speed = 0, ejection_req = 0, ejecting = 0;
int c;

int kbhit(void);
void *ejection_mode(); // Ejection mode - emergency
void *normal_mode(); // In flight

//------------------------------------------------------------------------------
//=================== UTILITY METHOD TO SELECT NEXT MODE =======================
//------------------------------------------------------------------------------
void *select_operation_mode() {
  if (ejecting) {
    return ejection_mode;
  }
  return normal_mode;
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//================ AIRCRAFT OPERATIONS, COMMON TO BOTH METHODS =================
//------------------------------------------------------------------------------
// Increase aircraft speed.
void *speed_up() {
  fprintf(stderr, "SPEED UP ");
  current_speed += SPEED_DELTA;
  if (current_speed > MAX_FLIGHT_SPEED) {
    current_speed = MAX_FLIGHT_SPEED;
  }
  return select_operation_mode();
}

// Decrease aircraft speed.
void *speed_down() {
  fprintf(stderr, "SPEED DOWN ");
  current_speed -= SPEED_DELTA;
  if (current_speed < MIN_FLIGHT_SPEED) {
    current_speed = MIN_FLIGHT_SPEED;
  }
  return select_operation_mode();
}

// Roll the aircraft left.
void *roll_left() {
  fprintf(stderr, "ROLL LEFT ");
  current_angle -= ANGLE_DELTA;
  if (current_angle < -180) {
    current_angle = 360 + current_angle;
  }
  return select_operation_mode();
}

// Roll the aircraft right.
void *roll_right() {
  fprintf(stderr, "ROLL RIGHT ");
  current_angle += ANGLE_DELTA;
  if (current_angle > 180) {
    current_angle = 360 - current_angle;
  }
  return select_operation_mode();
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//============================= EJECTION MODE ==================================
//------------------------------------------------------------------------------
int safe_to_eject() {
  // Check if conditions are fine for ejection.
  if (current_speed > MAX_EJECT_SPEED) {
    return 0;
  }

  if (current_angle > MAX_SAFE_ROOL || current_angle < MIN_SAFE_ROOL) {
    return 0;
  }

  return 1;
}

void *ejection_mode() {
  fprintf(stderr, "EJECTING ");
  if (safe_to_eject()) {
    fprintf(stderr, "\n\nSAFE TO EJECT. OFF YOU GO!\n\n");
    return 0;
  }

  switch (req) {
    case ROLL_LEFT: return roll_left;
    case ROLL_RIGHT: return roll_right;
    case SPEED_UP: return speed_up;
    case SPEED_DOWN: return speed_down;
  }
  return ejection_mode;
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//============================ NORMAL OPERATION ================================
//------------------------------------------------------------------------------
void *eject() {
  fprintf(stderr, "REQUEST EJECT ");
  // Increment ejection request count and verify if condition met.
  ++ejection_req;
  if (ejection_req >= 2) {
    ejecting = 1;
    return ejection_mode;
  }

  return normal_mode;
}

// Run normal operation
void *normal_mode() {
  fprintf(stderr, "FLYING ");
  if (req == EJECT) {
    return eject;
  }

  // We haven't received two requests to eject in a row (one second).
  // Reset the counter.
  ejection_req = 0;

  switch (req) {
    case ROLL_LEFT: return roll_left;
    case ROLL_RIGHT: return roll_right;
    case SPEED_UP: return speed_up;
    case SPEED_DOWN: return speed_down;
  }
  req = 0;
  return normal_mode;
}
//------------------------------------------------------------------------------

int main() {
	state_func curr_state = normal_mode;
  current_speed = MAX_EJECT_SPEED;

	while(1) {
		curr_state = (state_func)(*curr_state)();

    // If we're done with the aircraft operation (pilot out of airplane),
    // Stop execution.
    if (curr_state == 0) {
      break;
    }
		fprintf(stderr, "(current request: %d | speed: %d | angle: %d)\n", req, current_speed, current_angle);
		sleep(1);
    req = 0;
		if (kbhit()){
			c = getchar();
			if (c == '0') {
				req = EJECT;
      } else if (c == '2') {
        req = SPEED_DOWN;
      } else if (c == '8') {
        req = SPEED_UP;
      } else if (c == '4') {
        req = ROLL_LEFT;
      } else if (c == '6') {
        req = ROLL_RIGHT;
      }
		}
	}

	return 0;
}
