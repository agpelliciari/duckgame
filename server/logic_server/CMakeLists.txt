target_sources(taller_server
    PRIVATE
    # .cpp files
            coordinates.cpp
            action.cpp
            match_logic.cpp
            player.cpp
            armor.cpp
            weapon.cpp
            match_queue.cpp
            match_state.cpp
            box.cpp
 

    PUBLIC
    # .h files
            player.h
            match_logic.h
            match_queue.h
            action.h
            match_state.h
            weapon.h
            coordinates.h
            box.h
            armor.h

    )
