cmake_minimum_required(VERSION 2.8)

enable_testing()

project(mathgp-test)

file(GLOB tests ${CMAKE_CURRENT_SOURCE_DIR}/*.*)
file(GLOB doctest ${CMAKE_CURRENT_SOURCE_DIR}/doctest/*.*)

add_executable(mathgp-test
    ${tests}
    ${doctest}
)

add_test(mathgp-test mathgp-test)
