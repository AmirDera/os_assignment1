#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  printf("Memory before allocation: %d bytes\n", memsize());

  char *p = malloc(20000);

  printf("Memory after allocation: %d bytes\n", memsize());

  free(p);

  printf("Memory after free: %d bytes\n", memsize());

  exit(0);
}
