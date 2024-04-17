# Walnut

Walnut is a simple application framework built with Dear ImGui and designed to be used with Vulkan - basically this means you can seemlessly blend real-time Vulkan rendering with a great UI library to build desktop applications. The plan is to expand Walnut to include common utilities to make immediate-mode desktop apps and simple Vulkan applications.

Currently supports Windows - with macOS and Linux support planned. Setup scripts support Visual Studio 2022 by default.

![WalnutExample](https://hazelengine.com/images/ForestLauncherScreenshot.jpg)
_<center>Forest Launcher - an application made with Walnut</center>_

## CMake
To use this with cmake you have to add the dependencies to your project / executable as shown below
```cmake
add_executable(walnut-cmake-example ${SOURCES})
target_link_libraries(walnut-cmake-example PRIVATE Walnut)
target_include_directories(walnut-cmake-example PRIVATE includes ../../deps/imgui ../../deps/GLFW/include ../../deps/Walnut/Source ../../deps/Walnut/Platform/GUI C:/VulkanSDK/1.3.268.0/Include ../../deps/glm)
```

you don't **NEED** all of those includes but to make the most out of it, I would advise it, please not that for some reason you will get some issues if you aren't compiling with mingw, i haven't tested all of them but i was trying to use a different version of GCC and it didn't work, your milage may vary.

## Requirements
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home#windows) (preferably a recent version)


### 3rd party libaries
- [Dear ImGui](https://github.com/ocornut/imgui)
- [GLFW](https://github.com/glfw/glfw)
- [stb_image](https://github.com/nothings/stb)
- [GLM](https://github.com/g-truc/glm) (included for convenience)

### Additional
- I haven't tested this on Linux or MacOS, I only know that it works on windows, again your milage may vary
- Walnut uses the [Roboto](https://fonts.google.com/specimen/Roboto) font ([Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0))

### Author
- CMake Addition     -  [bonsall2004](https://github.com/bonsall2004)
- Walnut             -  [StudioCherno](https://github.com/StudioCherno/Walnut)
