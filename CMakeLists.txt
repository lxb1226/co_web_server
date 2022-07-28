cmake_minimum_required(VERSION 3.10)

project(co_web_server)

enable_language(ASM)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CXX_FLAGS
        -g
        # -DVALGRIND
        -DCHECK_PTHREAD_RETURN_VALUE
        -D_FILE_OFFSET_BITS=64
        -Wall
        -Wextra
        -Werror
        -Wconversion
        -Wno-unused-parameter
        -Wno-unused-but-set-variable
        -Wno-unused-variable
        -Wno-unused-result
        -Wold-style-cast
        -Woverloaded-virtual
        -Wpointer-arith
        -Wshadow
        -Wwrite-strings
        -march=native
        -Wno-deprecated
        # -MMD
        -std=c++11
        -rdynamic
        -pthread   # check
        )
#if (CMAKE_BUILD_BITS EQUAL 32)
#    list(APPEND CXX_FLAGS "-m32")
#endif ()
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    list(APPEND CXX_FLAGS "-Wno-null-dereference")
    list(APPEND CXX_FLAGS "-Wno-sign-conversion")
    list(APPEND CXX_FLAGS "-Wno-unused-local-typedef")
    list(APPEND CXX_FLAGS "-Wthread-safety")
    list(REMOVE_ITEM CXX_FLAGS "-rdynamic")
endif ()
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")


include_directories(${PROJECT_SOURCE_DIR}/third_party)
include_directories(${PROJECT_SOURCE_DIR}/third_party/co_net)
include_directories(${PROJECT_SOURCE_DIR}/third_party/co_net/thirdparty)
include_directories(${PROJECT_SOURCE_DIR}/src)

link_directories(${PROJECT_SOURCE_DIR}/lib)


string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})
#add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/http_server)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/co_net/conet/base)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/co_net/conet/net)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/co_net/config)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/co_net/thirdparty/googletest)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/co_net/thirdparty/spdlog)


#add_executable(server main.cpp)
#target_link_libraries(server co_net co_base http)