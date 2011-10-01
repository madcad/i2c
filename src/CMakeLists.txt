
add_subdirectory (core)
add_subdirectory (net)
add_subdirectory (io)

add_library (lionheart
    Exceptions.cpp
    # LogSink.cpp
    # Log.cpp
    OptionParser.cpp
)


FIND_PACKAGE(Boost COMPONENTS thread system signals date_time)

link_directories ( ${Boost_LIBRARY_DIRS} )
target_link_libraries (lionheart lionheart_core ${Boost_LIBRARIES})
