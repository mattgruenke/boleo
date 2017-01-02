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

set( headers
    ${h_dir}/config.hpp
    ${h_dir}/exceptions.hpp
    ${h_dir}/pcl.hpp
    ${h_dir}/safe_call.hpp
)

set( details
    ${h_dir}/detail/common.hpp
)

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

