target_sources(taller_client
    PRIVATE
    # .cpp files
          lobby_client_sender.cpp
          game_action_sender.cpp
          game_state_recv.cpp
          lobby_connector.cpp

    PUBLIC
    # .h files
          lobby_client_sender.h
          lobby_connector.h
          game_action_sender.h
          game_state_recv.h
    )
