#include <cstdlib>
#include "boo.h"

int ok(const char* cmd) {
   return 0;
}

int err(const char* cmd) {
   return system(cmd);
}
