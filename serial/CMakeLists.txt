
target_sources(taller_serial
    PRIVATE
    # .cpp files
        map_serializer.cpp
        map_deserializer.cpp
        map_importer.cpp
        map_loader.cpp
        map_reader.cpp
        config_reader.cpp
    PUBLIC
    # .h files
        map_serializer.h
        map_deserializer.h
        map_importer.h
        map_loader.h
        map_reader.h
        config_reader.h
    )
