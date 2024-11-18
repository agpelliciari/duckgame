target_sources(taller_server_logic
    PRIVATE
    # .cpp files

            match_logic.cpp
            player.cpp
            armor.cpp
            weapon.cpp
            match_queue.cpp
            match_state.cpp
            match_map.cpp
            box.cpp
            item.cpp
            action_command.cpp
            physical_object.cpp
            physical_player.cpp
            cowboy_pistol_weapon.cpp
            physical_bullet.cpp
            magnum_weapon.cpp
            duel_pistol.cpp
            pewpew_laser_weapon.cpp



    PUBLIC
    # .h files
            player.h
            match_logic.h
            match_queue.h
            match_state.h
            match_map.h
            weapon.h
            box.h
            item.h
            armor.h
            command.h
            action_command.h
            matchobserver.h
            physical_object.h
            physical_player.h
            shooting_direction.h
            cowboy_pistol_weapon.h
            physical_bullet.h
            magnum_weapon.h
            duel_pistol.h
            pewpew_laser_weapon.h

    )
