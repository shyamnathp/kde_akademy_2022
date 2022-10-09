# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/scriptableapplication_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/scriptableapplication_autogen.dir/ParseCache.txt"
  "scriptableapplication_autogen"
  )
endif()
