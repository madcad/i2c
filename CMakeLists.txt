project (Lionheart)
cmake_minimum_required (VERSION 2.6)
set(Boost_ADDITIONAL_VERSIONS "1.47" "1.47.0")
FIND_PACKAGE(Boost COMPONENTS thread)
# make it easy to locate CMake modules for finding libraries
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CmakeModules/")

include_directories ("${PROJECT_SOURCE_DIR}/src")
# include_directories ("${PROJECT_SOURCE_DIR}/libs/lua/src")
# link_directories ("${PROJECT_SOURCE_DIR}/shared_content/lib/macosx")
IF (Boost_FOUND)
    include_directories (${Boost_INCLUDE_DIRS})
    link_directories (${Boost_LIBRARY_DIRS})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()
message(STATUS "BOOST INC=${Boost_INCLUDE_DIRS}")
message(STATUS "BOOST LIB=${Boost_LIBRARY_DIRS}")

#add_executable (lionheart main.cpp
#    src/Exceptions.cpp
#    src/LogSink.cpp
#    src/Log.cpp
#    src/OptionParser.cpp
#)
# add_subdirectory (libs)
add_subdirectory (config-c--)
add_subdirectory (src)
add_subdirectory (demo)

