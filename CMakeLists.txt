cmake_minimum_required( VERSION 3.5 )

project( passgen )
set( CMAKE_CXX_STANDARD 11 )

set( CMAKE_CXX_VISIBLITY_PRESET hidden )
set( CMAKE_VISIBILITY_INLINES_HIDDEN 1 )

find_package( OpenSSL REQUIRED )

set( PWGEN_SRC_FILES
     passgen.cpp
     pgrandom.c
     pgrandom.h
     strutil.cpp
     strutil.h
)

add_executable( passgen ${PWGEN_SRC_FILES} )
target_include_directories( passgen PRIVATE "." )

if( WIN32 )
    install( TARGETS passgen EXPORT passgen
             RUNTIME DESTINATION bin
             LIBRARY DESTINATION bin
             ARCHIVE DESTINATION lib
    )

    install( FILES $<TARGET_PDB_FILE:passgen> DESTINATION bin OPTIONAL )
else()
    install( TARGETS passgen EXPORT passgen
             RUNTIME DESTINATION bin
             LIBRARY DESTINATION lib
             ARCHIVE DESTINATION lib
    )
endif()

