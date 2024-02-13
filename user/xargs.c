#include "kernel/types.h"
#include "user/user.h"
char buf[512];
char *args[512];
int
main(int argc, char *argv[]) {
  int i = 1;
  for (; i < argc; i++) {
    args[i - 1] = argv[i];
    printf("[%s]", args[i - 1]);
  }
  int n;
  while ((n = read(0, buf, sizeof(buf))) > 0) {
    int len = strlen(buf);
    buf[len - 2] = '\0';
    printf("[%s]", buf);
    args[i] = (char *)malloc(len - 1);
    for (int j = 0; j < len - 1; j++) {
      args[i][j] = buf[j];
    }
    i += 1;
  }
  args[i] = 0;
  int args_num = i;
  exec(args[0], args);

  for (i = argc - 1; i < args_num; i++) {
    free(args[i]);
  }
  exit(0);
}

