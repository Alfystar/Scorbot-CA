if (NOT TARGET qcustomplot)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)


    if (CMAKE_VERSION VERSION_LESS "3.7.0")
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
    endif ()

    add_library(qcustomplot #SHARED
            qcustomplot.h qcustomplot.cpp
            )

    #su qt creator da errore???
    target_link_directories(qcustomplot PUBLIC ".")
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    target_link_libraries(qcustomplot Qt5::Widgets)

    find_package(Qt5PrintSupport REQUIRED)
    target_link_libraries(qcustomplot Qt5::PrintSupport)


    message("La libreria 'qcustomplot' è stata aggiunta")
endif ()