cmake_minimum_required(VERSION 3.21)

project(VulkanRenderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===== Conan toolchain =====
# (TEN PLIK JEST ŁADOWANY PRZY KONFIGURACJI)
# -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake

# ===== ZALEŻNOŚCI Z CONANA =====
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(vulkan-loader CONFIG REQUIRED)

# ===== ŹRÓDŁA =====
file(GLOB_RECURSE ENGINE_SRC
    src/*.cpp
)

add_executable(VulkanRenderer 
	${ENGINE_SRC}
	main.cpp
)

target_include_directories(VulkanRenderer PRIVATE
    include
)

# ===== LINKOWANIE =====
target_link_libraries(VulkanRenderer PRIVATE
    glm::glm
    glfw
    vulkan-loader::vulkan-loader
)