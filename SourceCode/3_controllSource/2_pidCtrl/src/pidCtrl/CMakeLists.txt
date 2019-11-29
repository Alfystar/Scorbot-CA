if (NOT TARGET pidCtrl)
    add_library(pidCtrl
            PIDScorbot.h PIDScorbot.cpp
            )

    target_include_directories(pidCtrl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(pidCtrl PUBLIC dataTransfert)
    target_link_libraries(pidCtrl PUBLIC timeOp)
    message("La libreria 'pidCtrl' è stata aggiunta")
endif ()
