add_subdirectory(interface/)
add_subdirectory(playground/)

target_sources(taller_editor
    PRIVATE
    # .cpp files
    main.cpp
    editorWindow.cpp
    loader.cpp
    tileset.cpp
    PUBLIC
    # .h files
    editorWindow.h
    loader.h
    tileset.h
    types.h
    # .ui files
    editorWindow.ui
    )
