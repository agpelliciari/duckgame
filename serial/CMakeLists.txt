
target_sources(taller_serial
    PRIVATE
    # .cpp files
        serializer.cpp
        deserializer.cpp
    PUBLIC
    # .h files
        serializer.h
        deserializer.h
        level_fields.h
    )
