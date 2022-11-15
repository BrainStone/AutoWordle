cmake_minimum_required(VERSION 3.14)

project(AutoWordle CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)

###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variables
# `sources` and `data`
file(GLOB_RECURSE sources src/*.cpp src/*.hpp)
file(GLOB_RECURSE data assets/*)
# you can use set(sources src/main.cpp) etc if you don't want to
# use globing to find files automatically

###############################################################################
## file generation ############################################################
###############################################################################

file(STRINGS assets/allowed_words.txt allowed_words)
file(STRINGS assets/solution_words.txt solution_words)
list(TRANSFORM allowed_words PREPEND "    \"")
list(TRANSFORM solution_words PREPEND "    \"")
list(TRANSFORM allowed_words APPEND "\",\n")
list(TRANSFORM solution_words APPEND "\",\n")
list(JOIN allowed_words "" allowed_words_joined)
list(JOIN solution_words "" solution_words_joined)
string(CONCAT
        content
        [=[
#pragma once

#include <list>

#include "Word.hpp"

namespace builtin_lists {

inline const std::list<Word> allowed_words{
]=]
        "${allowed_words_joined}"
        [=[
};

inline const std::list<Word> solution_words{
]=]
        "${solution_words_joined}"
        [=[
};

} // builtin_lists
]=]
        )
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/assets/builtin_lists.hpp "${content}")

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
add_executable(${PROJECT_NAME} ${sources} ${data} ${CMAKE_CURRENT_BINARY_DIR}/assets/builtin_lists.hpp)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif ()

# this lets me include files relative to the root src dir with a <> pair
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/assets)

# this copies all resource files in the build directory
# we need this, because we want to work with paths relative to the executable
file(COPY ${data} DESTINATION assets)

###############################################################################
## dependencies ###############################################################
###############################################################################

## this defines the variables Boost_LIBRARIES that contain all library names
## that we need to link to
#find_package(Boost 1.64.0 REQUIRED)
#
#if (Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIR})
#    add_definitions("-DHAS_BOOST")
#endif ()
#
#target_link_libraries(${PROJECT_NAME} PUBLIC
#        ${Boost_LIBRARIES}
#        # here you can add any library dependencies
#        )

file(DOWNLOAD "https://raw.githubusercontent.com/aantron/better-enums/0.11.3/enum.h" "lib/better-enums/enum.h")
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/lib)

###############################################################################
## packaging ##################################################################
###############################################################################

# all install commands get the same destination. this allows us to use paths
# relative to the executable.
install(TARGETS ${PROJECT_NAME} DESTINATION install)
# this is basically a repeat of the file copy instruction that copies the
# resources in the build directory, but here we tell cmake that we want it
# in the package
install(DIRECTORY assets DESTINATION install)

# now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here
set(CPACK_PACKAGE_NAME "AutoWordle")
set(CPACK_PACKAGE_VERSION "1.0.0")

# we don't want to split our program up into several things
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)
