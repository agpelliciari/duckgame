add_subdirectory(logic_server/)
add_subdirectory(simple_logic/)

target_sources(taller_server
    PRIVATE
    # .cpp files
        playeracceptor.cpp
        matchserver.cpp
        lobbycontainer.cpp
        match.cpp
        gameerror.cpp
        playerprotocol.cpp
        playercontainer.cpp
        main.cpp
        controlledplayer.cpp
        controlreceiver.cpp
        controlnotifier.cpp
         

    PUBLIC
    # .h files
        playerprotocol.h
        match.h
        playeracceptor.h
        lobbycontainer.h
        playercontainer.h
        gameerror.h
        matchserver.h
        controlreceiver.h
        controlledplayer.h
        controlnotifier.h
    )
