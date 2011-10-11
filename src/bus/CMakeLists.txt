set(LIBUSB_FIND_REQUIRED, true)
find_package(Libusb)
find_package(Boost COMPONENTS thread)
add_library (lionheart_bus
    I2CDevice.cpp
)

target_link_libraries(lionheart_bus lionheart ${LIBUSB_LIBRARIES} ${Boost_LIBRARIES})
