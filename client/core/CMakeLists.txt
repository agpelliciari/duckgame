target_sources(taller_client
    PRIVATE
    # .cpp files
          lobby_client_sender.cpp
          lobbycreatemode.cpp
          game_action_sender.cpp
          joinlobbymode.cpp
          game_loop.cpp

    PUBLIC
    # .h files
          lobbymode.h
          lobby_client_sender.h
          joinlobbymode.h
          game_loop.h
          game_action_sender.h
          lobbycreatemode.h
    )
