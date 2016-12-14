## Finds TangoSDK
#
# Sets:
#   TANGO_SDK_INCLUDE_DIRS - must be added to include path to use TangoSDK.
#   TANGO_SDK_LIBRARY - library implementing TangoSDK.
#   TangoSDK_FOUND - Set if the dependencies were found.
#
# TBD:
#   TANGO_SDK_VERSION - indicates version of TangoSDK

find_path( TANGO_SDK_INCLUDE_DIRS tango_client_api.h )

find_library( TANGO_SDK_LIBRARY tango_client_api )

    # For now, ignore whether library is found.
if( EXISTS ${TANGO_SDK_INCLUDE_DIRS} )
    set( TangoSDK_FOUND TRUE )
endif()

