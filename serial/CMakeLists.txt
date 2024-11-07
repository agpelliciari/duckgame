
target_sources(taller_serial
    PRIVATE
    # .cpp files
        map_serializer.cpp
        map_deserializer.cpp
        map_loader.cpp
    PUBLIC
    # .h files
        map_serializer.h
        map_deserializer.h
        map_loader.h
    )
