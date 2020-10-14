get_filename_component(libName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (NOT TARGET ${libName})
    #definisco da quali file è composta la libreria
    add_library(${libName}
            ScorCalc.h ScorCalc.cpp
            )

    #aggiunge la libreria/eseguibile in modalità INTERFACE|PUBLIC|PRIVATE alla INCLUDE_DIRECTORIES property
    target_include_directories(${libName} PUBLIC ".")
    target_link_libraries(${libName} PUBLIC dataTransfertPrimitive)
    message("[${libName}] subsystem included")
endif ()
