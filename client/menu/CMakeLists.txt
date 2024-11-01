add_subdirectory(setHostnamePortWidget/)
add_subdirectory(createJoinWidget/)
add_subdirectory(setLobbyIdWidget/)
add_subdirectory(setSoloDuoWidget/)
add_subdirectory(lobbyWidget/lobbyHostWidget/)
add_subdirectory(lobbyWidget/lobbyGuestWidget/)
add_subdirectory(lobbyWidget/playerWidget/)

target_sources(taller_client
    PRIVATE
    # .cpp files
    menu.cpp
    menuhandler.cpp
    menuAction.cpp
    
    PUBLIC
    # .h files
    menu.h
    menuhandler.h
    menuAction.h
    
    # .ui files
    menu.ui
    )
