#definisco da quali file è composta la libreria
add_library(interProcessCom
        comLib.h comLib.cpp
        )
#aggiunge la libreria/eseguibile in modalità INTERFACE|PUBLIC|PRIVATE alla INCLUDE_DIRECTORIES property
target_include_directories(interProcessCom PUBLIC .)

#Includo le librerie di cui ho busogno
target_link_libraries(interProcessCom PUBLIC dataTransfert)
find_package(Threads)
target_link_libraries(interProcessCom PUBLIC ${CMAKE_THREAD_LIBS_INIT})

message("La libreria 'interProcessCom' è stata aggiunta")
message("CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_THREAD_LIBS_INIT})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
