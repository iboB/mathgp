cmake_minimum_required(VERSION 2.8)

enable_testing()

project(mathgp-test)

file(GLOB tests ${CMAKE_CURRENT_SOURCE_DIR}/*.*)
file(GLOB doctest ${CMAKE_CURRENT_SOURCE_DIR}/doctest/*.*)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

add_executable(mathgp-test
    ${tests}
    ${doctest}
)

add_test(mathgp-test mathgp-test)
