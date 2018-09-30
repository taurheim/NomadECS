# Building the example project
Make sure you've added the remote into conan (see the main README.md) before building the example project

## CMake & GCC (Shell)
If using the shell:
mkdir build && cd build
conan install ..
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .

## MSVC (Visual Studio 2017)
Follow instructions here: https://docs.conan.io/en/latest/integrations/visual_studio.html