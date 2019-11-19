cmake_minimum_required(VERSION 3.1)

message("Sono Unix?: ${UNIX}")
message("Sono WIN32?: ${WIN32}")
message("Sono WINDOWS_PHONE?: ${WINDOWS_PHONE}")
message("Sono ANDROID?: ${ANDROID}")
message("Sono APPLE?: ${APPLE}")

project("py2c")
add_subdirectory(Common-src/DataTransfertPackge)
add_subdirectory(comLib)

#add executable
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC interProcessCom)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)