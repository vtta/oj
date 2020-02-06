cmake_minimum_required(VERSION 2.8)

project(oj)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(add_all_oj_target ojname)
    file(GLOB_RECURSE oj_src RELATIVE ${CMAKE_SOURCE_DIR} "${ojname}/*.cpp")
    foreach (filepath ${oj_src})
        get_filename_component(filename ${filepath} NAME)
        string(REPLACE ".cpp" "" filebasename ${filename})
        set(execname ${ojname}-${filebasename})
        string(REPLACE ".cpp" ".in" execinput ${filepath})
        string(REPLACE ".cpp" ".out" execoutput ${filepath})
        add_executable(${execname} ${filepath})
        add_custom_target(run-${execname}
                COMMAND time sh -c ' set -x && cat ${CMAKE_SOURCE_DIR}/${execinput} | ${PROJECT_BINARY_DIR}/${execname} | tee ${CMAKE_SOURCE_DIR}/${execoutput} '
                DEPENDS ${execname}
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
        # message("${filepath} ${filename} ${filebasename} ${execname}")
    endforeach ()
endfunction()

add_all_oj_target(lib)

add_all_oj_target(poj)

# https://cmake.org/cmake/help/latest/command/string.html
# https://cmake.org/cmake/help/latest/command/get_filename_component.html
# https://cmake.org/cmake/help/latest/command/add_executable.html
# https://cmake.org/cmake/help/latest/command/function.html
# https://cmake.org/cmake/help/latest/command/set.html
# string(REPLACE <match-string> <replace-string> <out-var> <input>...)
# get_filename_component(<var> <FileName> <mode> [CACHE])
# add_executable(<name> [WIN32] [MACOSX_BUNDLE] [EXCLUDE_FROM_ALL] [source1] [source2 ...])
# function(<name> [<arg1> ...]) <commands> endfunction()
# set(<variable> <value>... [PARENT_SCOPE])
