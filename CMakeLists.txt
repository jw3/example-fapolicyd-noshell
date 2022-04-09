cmake_minimum_required(VERSION 3.10)
project(example_fapolicyd_deny_shell)

set(CMAKE_CXX_STANDARD 14)

# lib
add_library(boo_lib SHARED lib.cpp)
set_target_properties(boo_lib PROPERTIES OUTPUT_NAME boo)

# main
add_executable(boo main.cpp)
target_link_libraries(boo boo_lib)
install(TARGETS boo boo_lib RUNTIME DESTINATION bin LIBRARY DESTINATION  lib)

# support
install(FILES boo.conf DESTINATION config)
install(FILES boo.service DESTINATION /etc/systemd/system)
install(FILES fapolicyd.rules DESTINATION /etc/fapolicyd)

# rpm
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_PACKAGE_NAME fapolicyd-deny-shell)
set(CPACK_INSTALL_PREFIX /usr/local/boo)
set(CPACK_RPM_PACKAGE_GROUP examples)
set(CPACK_SET_DESTDIR ON)
set(CPACK_RPM_PACKAGE_AUTOREQPROV no)
include(CPack)
