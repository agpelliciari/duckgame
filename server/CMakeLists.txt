add_subdirectory(logic_server/)

target_sources(taller_server
    PRIVATE
    # .cpp files
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
         lobbycontainer.h
         playerprotocol.h
         matchaction.h
         player.h
         match.h
         matchqueue.h
         playeracceptor.h
         playernotifier.h
         matchstate.h
         playercontainer.h
         gameerror.h
         matchserver.h
         playercontroller.h
         box.h

    )
