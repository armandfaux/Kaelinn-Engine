cmake_minimum_required(VERSION 3.20)
project(sample)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W")
endif()

set(CLIENT sample-client)
# set(SERVER sample-server)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/../build/sample)

# GAME CLIENT
file(GLOB_RECURSE CLIENT_SOURCE_FILES
    # Replace these with your game source files
    src/*.cpp
)
add_executable(${CLIENT} ${CLIENT_SOURCE_FILES})
target_link_libraries(${CLIENT} PRIVATE engine)

# GAME SERVER (TO IMPLEMENT NETWORKING)
# file(GLOB_RECURSE SERVER_SOURCE_FILES path/to/server/*.cpp)
# add_executable(${SERVER} ${SERVER_SOURCE_FILES})
# target_link_libraries(${SERVER} PRIVATE engine)

if(DEFINED ACTIVATE_LINTER AND ACTIVATE_LINTER STREQUAL "clang-tidy")
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=-*,modernize-*")
    set_target_properties(
        ${CLIENT}
        # ${SERVER}
        PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}"
    )
endif()

if(DEFINED ACTIVATE_LINTER AND ACTIVATE_LINTER STREQUAL "cppcheck")
    find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
    if(CMAKE_CXX_CPPCHECK)
        list(
            APPEND CMAKE_CXX_CPPCHECK
            "--enable=all"
            "--std=c++20"
            "--verbose"
            ${CLIENT_SOURCE_FILES} ${SERVER_SOURCE_FILES}
        )
    endif()
endif()

find_program(CMAKE_CXX_CLANGFORMAT NAMES clang-format)
if (CMAKE_CXX_CLANGFORMAT)
    message(STATUS "Found clang-format: ${CMAKE_CXX_CLANGFORMAT}")
    execute_process(
        COMMAND
            ${CMAKE_CXX_CLANGFORMAT} -i --style=file
            ${CLIENT_SOURCE_FILES}
            # ${SERVER_SOURCE_FILES}
    )
endif ()

if (WIN32)
    add_custom_command(
        TARGET ${CLIENT}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:engine>
        $<TARGET_FILE_DIR:${CLIENT}>
    )

    add_custom_command(
        TARGET ${SERVER}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:engine>
        $<TARGET_FILE_DIR:${SERVER}>
    )
endif()

if (WIN32)
    set(CPACK_GENERATOR ZIP)
else()
    set(CPACK_GENERATOR TGZ)
endif()
set(CPACK_PACKAGE_FILE_NAME "sample")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)

install(TARGETS
    ${CLIENT}
    # ${SERVER}
    engine
    DESTINATION sample
)

install(DIRECTORY assets
    DESTINATION sample
)

include(CPack)