



int main() {
	state_func curr_state = idle;

	while(1) {
		curr_state = (state_func)(*curr_state)();
		fprintf(stderr, "(speed: %d | door lock: %d)\n", speed, door_lock);
		sleep(1);
		if (kbhit() && !act){
			c = getchar();
			if (c == '1') {
        act = 1;
				car_action = IDLE;
      } else if (c == '2') {
        act = 1;
        car_action = SPEED_UP;
      } else if (c == '3') {
        act = 1;
        car_action = BRAKE;
      } else if (c == '4') {
        act = 1;
        car_action = OPEN_DOORS;
      }
		}
	}

	return 0;
}
