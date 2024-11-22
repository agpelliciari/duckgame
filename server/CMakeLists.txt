#Se removio mientras no ese usable
add_subdirectory(logic_server/)

target_sources(taller_server_logic
    PRIVATE
    # .cpp files
        server.cpp
        #main.cpp
        gameerror.cpp
        lobbycontainer.cpp
        lobbycontrol.cpp
        match.cpp
        playeracceptor.cpp
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
        lobbycontrol.h
        playeracceptor.h
        playercontainer.h
        controlreceiver.h
        controlledplayer.h
        controlnotifier.h
        controlid.h
    )
