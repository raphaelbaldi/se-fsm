#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef void *(*state_func)();

int external_door = 0, internal_door = 0, client_between_doors = 0;
int client_wait = 0, c;

int kbhit(void);
void *idle();
void *entering_bank();
void *exiting_bank();

#define ENTER_BANK 1
#define EXIT_BANK 2

void *idle() {
	fprintf(stderr, "IDLE ");
	external_door = 0; internal_door = 0; client_between_doors = 0;

  // If no client is waiting, keep the bank doors idle
	if (client_wait == 0)	return idle;

  // If a client is entering the bank, switch state to enter
	if (client_wait == ENTER_BANK)	return entering_bank;

  // If a client is exiting the bank, switch state to exit
	if (client_wait == EXIT_BANK)	return exiting_bank;
	return 0;
}

void *entering_bank() {
	fprintf(stderr, "ENTERING ");
  if (client_between_doors) {
    if (external_door) {
      // Client in between doors, external door open, close it
      external_door = 0;
    } else if (!internal_door) {
      // Client in between doors, internal door closed, open it
      internal_door = 1;
    } else {
      // Internal door open, client exit
      client_between_doors = 0;
    }
  } else {
    if (internal_door) {
      // No client in between doors, internal door open, close and get back to idle
      internal_door = 0;
      client_wait = 0;
      return idle;
    } else if (!external_door) {
      // Client not in between doors, external door closed, open it
      external_door = 1;
    } else {
      // Client not in between doors, external door open, client enters it
      client_between_doors = 1;
    }
  }
  return entering_bank;
}

void *exiting_bank() {
	fprintf(stderr, "EXITING ");
  if (client_between_doors) {
    if (internal_door) {
      // Client in between doors, internal door open, close it
      internal_door = 0;
    } else if (!external_door) {
      // Client in between doors, external door closed, open it
      external_door = 1;
    } else {
      // Client in between doors, external door open, client exit it
      client_between_doors = 0;
    }
  } else {
    if (external_door) {
      // No client inside, external door open, close and get back to idle
      external_door = 0;
      client_wait = 0;
      return idle;
    } else if (!internal_door) {
      // Both doors closed, open internal door
      internal_door = 1;
    } else {
      // Internal door open, client enters it
      client_between_doors = 1;
    }
  }
  return exiting_bank;
}

int main() {
	state_func curr_state = idle;

	while(1){
		curr_state = (state_func)(*curr_state)();
		fprintf(stderr, "BANK: (external door: %d | client between doors: %d | internal door: %d)\n", external_door, client_between_doors, internal_door);
		sleep(1);
		if (kbhit() && !client_wait){
			c = getchar();
			if (c == '0') {
				client_wait = ENTER_BANK;
      } else if (c == '1') {
        client_wait = EXIT_BANK;
      }
		}
	}

	return 0;
}
