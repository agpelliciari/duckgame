target_sources(taller_common
    PRIVATE
    # .cpp files
        resolver.cpp
        socket.cpp
        liberror.cpp
        resolvererror.cpp
        protocol.cpp
    PUBLIC
    # .h files
        dtos.h
        dtosplayer.h
        resolver.h
        socket.h
        liberror.h
        protocol.h
        resolvererror.h
        thread.h
        queue.h

    )
