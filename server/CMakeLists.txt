target_sources(taller_server
    PRIVATE
    # .cpp files
         lobby.cpp
         lobbycontainer.cpp
         playernotifier.cpp
         player.cpp
         matchserver.cpp
         box.cpp
         playeracceptor.cpp
         matchaction.cpp
         match.cpp
         matchqueue.cpp
         playercontroller.cpp
         gameerror.cpp
         playerprotocol.cpp
         playercontainer.cpp
         main.cpp
         matchstate.cpp

    PUBLIC
    # .h files
         lobby.h
         lobbycontainer.h
         playerprotocol.h
         matchaction.h
         player.h
         match.h
         matchqueue.h
         matchobserver.h
         playeracceptor.h
         playernotifier.h
         matchstate.h
         playercontainer.h
         gameerror.h
         matchserver.h
         playercontroller.h
         box.h

    )
