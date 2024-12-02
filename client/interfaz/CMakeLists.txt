target_sources(taller_client
    PRIVATE
    # .cpp files
    animation.cpp
    loop_ui.cpp
    texture_container.cpp
    event_handler.cpp
    drawer.cpp
    camera.cpp
    sound_manager.cpp
    sound_container.cpp
    animationUtils/explosion_animation.cpp
    drawerUtils/armor_drawer.cpp
    drawerUtils/player_drawer.cpp
    drawerUtils/weapon_drawer.cpp
    
    PUBLIC
    # .h files
    animation.h
    loop_ui.h
    texture_container.h
    event_handler.h
    drawer.h
    camera.h
    sound_manager.h
    sound_container.h
    animationUtils/animation_builder.h
    animationUtils/explosion_animation.h
    drawerUtils/armor_drawer.h
    drawerUtils/player_drawer.h
    drawerUtils/weapon_drawer.h
    drawerUtils/weapon_builder.h
    drawerUtils/equipment_drawer.h
    )
