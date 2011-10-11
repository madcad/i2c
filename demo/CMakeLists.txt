add_executable (lion
    main.cpp
    ConsoleApplication.cpp
    Commands.cpp
)
FIND_PACKAGE(Boost COMPONENTS thread system signals)

link_directories ( ${Boost_LIBRARY_DIRS} )
target_link_libraries (lion lionheart lionheart_core lionheart_io lionheart_bus ${Boost_LIBRARIES})
install (TARGETS lion
    RUNTIME DESTINATION bin
)
