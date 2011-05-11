project (Lionheart)
cmake_minimum_required (VERSION 2.6)
include_directories ("${PROJECT_SOURCE_DIR}/shared_content/include")
include_directories ("${PROJECT_SOURCE_DIR}/src")
link_directories ("${PROJECT_SOURCE_DIR}/shared_content/lib/macosx")


#add_executable (lionheart main.cpp
#    src/Exceptions.cpp
#    src/LogSink.cpp
#    src/Log.cpp
#    src/OptionParser.cpp
#)
add_subdirectory (libs)
add_subdirectory (src)
add_subdirectory (demo)

