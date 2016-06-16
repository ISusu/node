#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.6)
project(node)

#------------------------------------------------------------------------------
include(cmake/Dependencies.cmake)

#------------------------------------------------------------------------------
if (UNIX)
  add_definitions(-Wall)
  if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
  else ()
    add_definitions(-std=stdc++11)
  endif()
endif()

#------------------------------------------------------------------------------
include(cmake/CheckSystemPlatform.cmake)
CHECK_SYSTEM_PLATFORM(SYSTEM_PLATFORM SYSTEM_ARCH SYSTEM_ENDIAN)
configure_file(config.h.in ${PROJECT_SOURCE_DIR}/node/config.h)

#------------------------------------------------------------------------------
include_directories(
  "${PROJECT_SOURCE_DIR}"
)

#------------------------------------------------------------------------------
if (WIN32)
  set(SRC_PLAT "win32")
elseif (UNIX)
  set(SRC_PLAT "posix")
endif()

set(node_OS_SRC
  node/os/string.h
  
  src/os/string.cpp
  src/os/string_${SRC_PLAT}.cpp
)

set(node_Base_SRC
  node/noncopyable.h
  node/platform.h
  node/config.h
  node/macros.h
  node/auto_ptr.h
  node/scoped_ptr.h
  node/scoped_array.h
  node/byte_converter.h
  node/byte_buffer.h
  node/byte_buffer.inl
  
  src/byte_buffer.cpp
)
set(node_Thread_SRC
  node/thread/runnable.h
  node/thread/event.h
  node/thread/event_${SRC_PLAT}.h
  node/thread/mutex.h
  node/thread/mutex_${SRC_PLAT}.h
  node/thread/thread.h
  node/thread/thread_${SRC_PLAT}.h
  node/thread/tss.h
  node/thread/tss_${SRC_PLAT}.h
  node/thread/lock_guard.h
  
  src/thread/event.cpp
  src/thread/event_${SRC_PLAT}.cpp
  src/thread/mutex.cpp
  src/thread/mutex_${SRC_PLAT}.cpp
  src/thread/thread.cpp
  src/thread/thread_${SRC_PLAT}.cpp
  src/thread/tss.cpp
  src/thread/tss_${SRC_PLAT}.cpp
)
if(OPENSSL_FOUND)
  set(node_Crypto_SRC
    node/crypto/bignumber.h
    node/crypto/sha1.h
    node/crypto/hmac.h
    
    src/crypto/bignumber.cpp
    src/crypto/sha1.cpp
    src/crypto/hmac.cpp
  )
endif(OPENSSL_FOUND)

if (WIN32)
  source_group("OS" FILES ${node_OS_SRC})
  source_group("Base" FILES ${node_Base_SRC})
  source_group("Thread" FILES ${node_Thread_SRC})
  if(OPENSSL_FOUND)
    source_group("Crypto" FILES ${node_Crypto_SRC})
  endif(OPENSSL_FOUND)
endif()

#------------------------------------------------------------------------------
set(node_SRC
  ${node_OS_SRC}
  ${node_Base_SRC}
  ${node_Thread_SRC}
)
if(OPENSSL_FOUND)
  set(node_SRC ${node_Crypto_SRC} ${node_SRC})
endif(OPENSSL_FOUND)

add_library(node STATIC ${node_SRC})