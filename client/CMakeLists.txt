add_subdirectory(menu/)
add_subdirectory(interfaz/)

target_sources(taller_client
    PRIVATE
    # .cpp files
          lobby_client_sender.cpp
          lobbycreatemode.cpp
          game_action_sender.cpp
          joinlobbymode.cpp
          client.cpp
          game_loop.cpp
          main.cpp

    PUBLIC
    # .h files
          lobbymode.h
          lobby_client_sender.h
          actionlistener.h
          joinlobbymode.h
          menuhandler.h
          game_loop.h
          game_action_sender.h
          client.h
          eventlistener.h
          lobbycreatemode.h

    )
