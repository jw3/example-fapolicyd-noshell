#include <iostream>
#include <cstdlib>
#include "boo.h"

int no_shell() {
   std::cout << "[no_shell]   ";
   return 0;
}

int with_shell(const char* cmd) {
   std::cout << "[with_shell] ";
   return system(cmd);
}
