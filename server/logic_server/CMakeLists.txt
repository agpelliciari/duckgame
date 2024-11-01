target_sources(taller_server_logic
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
            action_command.cpp
            physical_object.cpp


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
            command.h
            action_command.h
            matchobserver.h
            physical_object.h


    )
