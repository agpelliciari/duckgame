add_subdirectory(menu/)

target_sources(taller_client
    PRIVATE
    # .cpp files
       client.cpp
       game_loop.cpp
       lobbycreatemode.cpp    
       joinlobbymode.cpp
       main.cpp
    PUBLIC
    # .h files
       client.h
       game_loop.h
       lobbymode.h    
       lobbycreatemode.h    
       joinlobbymode.h    
    )
