## Settings ##

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )


## Paths ##

set( incl ${PROJECT_SOURCE_DIR}/include )
set( h_dir ${incl}/boleo )


## What to build ##

set( sources config.cpp error_handling.cpp )
set( headers ${h_dir}/config.hpp ${h_dir}/error_handling.hpp ${h_dir}/pcl.hpp ${h_dir}/common.hpp )
add_library( boleo ${sources} )
target_link_libraries( boleo ${TANGO_SDK_LIBRARY} )


## How to build it ##

include_directories( ${incl} ${TANGO_SDK_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS} )


## Where to install it ##

install( TARGETS boleo DESTINATION lib )
install( FILES ${headers} DESTINATION include/boleo )

