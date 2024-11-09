target_sources(taller_client
    PRIVATE
    # .cpp files
          lobby_state_recv.cpp
          lobby_create_state.cpp
          lobby_join_state.cpp
          lobby_action_queue.cpp
          lobby_action_sender.cpp
    PUBLIC
    # .h files
          lobby_state_recv.h
          lobby_create_state.h
          lobby_join_state.h
          lobby_action_queue.h
          lobby_action_sender.h
    )
