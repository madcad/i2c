
add_subdirectory (core)

add_library (lionheart
    Exceptions.cpp
    LogSink.cpp
    Log.cpp
    OptionParser.cpp
)

target_link_libraries (lionheart lionheart_core liblua)
