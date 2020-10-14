# Le librerie Comuni DEVONO essere PRE-Incluse
get_filename_component(libName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (NOT TARGET ${libName})
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)


    if (CMAKE_VERSION VERSION_LESS "3.7.0")
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
    endif ()

    # Per installare i pacchetti necessari se serve:
    # sudo apt install qt5-d* qtbase5-dev qtdeclarative5-dev qttools5-dev-tools
    # sudo apt install libqwt-qt5-*
    # sudo apt install libqwtmathml-qt5-*
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    find_package(Qt5PrintSupport REQUIRED)
    list(APPEND RESOURCES ui_source/imgs.qrc)
    qt5_add_resources(RCC_SOURCES ${RESOURCES})



    add_library(${libName} #SHARED
            mainwindow.h mainwindow.cpp ui_source/mainwindow.ui ${RCC_SOURCES}
            settingBoardWindow.h settingBoardWindow.cpp ui_source/settingBoardWindow.ui
            freeMoveWindow.h freeMoveWindow.cpp ui_source/freeMoveWindow.ui
            uartChoose.h uartChoose.cpp ui_source/uartChoose.ui

            qcustomplot/qcustomplot.h qcustomplot/qcustomplot.cpp
            )

    target_link_libraries(${libName} PUBLIC Qt5::Widgets)
    target_link_libraries(${libName}  PUBLIC Qt5::PrintSupport)

    target_link_directories(${libName} PUBLIC ".")
    target_include_directories(${libName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_include_directories(${libName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/qcustomplot)



    target_link_libraries(${libName} PUBLIC dataTransfertPrimitive)
    target_link_libraries(${libName} PUBLIC utilityScorbot)


    message("[${libName}] subsystem included")
endif ()