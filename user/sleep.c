#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc <= 1)
  {
    fprintf(2, "usage: sleep timeElapsed");
    exit(1);
  }

  int sleep_length = atoi(argv[1]);
  if (sleep_length < 0)
  {
    fprintf(2, "sleep: please input a positive sleep length");
    exit(1);
  }

  sleep(sleep_length);
  exit(0);
}