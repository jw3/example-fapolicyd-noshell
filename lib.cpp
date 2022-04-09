#include <cstdlib>
#include "boo.h"

int no_shell() {
   return 0;
}

int with_shell(const char* cmd) {
   return system(cmd);
}
