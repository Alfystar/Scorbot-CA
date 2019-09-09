cmake_minimum_required(VERSION 3.1)
project(SpiRasp_demo)

set(CMAKE_CXX_STANDARD 11)

set(HEADERS ../SpiPack/SpiPack.h SPILib/SpiRaspInterface.h)
set(SOURCE ../SpiPack/SpiPack.cpp SPILib/SpiRaspInterface.cpp)

add_executable(SpiRasp_demo main.cpp ${HEADERS} ${SOURCE})
