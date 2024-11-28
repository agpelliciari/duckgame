#Se removio mientras no ese usable
add_subdirectory(logic/)
add_subdirectory(core/)

target_sources(taller_server_logic
    PRIVATE
    # .cpp files
        gameerror.cpp
        controlledplayer.cpp
        match.cpp
        playercontainer.cpp
        lobbycontainer.cpp
        lobbycontrol.cpp
        controlreceiver.cpp
        controlnotifier.cpp
        playeracceptor.cpp
        server.cpp
         

    PUBLIC
    # .h files
        server.h
        gameerror.h
        match.h
        lobbycontainer.h
        lobbycontrol.h
        playeracceptor.h
        playercontainer.h
        controlreceiver.h
        controlledplayer.h
        controlnotifier.h
        controlid.h
    )
