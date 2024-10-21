add_subdirectory(core/)

target_sources(taller_common
    PRIVATE
    # .cpp files
        clientprotocol.cpp
        playerprotocol.cpp
        protocolerror.cpp
        protocol.cpp
    PUBLIC
    # .h files
        clientprotocol.h
        playerprotocol.h
        protocolerror.h
        protocol.h
        dtos.h
        dtosplayer.h
    )
