#include <iostream>
#include <fstream>

#include "boo.h"

int main(int c, char** v) {
   // show that the config file can be read
   std::ifstream in("/usr/local/boo/config/boo.conf");
   std::string shell;
   in >> shell;

   // it is ok to call into the lib
   int ec = no_shell();
   std::cout << "calling into the lib is" << (ec ? " not " : " ") << "ok" << std::endl;

   // but creating a shell is not ok
   ec = with_shell(shell.c_str());
   std::cout << "summoning a shell is" << (ec ? " not " : " ") << "ok" << std::endl;

   return ec;
}
