add_subdirectory(menu/)

target_sources(taller_client
    PRIVATE
    # .cpp files
       client.cpp
       main.cpp
    PUBLIC
    # .h files
       client.h    
    )
