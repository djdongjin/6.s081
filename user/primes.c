#include "kernel/types.h"
#include "user/user.h"

void
filter(int reader)
{
  int pid, prime, i, n;

  if ((n = read(reader, &prime, sizeof(prime))) > 0)
  {
    int fds[2];
    pipe(fds);
    pid = fork();
    if (pid == 0)
    {
      close(reader);
      close(fds[1]);
      filter(fds[0]);
      close(fds[0]);
    }
    else
    {
      fprintf(1, "prime %d\n", prime);
      while ((n = read(reader, &i, sizeof(i))) > 0)
      {
        if (i % prime != 0)
        {
          write(fds[1], &i, sizeof(i));
        }
      }
      close(reader);
      close(fds[1]);
      close(fds[0]);
      wait((int *) 0);
    }
  }
  exit(0);
}

int
main(int argc, char *argv[])
{
  int pid, i;
  int fds[2];
  pipe(fds);

  pid = fork();

  if (pid == 0)
  {
    close(fds[1]);
    filter(fds[0]);
    close(fds[0]);
  }
  else
  {
    for (i = 2; i <= 35; i++)
    {
      write(fds[1], &i, sizeof(i));
    }
    close(fds[1]);
    close(fds[0]);
    wait((int *) 0);
  }
  exit(0);
}