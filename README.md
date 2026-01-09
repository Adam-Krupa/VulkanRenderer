# VulkanRenderer
You need to have VulkanSDK installed, if you dont have one yet you can install it via:
```cmd
winget install Khronos.VulkanSDK
```
then go into root dir of the project with main.cpp file
type:
```cmd
conan install . --output-folder=. --build=missing
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=./generators/conan_toolchain.cmake
```
and done project built
