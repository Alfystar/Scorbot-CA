cmake_minimum_required(VERSION 3.1)
project(SpiRasp_Terminal)

set(CMAKE_CXX_STANDARD 11)

set(HEADERS ../SpiPack/SpiPack.h ../ScorbotRaspLib/SPILib/SpiRaspInterface.h ../ScorbotRaspLib/UtilityScorbot/ScorCalc.h)
set(SOURCE ../SpiPack/SpiPack.cpp ../ScorbotRaspLib/SPILib/SpiRaspInterface.cpp ../ScorbotRaspLib/UtilityScorbot/ScorCalc.cpp)
add_executable(${PROJECT_NAME} main.cpp ${HEADERS} ${SOURCE})


#include(../ScorbotRaspLib/CMakeLists.txt)
#include_directories(../ScorbotRaspLib)
#link_directories(../ScorbotRaspLib)

#add_executable(${PROJECT_NAME} main.cpp)

#Copy only on rapsberry CMakeList this line, on other linux Computer may make error
#add_definitions(-DONLYRaspCompiling)
#find_library(wiringPi_lib wiringPi)
#target_link_libraries(${PROJECT_NAME} ${wiringPi_lib})
