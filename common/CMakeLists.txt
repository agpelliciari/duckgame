add_subdirectory(core/)

target_sources(taller_common
    PRIVATE
    # .cpp files
        clientprotocol.cpp
        playerprotocol.cpp
        protocolerror.cpp
    PUBLIC
    # .h files
        clientprotocol.h
        playerprotocol.h
        protocolerror.h
        dtos.h
        dtosplayer.h
        thread.h
        queue.h
        
    )
