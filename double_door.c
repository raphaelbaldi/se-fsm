#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef void *(*state_func)();

int external_door = 0, internal_door = 0, client_between_doors = 0;
int client_action = 0, c;

int kbhit(void);
void *idle();
void *entering_bank();
void *exiting_bank();
void *open_internal_door();
void *close_internal_door();
void *open_external_door();
void *close_external_door();
void *client_enters_doors();
void *client_exits_doors();

#define ENTER_BANK 1
#define EXIT_BANK 2

void *idle() {
	fprintf(stderr, "IDLE ");
	external_door = 0; internal_door = 0; client_between_doors = 0;

  // If no client is waiting, keep the bank doors idle.
	if (client_action == 0)	return idle;

  // If a client is entering the bank, switch state to enter.
	if (client_action == ENTER_BANK)	return entering_bank;

  // If a client is exiting the bank, switch state to exit.
	if (client_action == EXIT_BANK)	return exiting_bank;
	return 0;
}

void *client_enters_doors() {
	fprintf(stderr, "CLIENT ENTERING DOORS ");
	// Mark the client as being in between doors.
	client_between_doors = 1;
	if (client_action == ENTER_BANK) {
		// If the client is entering the bank, next state should close
		// the external door.
		return close_external_door;
	} else if (client_action == EXIT_BANK) {
		// If the client is exiting the bank, next state should close
		// the internal door.
		return close_internal_door;
	}
	return 0;
}

void *client_exits_doors() {
	fprintf(stderr, "CLIENT EXITING DOORS ");
	// Mark the client as no longer between double doors.
	client_between_doors = 0;
	if (client_action == ENTER_BANK) {
		// If the client was entering the bank, close internal door.
		return close_internal_door;
	} else if (client_action == EXIT_BANK) {
		// If the client was exiting the bank, close external door.
		return close_external_door;
	}
	return 0;
}

void *open_internal_door() {
	fprintf(stderr, "OPEN INTERNAL DOOR ");
	// Mark internal door as open
	internal_door = 1;
	if (client_action == ENTER_BANK) {
		// If client is entering the bank, he can now leave the double doors.
		return client_exits_doors;
	} else if (client_action == EXIT_BANK) {
		// If the client is exiting the bank, he can now enter the double doors.
		return client_enters_doors;
	}
	return 0;
}

void *close_internal_door() {
	fprintf(stderr, "CLOSE INTERNAL DOOR ");
	// Mark internal door as closed
	internal_door = 0;
	if (client_action == ENTER_BANK) {
		// If the client was entering the bank, the flow is over.
		// Return to idle.
		client_action = 0;
		return idle;
	} else if (client_action == EXIT_BANK) {
		// If the client is exiting the bank, we now need to open the
		// external door.
		return open_external_door;
	}
	return 0;
}

void *open_external_door() {
	fprintf(stderr, "OPEN EXTERNAL DOOR ");
	// Mark external door as open.
	external_door = 1;
	if (client_action == ENTER_BANK) {
		// If the client is entering the bank, he can now move into
		// the double doors.
		return client_enters_doors;
	} else if (client_action == EXIT_BANK) {
		// If the client was exiting the bank, we now need to close
		// the external doors.
		return client_exits_doors;
	}
	return 0;
}

void *close_external_door() {
	fprintf(stderr, "CLOSE EXTERNAL DOOR ");
	// Mark external door as closed.
	external_door = 0;
	if (client_action == ENTER_BANK) {
		// If the client is entering the bank, we now need to open
		// the internal doors.
		return open_internal_door;
	} else if (client_action == EXIT_BANK) {
		// If the client was exiting the bank, the flow is over.
		// Return to idle.
		client_action = 0;
		return idle;
	}
	return 0;
}

void *entering_bank() {
	fprintf(stderr, "ENTERING ");
	// The client wants to enter the bank, start by openning the external door.
  return open_external_door;
}

void *exiting_bank() {
	fprintf(stderr, "EXITING ");
	// The client wants to leave the bank, start by openning the internal door.
	return open_internal_door;
}

int main() {
	state_func curr_state = idle;

	while(1) {
		curr_state = (state_func)(*curr_state)();
		fprintf(stderr, "(external door: %d | client between doors: %d | internal door: %d)\n", external_door, client_between_doors, internal_door);
		sleep(1);
		if (kbhit() && !client_action){
			c = getchar();
			if (c == '0') {
				client_action = ENTER_BANK;
      } else if (c == '1') {
        client_action = EXIT_BANK;
      }
		}
	}

	return 0;
}
