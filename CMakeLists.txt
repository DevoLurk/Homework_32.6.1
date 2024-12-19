cmake_minimum_required(VERSION 3.12)

set(GOOGLETEST_VERSION 1.15.2)

set(CMAKE_CXX_FLAGS_DEBUG
  "/DWIN32 /D_WINDOWS /EHsc /WX /wd4355 /wd4251 /wd4250 /wd4996"
  CACHE STRING "Debug compiler flags" FORCE
)

project(homework_32.6.1) #name of your project


enable_testing() #to  discover tests in test explorer 

add_subdirectory(googletest) # add googletest subdirectory

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>
include_directories(googlmock/include)  # this is so we can #include <gtest/gmock.h>

set( TARGET ${PROJECT_NAME} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )

set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include" )

file( GLOB_RECURSE HPPS "${INCLUDE_PATH}/*.h" )
file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp" )

add_executable( ${TARGET} ${CPPS} ${HPPS} )

target_link_libraries( ${TARGET} PRIVATE gtest gmock )

include(GoogleTest)
gtest_discover_tests(${TARGET}) 