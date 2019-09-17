cmake_minimum_required(VERSION 3.1)
project(SpiRasp_Terminal)

set(CMAKE_CXX_STANDARD 11)

set(HEADERS ../SpiPack/SpiPack.h SPILib/SpiRaspInterface.h)
set(SOURCE ../SpiPack/SpiPack.cpp SPILib/SpiRaspInterface.cpp)

add_executable(PROJECT_NAME main.cpp ${HEADERS} ${SOURCE})
find_library(wiringPi_lib wiringPi)
target_link_libraries(PROJECT_NAME ${wiringPi_lib})
