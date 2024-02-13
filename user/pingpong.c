#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
  int fd[2];
  pipe(fd);
  int ret = fork();
  if (ret == -1) {
    printf("pingpong: fork failed\n");
  } else if (0 == ret) {
    // child process
    char var;
    read(fd[1], &var, 1);
    int cpid = getpid();
    printf("%d: received ping\n", cpid);
    write(fd[0], "i", 1);
  } else {
    // father process
    write(fd[0], "i", 1);
    wait(0);
    char var;
    read(fd[1], &var, 1);
    int fpid = getpid();
    printf("%d: received pong\n", fpid);
  }

  exit(0);
}
