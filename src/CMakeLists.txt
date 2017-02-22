## Settings ##

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )


## Paths ##

set( incl ${PROJECT_SOURCE_DIR}/include )
set( h_dir ${incl}/boleo )


## What to build ##

set( sources
    config.cpp
    exceptions.cpp
)

file( GLOB headers
    LIST_DIRECTORIES false
    ${h_dir}/* )

file( GLOB details
    LIST_DIRECTORIES false
    ${h_dir}/detail/* )

add_library( boleo ${sources} )

if( ${LinkWithExternalLibs} )
    target_link_libraries( boleo ${TANGO_SDK_LIBRARY} )
endif()


## How to build it ##

include_directories(
    ${incl}
    ${TANGO_SDK_INCLUDE_DIRS}
    ${PCL_INCLUDE_DIRS}
)

# Enable this, if/when PCL support ceases to be header-only.  Even then, 
#  perhaps make it optional and conditionally compile pcl.cpp.
#
#find_package( PCL 1.3 REQUIRED )
#include_directories( ${PCL_INCLUDE_DIRS} )
#link_directories( ${PCL_LIBRARY_DIRS} )
#add_definitions( ${PCL_DEFINITIONS} )


## Where to install it ##

install(
    TARGETS boleo
    DESTINATION lib )

install(
    FILES ${headers}
    DESTINATION include/boleo )

install(
    FILES ${details}
    DESTINATION include/boleo/detail )

