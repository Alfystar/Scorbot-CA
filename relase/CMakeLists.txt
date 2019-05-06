cmake_minimum_required(VERSION 3.1)
project(scorbot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_STANDARD 11)

set(HEADERS PidClass/PIDScorbot.h SPILib/spi_scorebot_packdefine.h SPILib/spisend.h comC/comC.h)
set(SOURCE PidClass/PIDScorbot.cpp SPILib/spisend.cpp comC/comC.cpp)

add_executable(scorbot main.cpp ${HEADERS} ${SOURCE})
target_link_libraries (scorbot ${CMAKE_THREAD_LIBS_INIT})
