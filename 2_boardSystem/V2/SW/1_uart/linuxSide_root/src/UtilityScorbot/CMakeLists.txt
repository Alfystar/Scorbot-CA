#definisco da quali file è composta la libreria
add_library(scoreUtiliy
        ScorCalc.h ScorCalc.cpp
        )

#aggiunge la libreria/eseguibile in modalità INTERFACE|PUBLIC|PRIVATE alla INCLUDE_DIRECTORIES property
target_include_directories(scoreUtiliy PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(scoreUtiliy PUBLIC dataTransfert)