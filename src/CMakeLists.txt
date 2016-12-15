## Settings ##

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )


## What to build ##

set( sources config.cpp error_handling.cpp )
set( headers config.hpp error_handling.hpp )
add_library( boleo ${sources} )
#target_link_libraries( boleo ${TANGO_SDK_LIBRARY} )


## How to build it ##

include_directories( ${TANGO_SDK_INCLUDE_DIRS} )


## Where to install it ##

install( TARGETS boleo DESTINATION lib )
install( FILES ${headers} DESTINATION include )

