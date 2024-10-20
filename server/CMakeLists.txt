add_subdirectory(logic_server/)
add_subdirectory(simple_logic/)

target_sources(taller_server
    PRIVATE
    # .cpp files
        server.cpp
        main.cpp
        gameerror.cpp
        lobbycontainer.cpp
        match.cpp
        playeracceptor.cpp
        playerprotocol.cpp
        playercontainer.cpp
        controlledplayer.cpp
        controlreceiver.cpp
        controlnotifier.cpp
         

    PUBLIC
    # .h files
        server.h
        gameerror.h
        match.h
        lobbycontainer.h
        playerprotocol.h
        playeracceptor.h
        playercontainer.h
        controlreceiver.h
        controlledplayer.h
        controlnotifier.h
    )
