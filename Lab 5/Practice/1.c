#include <unistd.h>
main()
{
   char *args[] = { (char *) 0 };

  execv("/bin/pwd", args);
}
