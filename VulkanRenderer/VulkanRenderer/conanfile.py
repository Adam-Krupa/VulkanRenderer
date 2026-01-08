from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class VulcanEngineConan(ConanFile):
    name = "vulcan-engine"
    version = "0.1"

    settings = "os", "compiler", "build_type", "arch"

    requires = (
        "glfw/3.3.8",
        "glm/0.9.9.8"
    )

    generators = ("CMakeDeps", "CMakeToolchain")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
