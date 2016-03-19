cmake_minimum_required(VERSION 3.3)
project(AdaptiveHuffmanCoding)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(CORE_MAJOR_VERSION 0)
set(CORE_MINOR_VERSION 0)
set(CORE_PATCH_VERSION 1)
set(CORE_VERSION
        ${CORE_MAJOR_VERSION}.${CORE_MINOR_VERSION}.${CORE_PATCH_VERSION})

configure_file(include/Core.h.in "${CMAKE_CURRENT_SOURCE_DIR}/include/Core.h")


SET(HEADER_FILES
        include/Coder.h
        include/CodeTree.h
        include/Core.h
        include/Decoder.h
        include/HuffmanCode.h
        NameGenerator.h
        )

set(SOURCE_FILES
        src/Coder.cpp
        src/CodeTree.cpp
        src/Decoder.cpp
        src/HuffmanCode.cpp
        src/Main.cpp
        )


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


set(BOOST_ROOT "D:/Dev/CppWorkspace/boost_1_60_0")

set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

find_package(Boost REQUIRED COMPONENTS program_options filesystem system )
if(Boost_FOUND)
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif()

include_directories(include)

add_executable(AdaptiveHuffmanCoding ${SOURCE_FILES})
target_link_libraries(AdaptiveHuffmanCoding ${Boost_LIBRARIES})




