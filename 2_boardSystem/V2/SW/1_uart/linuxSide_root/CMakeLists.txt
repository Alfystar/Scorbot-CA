cmake_minimum_required(VERSION 3.1)

message("Sono Unix?: ${UNIX}")
message("Sono WIN32?: ${WIN32}")
message("Sono WINDOWS_PHONE?: ${WINDOWS_PHONE}")
message("Sono ANDROID?: ${ANDROID}")
message("Sono APPLE?: ${APPLE}")

project(pcListenUart)
message("Creato Progetto: ${PROJECT_NAME}")

add_subdirectory(src)

#Exe directory
add_subdirectory(pcListen_demo)
message("Caricate le impostazioni per l'eseguibile di pcListen_demo")


# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)