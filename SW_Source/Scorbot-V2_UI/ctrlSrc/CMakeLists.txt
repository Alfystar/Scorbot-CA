# Le librerie Comuni DEVONO essere PRE-Incluse
get_filename_component(libName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (NOT TARGET ${libName})
    add_library(${libName}
            ctrlSource.h ctrlSource.cpp
            )
    target_include_directories(${libName} PUBLIC ".")

    add_subdirectory(pidCtrl)
    target_link_libraries(${libName} PUBLIC pidCtrl)

    target_link_libraries(${libName} PUBLIC dataTransfertPrimitive)
    target_link_libraries(${libName} PUBLIC uartSubSystem)
    target_link_libraries(${libName} PUBLIC timeOp)
    message("[${libName}] subsystem included")
endif ()
