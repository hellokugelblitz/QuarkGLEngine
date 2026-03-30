cmake_minimum_required(VERSION 3.20)
project(Game LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------
# Find external libraries
# -------------------------

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

# -------------------------
# GLAD
# -------------------------

add_library(glad STATIC src/glad.c)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/thirdparty
)

# -------------------------
# QuarkPhysics
# -------------------------

file(GLOB_RECURSE QUARK_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/thirdparty/QuarkPhysics/*.cpp
)

add_library(quark STATIC ${QUARK_SRC})

target_include_directories(quark PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/thirdparty/QuarkPhysics
)

# -------------------------
# Game executable
# -------------------------

add_executable(Game
    src/main.cpp
    src/Shader.cpp
    src/PhysicsObject.cpp
    src/Primitives.cpp
    src/Level.cpp
    src/Platformer.cpp
    src/stb_image.cpp
    src/Object.cpp
    src/TextureCache.cpp
    src/Light.cpp
)

target_include_directories(Game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/thirdparty
)

# -------------------------
# Link libraries
# -------------------------

target_link_libraries(Game PRIVATE
    glad
    glfw
    OpenGL::GL
    glm::glm
    quark
)
