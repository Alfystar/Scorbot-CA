if (NOT TARGET scorbotUi)
    #    add_subdirectory(qcustomplot)

    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)


    if (CMAKE_VERSION VERSION_LESS "3.7.0")
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
    endif ()

    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    find_package(Qt5PrintSupport REQUIRED)

    list(APPEND RESOURCES ui_source/imgs.qrc)
    qt5_add_resources(RCC_SOURCES ${RESOURCES})

    add_library(scorbotUi #SHARED
            mainwindow.h mainwindow.cpp ui_source/mainwindow.ui ${RCC_SOURCES}
            settingBoardWindow.h settingBoardWindow.cpp ui_source/settingBoardWindow.ui
            freeMoveWindow.h freeMoveWindow.cpp ui_source/freeMoveWindow.ui
            uartChoise.h uartChoise.cpp ui_source/uartChoise.ui

            qcustomplot/qcustomplot.h qcustomplot/qcustomplot.cpp
            )

    #su qt creator da errore???
    target_link_directories(scorbotUi PUBLIC ".")
    target_include_directories(scorbotUi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_include_directories(scorbotUi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/qcustomplot)
    #    message("${CMAKE_CURRENT_SOURCE_DIR}")

    # Per installare i pacchetti necessari se serve:
    # sudo apt install qt5-d* qtbase5-dev qtdeclarative5-dev qttools5-dev-tools
    # sudo apt install libqwt-qt5-*
    # sudo apt install libqwtmathml-qt5-*
    target_link_libraries(scorbotUi PUBLIC Qt5::Widgets)
    target_link_libraries(scorbotUi PUBLIC Qt5PrintSupport)

    target_link_libraries(scorbotUi PUBLIC dataTransfert)
    target_link_libraries(scorbotUi PUBLIC scoreUtiliy)


    message("La libreria 'scorbotUi' è stata aggiunta")
endif ()