# Building the example project
Make sure you've added the remote into conan (see the main README.md) before building the example project

## CMake & GCC (Unix Shell or IDE with CMake support)
If using unix shell:

```
mkdir build && cd build
conan install ..
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

If you're using windows, both [Visual Studio 2017](https://docs.microsoft.com/en-us/cpp/ide/cmake-tools-for-visual-cpp?view=vs-2017) and [CLion](https://www.jetbrains.com/help/clion/quick-tutorial-on-configuring-clion-on-windows.html) have CMake support.

## MSVC (Visual Studio 2017)
Follow instructions here: https://docs.conan.io/en/latest/integrations/visual_studio.html

Make sure to change the `[generators]` to `visual_studio` in `conanfile.txt`