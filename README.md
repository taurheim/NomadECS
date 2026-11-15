# NomadECS
Nomad ECS is an entity component system implemention. More information about this project can be found on its homepage: https://savas.ca/nomad. Star this repo if you're a fan!

## Install
NomadECS is a plain CMake project (CMake 3.14+, C++14) with no dependencies. It provides the target `nomadecs::nomadecs`; headers are included as `#include "nomadecs/nomad.h"`.

### FetchContent
```cmake
include(FetchContent)
FetchContent_Declare(nomadecs
  GIT_REPOSITORY https://github.com/taurheim/NomadECS.git
  GIT_TAG master) # pin a commit hash for reproducible builds
FetchContent_MakeAvailable(nomadecs)

target_link_libraries(mygame PRIVATE nomadecs::nomadecs)
```

`add_subdirectory(path/to/NomadECS)` works the same way.

### Installed package
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
cmake --install build --config Release --prefix <install-dir>
```
Then, with `<install-dir>` on `CMAKE_PREFIX_PATH`:
```cmake
find_package(nomadecs 0.0.5 CONFIG REQUIRED)
target_link_libraries(mygame PRIVATE nomadecs::nomadecs)
```

### Example
Building this repository directly also builds the example in `example/` (disable with `-DNOMADECS_BUILD_EXAMPLE=OFF`):
```
cmake -S . -B build
cmake --build build
./build/example/nomadexample
```

## Disclaimer
This repository is still a work in progress - It's actually a simplified port of the more complex game engine I'm developing. This means that it might not cover every edge case or be the most performant in every scenario, instead it is primarily designed to show off ECS concepts and to accompany my blog posts at https://savas.ca/nomad.

Among the things still left to be done in this repo are:
- Fix memory ownership and add destructors
- Add unit tests
- Add component garbage collection (+ Blog post)
- Write demo game (+ Blog post)
- Support multiple worlds (+ Blog post)

Feel free to add issues for features that need adding or bugs that come up!
