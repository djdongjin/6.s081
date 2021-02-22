#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

void 
copy_str_arrs(char *dst[], char *src[], int cnt)
{
  int i;
  for (i = 0; i < cnt; i++)
  {
    strcpy(dst[i], src[i]);
  }
  dst[cnt] = 0;
}

int
main(int argc, char *argv[])
{
  char new_argv[MAXARG][512];
  int i;
  for (int i = 0; i < argc; i++)
  {
    strcpy(new_argv + i, argv[i]);
  }

  int ext_argc = 0;
  char *p = new_argv[argc];
  char ch;
  int len = 0;

  while ((read(0, ch, sizeof(ch))) == sizeof(ch))
  {
    switch (ch)
    {
    case '\n':
      char *copy_argv[MAXARG][512];
      copy_str_arrs(copy_argv, new_argv, argc + ext_argc);
      int pid = fork();
      if (pid == 0)
      {
        exec(copy_argv[0], copy_argv);
        exit(1);
      }
      else
      {
        ext_argc = 0;
        p = new_argv[argc];
        len = 0;
      }
      break;

    case ' ':
    case '\t':
      if (len != 0)
      {
        *p = 0;
        ext_argc++;
        p = new_argv[argc + ext_argc];
        len = 0;
      }
      break;
    
    default:
      *p++ = ch;
      len++;
      break;
    }
  }
  wait((int *) 0);
  exit(0);
}