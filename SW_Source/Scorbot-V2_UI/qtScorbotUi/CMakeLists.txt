# Le librerie Comuni DEVONO essere PRE-Incluse
get_filename_component(libName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (NOT TARGET ${libName})
    add_subdirectory(UI_useCase)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)


    if (CMAKE_VERSION VERSION_LESS "3.7.0")
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
    endif ()

    add_library(${libName} STATIC#SHARED
            QtScorbotUi.h QtScorbotUi.cpp
            )

    ## qt target
    #su qt creator da errore???
    target_include_directories(${libName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    target_link_libraries(${libName} PUBLIC Qt5::Widgets)

    ## System target
    target_link_libraries(${libName} PUBLIC UI_useCase)

    message("[${libName}] subsystem included")
endif ()