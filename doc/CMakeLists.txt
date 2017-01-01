cmake_minimum_required( VERSION 3.1 )

find_package( Doxygen )

if( DOXYGEN_FOUND )

    set( doxygen_cfg_in ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.cfg.in )
    set( doxygen_cfg ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg )
    configure_file( ${doxygen_cfg_in} ${doxygen_cfg} @ONLY )

    add_custom_target( doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxygen_cfg}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API docs"
        VERBATIM )

    install(
        DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
        DESTINATION share/doc/boleo
        OPTIONAL )

else()

    message( WARNING "Doxygen not found: no doc target created." )

endif()


install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/../README.md
    DESTINATION share/doc/boleo )

