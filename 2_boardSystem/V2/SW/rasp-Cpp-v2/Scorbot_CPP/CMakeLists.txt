cmake_minimum_required(VERSION 3.1)
project(pidClassDemo)

set(CMAKE_CXX_STANDARD 11)

set(HEADERS SPILib/SpiPack.h SPILib/SpiRaspInterface.h)
set(SOURCE SPILib/SpiPack.cpp SPILib/SpiRaspInterface.cpp)

add_executable(Scorebot_CPP main.cpp ${HEADERS} ${SOURCE})
