cmake_minimum_required(VERSION 2.6)
project(mazesolver)

find_package(GTest REQUIRED)
find_package(Eigen3 REQUIRED)

enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions( -DSRCDIR=\"${CMAKE_SOURCE_DIR}/\")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -Werror=reorder")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g -DBOOST_LOG_DYN_LINK -DNDEBUG")

MESSAGE( STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}" )
MESSAGE( STATUS "C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}" )
MESSAGE( STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}" )
MESSAGE( STATUS "C++ compiler string: ${CXX_COMPILER_STRING}" )

include_directories( ${CMAKE_SOURCE_DIR}
                     ${GTEST_INCLUDE_DIRS}
                     ${EIGEN3_INCLUDE_DIR}
		     )

add_executable( mazesolver
  driver.cpp
  Node.cpp
  utils.cpp
  search.cpp
  examplemaze.cpp
  )

target_link_libraries( mazesolver
  m
)


add_executable( unittests
  tests/tests.cpp
  tests/utils_test.cpp
  tests/node_test.cpp
  tests/search_test.cpp
  search.cpp
  examplemaze.cpp
  utils.cpp
  Node.cpp
)

target_link_libraries( unittests
  ${GTEST_LIBRARIES}
  #/usr/lib/libgtest.a
  pthread
)

enable_testing()

set_target_properties( unittests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

add_test(
  NAME
  unittests
  COMMAND
  unittests
)
