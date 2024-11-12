# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Intento_Juego_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Intento_Juego_autogen.dir\\ParseCache.txt"
  "Intento_Juego_autogen"
  )
endif()
