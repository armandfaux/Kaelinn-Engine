cmake_minimum_required(VERSION 3.20)
project(engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W")
endif()

find_package(SFML COMPONENTS graphics window system REQUIRED)
find_package(asio REQUIRED)
find_package(cereal REQUIRED)
find_package(Snappy REQUIRED)
find_package(SDL2 REQUIRED)

set(COMMON_LIBRARIES
    asio::asio
    cereal::cereal
    sfml-graphics
    sfml-system
    sfml-window
    Snappy::snappy
    SDL2::SDL2
)

file(GLOB_RECURSE ENGINE_SOURCE_FILES
    component/**/*.cpp
    component/**/*.hpp
    component/*.cpp
    component/*.hpp

    core/*.cpp
    core/*.hpp

    event/*.cpp
    event/*.hpp

    interface/*.hpp

    math/*.cpp
    math/*.hpp

    system/**/*.cpp
    system/**/*.hpp
    system/*.cpp
    system/*.hpp
)

if(DEFINED ACTIVATE_LINTER AND ACTIVATE_LINTER STREQUAL "cppcheck")
    find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
    if(CMAKE_CXX_CPPCHECK)
        list(
            APPEND CMAKE_CXX_CPPCHECK
            "--enable=all"
            "--std=c++20"
            "--verbose"
            ${ENGINE_SOURCE_FILES}
        )
    endif()
endif()

find_program(CMAKE_CXX_CLANGFORMAT NAMES clang-format)
if (CMAKE_CXX_CLANGFORMAT)
    message(STATUS "Found clang-format: ${CMAKE_CXX_CLANGFORMAT}")
    execute_process(
        COMMAND ${CMAKE_CXX_CLANGFORMAT} -i --style=file ${ENGINE_SOURCE_FILES}
    )
endif ()

add_library(engine SHARED ${ENGINE_SOURCE_FILES})
if (WIN32)
    target_compile_definitions(engine PUBLIC -D_WINDOWS ENGINE_EXPORTS)
endif()
target_include_directories(engine
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/component>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/event>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interface>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/math>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/system>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)
target_link_libraries(engine PUBLIC ${COMMON_LIBRARIES})

if(DEFINED ACTIVATE_LINTER AND ACTIVATE_LINTER STREQUAL "clang-tidy")
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=-*,modernize-*")
    set_target_properties(engine PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
endif()