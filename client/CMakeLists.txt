add_subdirectory(menu/)
add_subdirectory(core/)
add_subdirectory(interfaz/)

target_sources(taller_client
    PRIVATE
    # .cpp files
          client.cpp
          main.cpp
          simpleeventlistener.cpp

    PUBLIC
    # .h files
          actionlistener.h
          client.h
          eventlistener.h
          simpleeventlistener.h
          gamecontext.h
    )
