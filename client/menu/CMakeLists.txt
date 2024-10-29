add_subdirectory(setHostnamePortWidget/)
add_subdirectory(createJoinWidget/)
add_subdirectory(setLobbyIdWidget/)
add_subdirectory(setSoloDuoWidget/)
add_subdirectory(lobbyWidget/lobbyHostWidget/)
add_subdirectory(lobbyWidget/lobbyGuestWidget/)

target_sources(taller_client
    PRIVATE
    # .cpp files
    mainwindow.cpp
    
    PUBLIC
    # .h files
    mainwindow.h
    
    # .ui files
    mainwindow.ui
    )
