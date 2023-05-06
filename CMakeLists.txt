CMAKE_MINIMUM_REQUIRED(VERSION 2.9)

SET(CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(googletest)

ADD_EXECUTABLE(solver
    main.cpp src/game.cpp src/tree.cpp src/node.cpp
)

ADD_EXECUTABLE(testcases
    mainTestFromDocs.cpp src/game.cpp src/tree.cpp src/node.cpp
)


TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
