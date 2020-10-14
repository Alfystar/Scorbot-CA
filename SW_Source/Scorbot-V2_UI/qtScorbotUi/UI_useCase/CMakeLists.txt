# Le librerie Comuni DEVONO essere PRE-Incluse
get_filename_component(libName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (NOT TARGET ${libName})
    add_subdirectory(scorbotUi)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)


    if (CMAKE_VERSION VERSION_LESS "3.7.0")
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
    endif ()

    add_library(${libName} STATIC #SHARED
            ## Aggiunta classi USE CASE ##
            UartConnect.h UartConnect.cpp UartConnectExeption.h
            MotorCTRL.h MotorCTRL.cpp
            DataShow.h DataShow.cpp
            SetupBoard.h SetupBoard.cpp
            )

    ## qt target
    #su qt creator da errore???
    target_include_directories(${libName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    target_link_libraries(${libName} PUBLIC Qt5::Widgets)

    find_package(Qt5PrintSupport REQUIRED)
    target_link_libraries(${libName} PUBLIC Qt5::PrintSupport)

    ## System target
    target_link_libraries(${libName} PUBLIC scorbotUi)
    target_link_libraries(${libName} PUBLIC dataTransfertPrimitive)
    target_link_libraries(${libName} PUBLIC uartSubSystem)
    target_link_libraries(${libName} PUBLIC ctrlSrc)

    message("[${libName}] subsystem included")
endif ()