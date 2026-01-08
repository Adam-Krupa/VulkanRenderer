cmake_minimum_required(VERSION 3.21)
project(VulcanEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vulkan
find_package(Vulkan REQUIRED)

# ŹRÓDŁA
file(GLOB_RECURSE ENGINE_SRC
    src/*.cpp
    Main.cpp
)

add_executable(VulcanEngine ${ENGINE_SRC})

# INCLUDE
target_include_directories(VulcanEngine PRIVATE
    include
)

# Conan packages
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(VulcanEngine PRIVATE
    glfw
    glm::glm
    Vulkan::Vulkan
)

# Shaders / Assets (opcjonalnie później)
