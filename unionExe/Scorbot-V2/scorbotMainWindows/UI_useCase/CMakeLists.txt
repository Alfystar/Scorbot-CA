add_subdirectory(uiSrc)

if (NOT TARGET UI_useCase)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)


    if (CMAKE_VERSION VERSION_LESS "3.7.0")
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
    endif ()

    add_library(UI_useCase #SHARED
            ## Aggiunta classi USE CASE ##
            UartConnect.h UartConnect.cpp UartConnectExeption.h
            MotorCTRL.h MotorCTRL.cpp
            DataShow.h DataShow.cpp
            SetupBoard.h SetupBoard.cpp
            )

    ## qt target
    #su qt creator da errore???
    target_include_directories(UI_useCase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    target_link_libraries(UI_useCase PUBLIC Qt5::Widgets)

    find_package(Qt5PrintSupport REQUIRED)
    target_link_libraries(UI_useCase PUBLIC Qt5::PrintSupport)

    ## System target
    target_link_libraries(UI_useCase PUBLIC scorbotUi)
    target_link_libraries(UI_useCase PUBLIC dataTransfert)
    target_link_libraries(UI_useCase PUBLIC UartSubSystem)
    target_link_libraries(UI_useCase PUBLIC pidCtrl)

    message("La libreria 'UI_useCase' è stata aggiunta")
endif ()