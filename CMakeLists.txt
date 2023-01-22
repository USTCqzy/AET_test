project(AET_test)

cmake_minimum_required(VERSION 3.12)

SET(SRC_LIST test_trace.cc)

SET(AETLIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/AETLib)
message(STATUS "AETLIB_PATH: ${AETLIB_PATH}")

INCLUDE_DIRECTORIES(${AETLIB_PATH})
# get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
# foreach(dir ${dirs})
#   message(STATUS "dir='${dir}'")
# endforeach()

find_library(LIBAET libaet.so HINTS ${AETLIB_PATH})
message(STATUS "LIBAET: ${LIBAET}")

ADD_EXECUTABLE(AET_test ${SRC_LIST})
target_link_libraries(AET_test ${LIBAET})




# INCLUDE_DIRECTORIES(./AETLib/)

# find_path(INCAET aet.h PATHS ./AETLib/)
# message(STATUS "INCAET: ${INCAET}")

# find_library(LIBAET libaet PATHS ./AETLib/)
# message("${LIBAET}")

# ADD_EXECUTABLE(AET_test ${SRC_LIST})
# target_link_libraries(AET_test ${LIBAET})