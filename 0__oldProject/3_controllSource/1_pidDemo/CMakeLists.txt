cmake_minimum_required(VERSION 3.1)
project(pidClassDemo)

set(CMAKE_CXX_STANDARD 11)

set(HEADERS PidClass/PIDScorbot.h SPILib/spi_scorebot_packdefine.h SPILib/spisend.h)
set(SOURCE PidClass/PIDScorbot.cpp SPILib/spisend.cpp)

add_executable(pidClassDemo main.cpp ${HEADERS} ${SOURCE})
