cmake_minimum_required(VERSION 3.1)

add_library(pidCtrl
        PIDScorbot.h PIDScorbot.cpp
        )

target_include_directories(pidCtrl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
