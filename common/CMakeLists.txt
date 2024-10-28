add_subdirectory(core/)

target_sources(taller_common
    PRIVATE
    # .cpp files
        clientprotocol.cpp
        serverprotocol.cpp
        protocolerror.cpp
    PUBLIC
    # .h files
        clientprotocol.h
        serverprotocol.h
        protocolerror.h
        dtos.h
        dtosplayer.h
        dtosobject.h
        thread.h
        queue.h
        
    )
