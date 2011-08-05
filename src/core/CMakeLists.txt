FIND_PACKAGE(Curses)

IF (CURSES_FOUND)
    include_directories (${CURSES_INCLUDE_DIR})
    ADD_DEFINITIONS ( "-DHAS_CURSES")
ENDIF()

add_library (lionheart_core
    Application.cpp
    ConsoleApplication.cpp
    LogSink.cpp
    Log.cpp
    Singleton.cpp
)

target_link_libraries(lionheart_core lionheart ${CURSES_LIBRARIES})
