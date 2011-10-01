add_executable (lion
    main.cpp
    ConsoleApplication.cpp
    # InputThread.cpp
)
FIND_PACKAGE(Boost COMPONENTS thread system signals)

# target_link_libraries (lion lionheart lionheart_core boost_date_time-xgcc42-mt boost_system-xgcc42-mt boost_thread-xgcc42-mt)
# target_link_libraries (lion lionheart lionheart_core ${Boost_date_LIBRARY} ${Boost_system_LIBRARY}
#    ${Boost_thread_LIBRARY})
link_directories ( ${Boost_LIBRARY_DIRS} )
target_link_libraries (lion lionheart lionheart_core ${Boost_LIBRARIES})
install (TARGETS lion
    RUNTIME DESTINATION bin
)
