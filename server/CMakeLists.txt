add_subdirectory(logic_server/)
add_subdirectory(simple_logic/)

target_sources(taller_server
    PRIVATE
    # .cpp files
        playernotifier.cpp
        playeracceptor.cpp
        matchserver.cpp
        lobbycontainer.cpp
        match.cpp
        gameerror.cpp
        controlledplayer.cpp
        controlreceiver.cpp
        playerprotocol.cpp
        playercontainer.cpp
        main.cpp
         

    PUBLIC
    # .h files
        playerprotocol.h
        match.h
        playeracceptor.h
        lobbycontainer.h
        playernotifier.h
        playercontainer.h
        gameerror.h
        matchserver.h
        controlreceiver.h
        controlledplayer.h
    )
