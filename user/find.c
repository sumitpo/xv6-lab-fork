// clang-format off
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
// clang-format on

void
find(char *path, char *filename) {
  int fd;
  char *p;
  struct dirent de;
  struct stat st;
  if ((fd = open(path, O_RDONLY)) < 0) {
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
  if (T_DIR != st.type) {
    close(fd);
    return;
  }
  p = path + strlen(path);
  *p++ = '/';
  while (read(fd, &de, sizeof(de)) == sizeof(de)) {
    if (de.inum == 0) continue;
    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;
    if (stat(path, &st) < 0) {
      printf("ls: cannot stat %s\n", path);
      continue;
    }
    if (T_DIR == st.type) {
      if (strcmp(de.name, ".") == 0) {
        continue;
      }
      if (strcmp(de.name, "..") == 0) {
        continue;
      }
      find(path, filename);
    } else {
      if (strcmp(de.name, filename) == 0) {
        printf("%s\n", path);
      }
    }
    // printf("%s %d %d %d\n", buf, st.type, st.ino, st.size);
  }
  *p = 0;
  close(fd);
}

int
main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("find [path] [filename]\n");
    exit(0);
  }
  char buf[512];
  strcpy(buf, argv[1]);
  find(buf, argv[2]);
  exit(0);
}
