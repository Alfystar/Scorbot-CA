set(RaspHEADERS ../DataTransfertPackge/DataManipolation/Pack.h SPILib/SpiRaspInterface.h UtilityScorbot/ScorCalc.h)
set(RaspSOURCE ../DataTransfertPackge/DataManipolation/Pack.cpp SPILib/SpiRaspInterface.cpp UtilityScorbot/ScorCalc.cpp)

add_executable(${PROJECT_NAME} ${RaspHEADERS} ${RaspSOURCE})


#add_library(raspLib ${SOURCE})
#target_include_directories (raspLib PUBLIC ${SOURCE})

#Copy only on rapsberry CMakeList this line, on other linux Computer may make error
#add_definitions(-DONLYRaspCompiling)
#find_library(wiringPi_lib wiringPi)
#target_link_libraries(${PROJECT_NAME} ${wiringPi_lib})