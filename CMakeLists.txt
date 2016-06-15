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
)

set(node_Base_SRC
    node/noncopyable.h
    node/platform.h
    node/config.h
)
set(node_Thread_SRC
    node/thread/mutex.h
    node/thread/mutex_${SRC_PLAT}.h
    node/thread/thread.h
    node/thread/thread_${SRC_PLAT}.h
    node/thread/tss.h
    node/thread/tss_${SRC_PLAT}.h
    
    src/thread/mutex.cpp
    src/thread/mutex_${SRC_PLAT}.cpp
    src/thread/thread_${SRC_PLAT}.cpp
    src/thread/tss_${SRC_PLAT}.cpp
)

if (WIN32)
  source_group("OS" FILES ${node_OS_SRC})
  source_group("Base" FILES ${node_Base_SRC})
  source_group("Thread" FILES ${node_Thread_SRC})
endif()

#------------------------------------------------------------------------------
add_library(node STATIC
  ${node_OS_SRC}
  ${node_Base_SRC}
  ${node_Thread_SRC}
)