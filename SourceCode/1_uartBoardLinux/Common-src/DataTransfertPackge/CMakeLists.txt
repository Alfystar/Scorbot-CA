#definisco da quali file è composta la libreria
add_library(dataTransfert
        DataTransfert_AllInclude.h     #Header con tutti gli include di questo sotto sistema
        DataPrimitive.h     #File con le definizioni comuni
        DataFactory.h DataFactory.cpp
        DataManipolation/AllSensor.h DataManipolation/AllSensor.cpp
        DataManipolation/CurrentMot.h DataManipolation/CurrentMot.cpp
        DataManipolation/EncoderMot.h DataManipolation/EncoderMot.cpp
        DataManipolation/SpeedMot.h DataManipolation/SpeedMot.cpp
        DataManipolation/SettingBoard_C.h DataManipolation/SettingBoard_C.cpp
        DataManipolation/Pack.h DataManipolation/Pack.cpp
        )

#aggiunge la libreria/eseguibile in modalità INTERFACE|PUBLIC|PRIVATE alla INCLUDE_DIRECTORIES property
target_include_directories(dataTransfert PUBLIC ".")
message("La libreria 'dataTransfert' è stata aggiunta")
message("CMAKE_CURRENT_SOURCE_DIR:" .)
if (${UNIX})
    target_compile_definitions(dataTransfert PUBLIC linuxSide=1)
endif ()