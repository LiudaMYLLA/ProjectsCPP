# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appMyListVisual_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appMyListVisual_autogen.dir\\ParseCache.txt"
  "appMyListVisual_autogen"
  )
endif()
