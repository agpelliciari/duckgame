add_subdirectory(lobby/)

target_sources(taller_client
    PRIVATE
    # .cpp files
          play_state_sender.cpp
          play_state_recv.cpp
          game_manager.cpp

    PUBLIC
    # .h files
          lobby_listener.h
          game_manager.h
          game_state.h
          play_state_sender.h
          play_state_recv.h
    )
