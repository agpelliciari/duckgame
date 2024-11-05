add_subdirectory(interface/)
add_subdirectory(playground/)

target_sources(taller_editor
    PRIVATE
    # .cpp files
    main.cpp
    editorWindow.cpp
    PUBLIC
    # .h files
    editorWindow.h
    # .ui files
    editorWindow.ui
    )
