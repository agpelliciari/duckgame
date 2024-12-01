add_subdirectory(weapons/)
add_subdirectory(physical/)

target_sources(taller_server_logic
    PRIVATE
    # .cpp files

            match_logic.cpp
            player.cpp
            armor.cpp
            match_queue.cpp
            box.cpp
            spawn_place.cpp
            action_command.cpp
            dropped_item.cpp

    PUBLIC
    # .h files
            player.h
            match_logic.h
            match_queue.h
            box.h
            spawn_place.h
            armor.h
            command.h
            action_command.h
            dropped_item.h
    )
