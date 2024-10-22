add_subdirectory(menu/)

target_sources(taller_client
    PRIVATE
    # .cpp files
       client.cpp
       lobbycreatemode.cpp    
       joinlobbymode.cpp
       main.cpp
    PUBLIC
    # .h files
       client.h    
       lobbymode.h    
       lobbycreatemode.h    
       joinlobbymode.h    
    )
