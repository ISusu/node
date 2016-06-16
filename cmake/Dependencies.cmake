#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(OpenSSL QUIET)
if(OPENSSL_FOUND)
  include_directories("${OPENSSL_INCLUDE_DIR}")
endif()
