
add_executable (lion main.cpp)

target_link_libraries (lion lionheart lionheart_core boost_date_time-xgcc42-mt boost_system-xgcc42-mt boost_thread-xgcc42-mt)
install (TARGETS lion
    RUNTIME DESTINATION bin
)
