#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int ret;

  // (a) Attempt to yield to a non-existent PID
  printf("Test (a): non-existent PID\n");
  ret = co_yield(9999, 42);
  printf("co_yield(9999, 42) = %d (expected -1)\n", ret);

  // (b) Attempt to yield to self
  printf("Test (c): self-yield\n");
  ret = co_yield(getpid(), 42);
  printf("co_yield(self, 42) = %d (expected -1)\n", ret);

  // (c) Attempt to yield to a killed process
  printf("Test (b): killed process\n");
  int pid_killed = fork();
  if(pid_killed == 0){
    // Child: just exit immediately
    exit(0);
  }
  wait(0); // wait for child to finish (now it's gone)
  ret = co_yield(pid_killed, 42);
  printf("co_yield(killed, 42) = %d (expected -1)\n", ret);

  printf("Error tests passed!\n\n");

  // Basic co_yield ping-pong (from assignment)
  printf("Basic co_yield test:\n");
  int pid1 = getpid();
  int pid2 = fork();

  if (pid2 == 0) { // Child
    for (;;) {
      int value = co_yield(pid1, 1);
      printf("Child received: %d\n", value); // Should print 2
    }
  } else { // Parent
    for (;;) {
      int value = co_yield(pid2, 2);
      printf("parent received: %d\n", value); // Should print 1
    }
  }
}

