    add_subdirectory(UI_useCase)
    if (NOT TARGET scorbotMainWindows)
        set(CMAKE_AUTOMOC ON)
        set(CMAKE_AUTORCC ON)
        set(CMAKE_AUTOUIC ON)
        set(CMAKE_INCLUDE_CURRENT_DIR ON)


        if (CMAKE_VERSION VERSION_LESS "3.7.0")
            set(CMAKE_INCLUDE_CURRENT_DIR ON)
        endif ()

        add_library(scorbotMainWindows #SHARED
                ScorbotMainWindows.h ScorbotMainWindows.cpp
                ## Aggiunta classi USE CASE ##
                )

        ## qt target
        #su qt creator da errore???
        target_include_directories(scorbotMainWindows PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
        find_package(Qt5 COMPONENTS Widgets REQUIRED)
        target_link_libraries(scorbotMainWindows PUBLIC Qt5::Widgets)

        ## System target
        target_link_libraries(scorbotMainWindows PUBLIC UI_useCase)

        message("La libreria 'scorbotMainWindows' è stata aggiunta")
    endif ()