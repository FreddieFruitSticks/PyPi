#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cppunit" for configuration "Release"
set_property(TARGET cppunit APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(cppunit PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libcppunit.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS cppunit )
list(APPEND _IMPORT_CHECK_FILES_FOR_cppunit "${_IMPORT_PREFIX}/lib/libcppunit.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
