#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
  if (argc < 2) {
    write(1, "usage: sleep [time second]\n", 27);
  }

  int time_intervals = atoi(argv[1]);
  sleep(time_intervals);

  exit(0);
}
