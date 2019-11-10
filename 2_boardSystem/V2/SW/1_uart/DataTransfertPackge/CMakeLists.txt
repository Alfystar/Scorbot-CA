#definisco da quali file è composta la libreria
add_library(dataTransfert SHARED
        DataPrimitive.h
        DataFactory.h
        DataFactory.cpp
        DataManipolation/AllSensor.h
        DataManipolation/AllSensor.cpp
        DataManipolation/CurrentMot.h
        DataManipolation/CurrentMot.cpp
        DataManipolation/EncoderMot.h
        DataManipolation/EncoderMot.cpp
        DataManipolation/SpeedMot.h
        DataManipolation/SpeedMot.cpp
        DataManipolation/SettingBoard_C.h
        DataManipolation/SettingBoard_C.cpp
        )

#aggiunge la libreria/eseguibile in modalità INTERFACE|PUBLIC|PRIVATE alla INCLUDE_DIRECTORIES property
target_include_directories(dataTransfert PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/DataTransfertPackge")
target_compile_definitions(dataTransfert PUBLIC version_D=5)