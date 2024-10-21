# No necesarias, pero parece eran necesarias para mac.. bue se dejan por las dudas
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -lgmock -lgstest")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lgmock -lgstest")

target_sources(taller_tests
    PRIVATE
    # .cpp files
    testbaseprotocol.cpp
    testclientprotocol.cpp
    testserverprotocol.cpp
    PUBLIC
    # .h files
    mocksocket.h
    )
