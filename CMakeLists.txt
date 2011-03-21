cmake_minimum_required (VERSION 2.6)
project (lionheart)

include_directories ("${PROJECT_SOURCE_DIR}/shared_content/include")
include_directories ("${PROJECT_SOURCE_DIR}/include")
link_directories ("${PROJECT_SOURCE_DIR}/shared_content/lib/macosx")


add_executable (lionheart main.cpp src/OptionParser.cpp)

