add_executable(Project_3_Hashing ../../src/lulucici/Project-3/main.c)
add_executable(Project_3_Hashing_Cpp ../../src/lulucici/Project-3/main.cpp)
add_custom_target(Project_3_Hashing_Swift
        COMMAND /Library/Developer/Toolchains/swift-latest.xctoolchain/usr/bin/swift build
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/lulucici/Project-3/swift
        SOURCES ../../src/lulucici/Project-3/swift)