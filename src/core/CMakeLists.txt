add_library (lionheart_core
    Application.cpp
    Command.cpp
    LogSink.cpp
    Log.cpp
    Singleton.cpp
)

target_link_libraries(lionheart_core lionheart)
