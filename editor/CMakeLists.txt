add_subdirectory(interface/)
add_subdirectory(playground/)

target_sources(taller_editor
    PRIVATE
    # .cpp files
    main.cpp
    editorWindow.cpp
    loader.cpp
    PUBLIC
    # .h files
    editorWindow.h
    loader.h
    # .ui files
    editorWindow.ui
    )
