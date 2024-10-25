add_subdirectory(menu/)
add_subdirectory(core/)

target_sources(taller_client
    PRIVATE
    # .cpp files
          client.cpp
          main.cpp

    PUBLIC
    # .h files
          actionlistener.h
          menuhandler.h
          client.h
          eventlistener.h
    )
