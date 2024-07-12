include(cmake/DisableInSourceBuildDir.cmake)

cmake_minimum_required(VERSION 3.10)

project(saf
  VERSION 1.0.0
  DESCRIPTION "Safe Arithmetics Function checks on overflows/underflows operations"
  LANGUAGES C CXX)

include(CMakePrintHelpers)
include(GNUInstallDirs)

configure_file(
  include/saf/version.h.in
  include/saf/version.h
  @ONLY
  )

add_subdirectory(src)

include(cmake/TestingOptions.cmake)
if(${PROJECT_NAME}_ENABLE_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

install(
  DIRECTORY
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/>
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PATTERN "*.in" EXCLUDE
  PATTERN "*.h"
  )

###############################################################################
#                       Install find_package() artifacts                      #
###############################################################################
include(CMakePackageConfigHelpers)

# Create the find_package version handling
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION "${PROJECT_VERSION}"
  COMPATIBILITY AnyNewerVersion
  )

# Create the '${PROJECT_NAME}Config.cmake' using
# '${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in'
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  )

# Install files created above
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  )
