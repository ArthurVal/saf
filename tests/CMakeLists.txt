message(STATUS "Building unittests ...")

message(STATUS "Finding GTest: ...")
find_gtest()
message(STATUS "Finding GTest: DONE")

include(GoogleTest)

add_subdirectory(saf)
