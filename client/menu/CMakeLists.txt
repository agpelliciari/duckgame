add_subdirectory(createJoinWidget/)
add_subdirectory(setLobbyIdWidget/)

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
