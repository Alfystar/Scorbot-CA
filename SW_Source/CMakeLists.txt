#Cmake root of source, here to link all
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DQT_NO_VERSION_TAGGING)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

add_compile_options(-Wall -Wextra -pedantic)
message("Platform type Unix : ${UNIX}")
project(ScorbotTerminal)

if(PLOT_ENABLE)
    message("\t>== Current Plot enable ==<")
    add_compile_definitions(PLOT_ON)
else()
    message("\t>== Current Plot disable ==<")
endif()

message(CMAKE_HOME_DIRECTORY = ${CMAKE_HOME_DIRECTORY})
message("Start Include Dirs:\n")
# Load all library
message("/=====================\\")
add_subdirectory(Common-src)
message("\\=====================/")
message("")
message("/=====================\\")
add_subdirectory(Scorbot-V2_UI)
message("\\=====================/")



#GUI exe:
#add_subdirectory(Scorbot-V2_UI)