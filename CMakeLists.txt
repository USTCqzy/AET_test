project(AER_test)

cmake_minimum_required(VERSION 3.16)

SET(SRC_LIST test_trace.cc)

INCLUDE_DIRECTORIES(./AETLib)
find_library(LIBAET libaet PATHS ./AETLib/)
# find_package(AETLib libaet PATHS ./AETLib/)
message("${LIBAET}")

ADD_EXECUTABLE(AER_test ${SRC_LIST})
target_link_libraries(AER_test ${LIBAET})