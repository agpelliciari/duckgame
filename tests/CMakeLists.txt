# No necesarias, pero parece eran necesarias para mac.. bue se dejan por las dudas
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -lgmock -lgstest")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lgmock -lgstest")
add_subdirectory(core/)
add_subdirectory(logic/)

target_sources(taller_tests
    PRIVATE
    # .cpp files
    testbaseprotocol.cpp
    testprotocolintegration.cpp
    #PUBLIC
    # .h files
    )
