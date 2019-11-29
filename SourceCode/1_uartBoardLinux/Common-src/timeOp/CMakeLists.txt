#definisco da quali file è composta la libreria

if (NOT TARGET timeOp)
    add_library(timeOp
            timeSpecOp.h timerSpecOp.cpp
            )

    #aggiunge la libreria/eseguibile in modalità INTERFACE|PUBLIC|PRIVATE alla INCLUDE_DIRECTORIES property
    target_include_directories(timeOp PUBLIC ".")
endif ()
