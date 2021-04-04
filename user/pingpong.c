#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int fds[2];
  char buf[10];
  int n, pid;

  pipe(fds);

  pid = fork();
  if (pid == 0)
  {
    n = read(fds[0], buf, 1);
    if (n <= 0)
    {
      fprintf(2, "pingpong: didn't receive a byte");
      exit(1);
    }
    fprintf(1, "%d: received ping\n", getpid());
    write(fds[1], "h", 1);
    exit(0);
  } 
  else 
  {
    write(fds[1], "h", 1);
    wait((int *) 0);
    n = read(fds[0], buf, 1);
    if (n <= 0)
    {
      fprintf(2, "pingpong: didn't receive a byte");
      exit(1);
    }
    fprintf(1, "%d: received pong\n", getpid());
    exit(0);
  }
}