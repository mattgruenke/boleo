cmake_minimum_required( VERSION 3.1 )

project( Boleo
    VERSION 0.0.0 )


## External Dependencies ##

set( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/" ${CMAKE_MODULE_PATH} )

find_package( TangoSDK REQUIRED )
if( NOT TangoSDK_FOUND )
    message( FATAL_ERROR "Required package not found: TangoSDK" )
endif()


## Subdirectories ##

add_subdirectory( src )
add_subdirectory( doc )

