#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int
getcmd(char *buf, int nbuf)
{
  memset(buf, 0, nbuf);
  gets(buf, nbuf);
  if(buf[0] == 0) // EOF
    return -1;
  return 0;
}

int 
parsecmd(char **argv, int offset, char *buf, int nbuf)
{
  int n = getcmd(buf, nbuf);
  if (n == -1)
  {
    return 0;
  }

  int argc = 0;
  char *q = buf;

  argv[offset] = q;
  while (*q != 0)
  {
    switch (*q)
    {
    case '\n':
      *q = 0;
      argc++;
      argv[argc + offset] = 0;
      break;
    case '\t':
    case ' ':
      *q = 0;
      argc++;
      q++;
      argv[argc + offset] = q;
      break;
    default:
      q++;
      break;
    }
  }
  return argc;
}

int
main(int argc, char *argv[])
{
  char buf[512];
  int nbuf = 512;
  int ext_argc = 0;
  int pid;

  char *new_argv[MAXARG];
  memset(new_argv, 0, MAXARG);
  for (int i = 1; i < argc; i++)
  {
    new_argv[i - 1] = argv[i];
  }
  argc--;

  while ((ext_argc = parsecmd(new_argv, argc, buf, nbuf)) != 0)
  {
    pid = fork();
    if (pid == 0)
    {
      exec(new_argv[0], new_argv);
    }
    else
    {
      wait((int *) 0);
    }
  }
  exit(0);
}