cmake_minimum_required(VERSION 3.20)
project(engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W")
endif()

find_package(Catch2 3 REQUIRED)

set(ACTIVATE_LINTER "none" CACHE STRING "Specify the linter to use: cppcheck, clang-tidy")
set(ENABLE_TESTS "none" CACHE STRING "Specify if you want to activate tests: true, false")

add_subdirectory(src/engine)

set(ENABLE_PROJECT "none" CACHE STRING "Specify the project to compile (ignore to compile only the engine):")

### CALLS YOUR GAME'S CMAKELISTS
if (ENABLE_PROJECT STREQUAL "mygame" OR ENABLE_PROJECT STREQUAL "all")
    add_subdirectory(src/games/simulation) # Path to your game CMakeLists
endif()

if (DEFINED ENABLE_TESTS AND ENABLE_TESTS STREQUAL "true")
    file(GLOB_RECURSE TEST_SOURCE_FILES src/tests/*.cpp)
    add_executable(tests ${TEST_SOURCE_FILES})
    target_link_libraries(tests PRIVATE engine Catch2::Catch2WithMain)
endif ()