if (NOT TARGET scorbotUi)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)


    if (CMAKE_VERSION VERSION_LESS "3.7.0")
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
    endif ()

    add_library(scorbotUi #SHARED
            mainwindow.h mainwindow.cpp ui_source/mainwindow.ui ui_source/logo.qrc
            settingBoardWindow.h settingBoardWindow.cpp ui_source/settingBoardWindow.ui
            freeMoveWindow.h freeMoveWindow.cpp ui_source/freeMoveWindow.ui
            uartChoise.h uartChoise.cpp ui_source/uartChoise.ui
            )

    #su qt creator da errore???
    target_link_directories(scorbotUi PUBLIC ".")

    # Per installare i pacchetti necessari se serve:
    # sudo apt install qt5-d* qtbase5-dev qtdeclarative5-dev qttools5-dev-tools
    # sudo apt install libqwt-qt5-*
    # sudo apt install libqwtmathml-qt5-*
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    target_link_libraries(scorbotUi Qt5::Widgets)

    #    find_package(Qwt)
    #
    #    if (QWT_INCLUDE_DIR AND QWT_LIBRARY)
    #        SET(QWT_FOUND TRUE)
    #    ENDIF (QWT_INCLUDE_DIR AND QWT_LIBRARY)
    #
    #    if (QWT_FOUND)
    #        if (NOT QWT_FIND_QUIETLY)
    #            MESSAGE(STATUS "Found QWT: ${QWT_LIBRARY}")
    #        endif (NOT QWT_FIND_QUIETLY)
    #    else (QWT_FOUND)
    #        if (QWT_FIND_REQUIRED)
    #            MESSAGE(FATAL_ERROR "Could not find QWT")
    #        endif (QWT_FIND_REQUIRED)
    #    endif (QWT_FOUND)
    #    find_package(QwtConfig COMPONENTS REQUIRED)
    #    target_link_libraries(scorbotUi PUBLIC ${QWT_LIBRARY})
    #    target_link_directories(scorbotUi PUBLIC ${QWT_INCLUDE_DIR})
    #    message("qwt: ${QWT_FOUND}")

    target_link_libraries(scorbotUi dataTransfert)
    target_link_libraries(scorbotUi scoreUtiliy)

    #set_property(TARGET scorbotUi PROPERTY POSITION_INDEPENDENT_CODE ON)

    message("La libreria 'scorbotUi' è stata aggiunta")
endif ()