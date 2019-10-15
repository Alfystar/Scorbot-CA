cmake_minimum_required(VERSION 3.1)
project(SpiRasp_Terminal)

set(CMAKE_CXX_STANDARD 11)

set(HEADERS ../DataTransfertPackge/DataManipolation/Pack.h ../ScorbotRaspLib/SPILib/SpiRaspInterface.h ../ScorbotRaspLib/UtilityScorbot/ScorCalc.h ../DataTransfertPackge/DataPrimitive.h ../DataTransfertPackge/DataManipolation/typePackWrongExcept.h ../DataTransfertPackge/DataManipolation/SpeedMot.cpp ../DataTransfertPackge/DataManipolation/SpeedMot.h ../DataTransfertPackge/DataManipolation/SettingBoard_C.cpp ../DataTransfertPackge/DataManipolation/SettingBoard_C.h)
set(SOURCE ../DataTransfertPackge/DataManipolation/Pack.cpp ../ScorbotRaspLib/SPILib/SpiRaspInterface.cpp ../ScorbotRaspLib/UtilityScorbot/ScorCalc.cpp ../DataTransfertPackge/DataManipolation/typePackWrongExcept.h ../DataTransfertPackge/DataFactory.cpp ../DataTransfertPackge/DataFactory.h ../DataTransfertPackge/DataManipolation/SpeedMot.cpp ../DataTransfertPackge/DataManipolation/SpeedMot.h ../DataTransfertPackge/DataManipolation/SettingBoard_C.cpp ../DataTransfertPackge/DataManipolation/SettingBoard_C.h ../DataTransfertPackge/DataManipolation/CurrentMot.cpp ../DataTransfertPackge/DataManipolation/CurrentMot.h ../DataTransfertPackge/DataManipolation/EncoderMot.cpp ../DataTransfertPackge/DataManipolation/EncoderMot.h ../DataTransfertPackge/DataManipolation/AllSensor.cpp ../DataTransfertPackge/DataManipolation/AllSensor.h)
add_executable(${PROJECT_NAME} main.cpp ${HEADERS} ${SOURCE})


#include(../ScorbotRaspLib/CMakeLists.txt)
#include_directories(../ScorbotRaspLib)
#link_directories(../ScorbotRaspLib)

#add_executable(${PROJECT_NAME} main.cpp)

#Copy only on rapsberry CMakeList this line, on other linux Computer may make error
#add_definitions(-DONLYRaspCompiling)
#find_library(wiringPi_lib wiringPi)
#target_link_libraries(${PROJECT_NAME} ${wiringPi_lib})
