target_sources(taller_server_logic
    PRIVATE
    # .cpp files
        match_state.cpp

    PUBLIC
    # .h files
        match_state.h
        configuration.h
        matchobserver.h
    )
