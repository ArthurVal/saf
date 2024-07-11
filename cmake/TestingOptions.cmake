#.rst
# TestingOptions
# --------------
#
# This module is meant to be included by the main CMake of a project in order to
# provide the testing related options
#
# It declares the following options, prefixed by ${PROJECT_NAME}:
#  ${PROJECT_NAME}_ENABLE_TESTING    - BOOL   - Enable unittests
#  ${PROJECT_NAME}_TESTING_GTEST_URL - STRING - GTest URL location


include(CMakePrintHelpers)

message(STATUS "${PROJECT_NAME} Testing Options:")

option(${PROJECT_NAME}_ENABLE_TESTING
  "Enable unit tests build of ${PROJECT_NAME}"
  OFF)
cmake_print_variables(${PROJECT_NAME}_ENABLE_TESTING)

set(${PROJECT_NAME}_TESTING_GTEST_URL
  "https://github.com/google/googletest/archive/v1.14.0.zip"
  CACHE STRING
  "Points towards the googletest.zip URL that will be fetch, if GTest is not installed on the system."
  )
cmake_print_variables(${PROJECT_NAME}_TESTING_GTEST_URL)

function(find_gtest)
  find_package(GTest)

  if(NOT GTest_FOUND)
    message(STATUS "Fetching GTest @ \"${${PROJECT_NAME}_TESTING_GTEST_URL}\": ...")



    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL ${${PROJECT_NAME}_TESTING_GTEST_URL}
      )
    FetchContent_MakeAvailable(googletest)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(INSTALL_GTEST OFF)

    message(STATUS "Fetching GTest @ \"${${PROJECT_NAME}_TESTING_GTEST_URL}\": DONE")
  endif()
endfunction()
