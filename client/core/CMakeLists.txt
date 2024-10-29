target_sources(taller_client
    PRIVATE
    # .cpp files
          lobby_client_sender.cpp
          game_action_sender.cpp
          game_state_recv.cpp
          game_loop.cpp

    PUBLIC
    # .h files
          lobby_client_sender.h
          game_loop.h
          game_action_sender.h
          game_state_recv.h
    )
