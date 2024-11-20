# No necesarias, pero parece eran necesarias para mac.. bue se dejan por las dudas
target_sources(taller_tests
    PRIVATE
    # .cpp files
    test_logic_integration.cpp
    mockobserver.cpp
    PUBLIC
    # .h files
    mockobserver.h
    )
