
add_executable (lion main.cpp)

target_link_libraries (lion lionheart lionheart_core)
install (TARGETS lion
    RUNTIME DESTINATION bin
)