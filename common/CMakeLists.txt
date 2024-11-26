add_subdirectory(core/)

target_sources(taller_common
    PRIVATE
    # .cpp files
        clientprotocol.cpp
        serverprotocol.cpp
        protocolerror.cpp
        serialerror.cpp
    PUBLIC
    # .h files
        clientprotocol.h
        serverprotocol.h
        protocolerror.h
        dtosobject.h
        dtosmap.h
        gameevents.h
        dtoslobby.h
        dtosgame.h
        dtosplayer.h
        thread.h
        queue.h
        errors.h
        serialerror.h
    )
