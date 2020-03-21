if (NOT TARGET scorbotUi)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)


    if (CMAKE_VERSION VERSION_LESS "3.7.0")
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
    endif ()

    add_library(scorbotUi #SHARED
            commonDefine.h
            mainwindow.h mainwindow.cpp ui_source/mainwindow.ui ui_source/logo.qrc
            settingBoardWindow.h settingBoardWindow.cpp ui_source/settingBoardWindow.ui
            freeMoveWinsow.h freeMoveWinsow.cpp ui_source/freeMoveWindow.ui
            uartChoise.h uartChoise.cpp ui_source/uartChoise.ui
            )

    #su qt creator da errore???
    target_link_directories(scorbotUi PUBLIC ".")

    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    target_link_libraries(scorbotUi Qt5::Widgets)

#    find_package(Qt5 COMPONENTS Widgets REQUIRED)
#    target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

    target_link_libraries(scorbotUi dataTransfert)
    target_link_libraries(scorbotUi scoreUtiliy)

    #set_property(TARGET scorbotUi PROPERTY POSITION_INDEPENDENT_CODE ON)

    message("La libreria 'scorbotUi' è stata aggiunta")
endif ()