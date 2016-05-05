cmake_minimum_required(VERSION 2.8)

project(mathgp-test)

# setup coverage stuff only when COVERALLS_SERVICE_NAME is set (usually on travis CI)
if(DEFINED ENV{COVERALLS_SERVICE_NAME})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/coveralls-cmake)
    include(Coveralls)
    coveralls_turn_on_coverage()

    file(GLOB mathgp_files ${CMAKE_CURRENT_SOURCE_DIR}/../../mathgp/*.*)

    coveralls_setup("${mathgp_files}" ON ${CMAKE_CURRENT_SOURCE_DIR}/coveralls-cmake)
endif()

enable_testing()

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
