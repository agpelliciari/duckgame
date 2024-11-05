target_sources(taller_client
    PRIVATE
    # .cpp files
          base_lobby_state.cpp
          lobby_create_sender.cpp
          lobby_join_sender.cpp
          lobby_client_sender.cpp
          game_action_sender.cpp
          game_state_recv.cpp
          lobby_connector.cpp
          lobby_action_listener.cpp

    PUBLIC
    # .h files
          base_lobby_state.h
          lobby_create_sender.h
          lobby_join_sender.h
          lobby_client_sender.h
          lobby_action_listener.h
          lobby_state.h
          lobby_listener.h
          lobby_connector.h
          game_action_sender.h
          game_state_recv.h
    )
