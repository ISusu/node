# Libevent_FOUND
# Libevent_INCLUDE_DIR
# Libevent_LIBRARY
# Libevent_LIBRARY_CORE
# Libevent_LIBRARY_EXTRAS
# Libevent_LIBRARYS

if (WIN32)
  set(Libevent_HOME "$ENV{LIBEVENT_HOME}")
elseif(UNIX)
  set(Libevent_HOME "")
endif(WIN32)

find_path(Libevent_INCLUDE_DIR
  NAMES
    event2/event.h
  PATHS
    ${Libevent_HOME}
    /usr/local/include
  PATH_SUFFIXES
    include
  DOC
  "Specify the directory containing event.h."
)

find_library( Libevent_LIBRARY
  NAMES
    libevent event
  PATHS
    ${Libevent_HOME}
    /usr/local/lib
  PATH_SUFFIXES
    lib
  DOC "Specify the location of the libevent library here."
)

find_library( Libevent_LIBRARY_CORE
  NAMES
    libevent_core event_core
  PATHS
    ${Libevent_HOME}
    /usr/local/lib
  PATH_SUFFIXES
    lib
  DOC "Specify the location of the libevent core library here."
)

find_library( Libevent_LIBRARY_EXTRAS
  NAMES
    libevent_extras event_extras
  PATHS
    ${Libevent_HOME}
    /usr/local/lib
  PATH_SUFFIXES
    lib
  DOC "Specify the location of the libevent extras library here."
)

if (NOT Libevent_INCLUDE_DIR)
  message(FATAL_ERROR "Can not found libevent.")
endif()

if (NOT Libevent_LIBRARY)
  message(FATAL_ERROR "Can not found libevent.")
endif()

message(STATUS "Found Libevent headers: " ${Libevent_INCLUDE_DIR})
message(STATUS "Found Libevent library: " ${Libevent_LIBRARY})

set(Libevent_LIBRARYS ${Libevent_LIBRARY} ${Libevent_LIBRARY_CORE} ${Libevent_LIBRARY_EXTRAS})
set(Libevent_FOUND TRUE)
