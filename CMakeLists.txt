# TODO: should i make a top level cmake file or script or something to
# avoid having to do `mkdir build && cd build && cmake ..` and instead
# run commands from the top level of the repository?
# i think the problem is that i want an out-of-tree build executed by
# default with a final distributable directory in a third, separate
# location. cmake supports out-of-tree very well... in that any cmake
# project can be either in-tree or out-of-tree depending on where you
# feel like launching cmake from that day. and for the most part it
# really does work consistently. it passes the choice to the user.
# but here's the thing: why pass that choice on to the user? the user
# is, in this case, a developer trying to compile your code. build
# systems should stay out of the way and, to the extent possible, work
# the same way for everybody. but that's just my opinion [kermit meme].
# and also it makes writing `.gitignore` files more complicated.
# so i want one or two commands, executed at the top level from a fresh
# checkout, without creating any directories, resulting in two
# directories, direct children of the top level: `build`, containing
# artfifacts of the build system and the build process itself, and
# `dist`, containing the final artifacts ready for distribution. i like
# this directory structure because it works well with most build
# automation platforms and packaging managers that i've encountered.
# iirc autotools provides that experience but so far i've found too many
# other reasons to prefer cmake and maybe i'll gain some deeper
# understanding of cmake and this `mkdir` stuff will make more sense to
# me. or maybe i'll just deal with it. or maybe i'll find a hack that's
# just elegant enough i'd rather deal with the hack.

# edit: i've hacked together a Makefile. haven't decided how i feel
# about it yet.

cmake_minimum_required(VERSION 3.0)

project(example)
set(EXAMPLE_VERSION_MAJOR 1)
set(EXAMPLE_VERSION_MINOR 0)

find_package(Git)
if(GIT_FOUND)
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE EXAMPLE_GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" log -1 --format=%h
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE EXAMPLE_GIT_REVISION
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else()
    set(EXAMPLE_GIT_BRANCH "")
    set(EXAMPLE_GIT_REVISION "")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c99 -Wall -Werror -Wextra")

file(
    GLOB_RECURSE EXAMPLE_SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

set(EXAMPLE_INCLUDE "${PROJECT_SOURCE_DIR}/inc/")

configure_file(
    "${EXAMPLE_INCLUDE}/config.h.in"
    "${CMAKE_BINARY_DIR}/inc/config.h"
)

add_executable(example "${EXAMPLE_SOURCES}")
target_include_directories(
    example PRIVATE
    "${CMAKE_BINARY_DIR}/inc" "${EXAMPLE_INCLUDE}"
)

set_target_properties(example
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/dist/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/dist/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/dist/bin"
)
