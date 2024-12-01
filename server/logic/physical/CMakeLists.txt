
target_sources(taller_server_logic
    PRIVATE
    # .cpp files

            match_map.cpp
            physical_object.cpp
            physical_player.cpp
            physical_bullet.cpp
            physical_grenade.cpp
    PUBLIC
    # .h files
            match_map.h
            physical_object.h
            physical_player.h
            physical_bullet.h
            physical_grenade.h
            collision.h
            map_object.h
            tuple.h
            type_collision.h
    )
