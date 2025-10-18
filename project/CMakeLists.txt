cmake_minimum_required(VERSION 3.16)
project(zpg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# warnings
if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# OpenGL + glfw3 + GLEW
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# GLM (header-only)
find_path(GLM_INCLUDE_DIR glm/glm.hpp PATH_SUFFIXES glm REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

# Assimp
find_package(assimp REQUIRED)
if (TARGET assimp::assimp)
  set(ASSIMP_LIB assimp::assimp)
else()
  find_library(ASSIMP_LIB assimp REQUIRED)
endif()

# stb_image.h
find_path(STB_INCLUDE_DIR
  NAMES stb_image.h
  HINTS
    ${CMAKE_SOURCE_DIR}/external/stb
    /usr/include/stb
    /usr/local/include/stb
    /usr/include
    /usr/local/include
  PATH_SUFFIXES stb
  REQUIRED
)
include_directories(${STB_INCLUDE_DIR})

# SOIL
find_path(SOIL_INCLUDE_DIR
  NAMES SOIL.h
  HINTS
    /usr/include/SOIL
    /usr/local/include/SOIL
    ${CMAKE_SOURCE_DIR}/external/soil
)
find_library(SOIL_LIBRARY NAMES SOIL)
if (SOIL_INCLUDE_DIR AND SOIL_LIBRARY)
  message(STATUS "Found SOIL: ${SOIL_INCLUDE_DIR}, lib: ${SOIL_LIBRARY}")
  include_directories(${SOIL_INCLUDE_DIR})
else()
  message(FATAL_ERROR "SOIL not found. Install libsoil-dev or vendor SOIL headers.")
endif()

# Sources
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
  "${CMAKE_SOURCE_DIR}/*.cpp"
)

list(FILTER SRC EXCLUDE REGEX ".*/CMakeFiles/.*")
list(FILTER SRC EXCLUDE REGEX ".*/build/.*")
list(FILTER SRC EXCLUDE REGEX ".*/cmake-build-.*")
list(FILTER SRC EXCLUDE REGEX ".*/CompilerIdCXX/.*")
list(FILTER SRC EXCLUDE REGEX ".*/CMakeCXXCompilerId\\.cpp$")

add_executable(zpg ${SRC})


target_include_directories(zpg PRIVATE
  ${CMAKE_SOURCE_DIR}
)

target_link_libraries(zpg PRIVATE
  OpenGL::GL
  glfw
  GLEW::GLEW
  ${ASSIMP_LIB}
  ${SOIL_LIBRARY}
)


set(RESOURCE_DIRS Shaders Models Cubemap)
foreach(dir IN LISTS RESOURCE_DIRS)
  if (EXISTS "${CMAKE_SOURCE_DIR}/${dir}")
    add_custom_command(TARGET zpg POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/${dir}" "$<TARGET_FILE_DIR:zpg>/${dir}")
  endif()
endforeach()

