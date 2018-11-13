# NomadECS
Nomad ECS is an entity component system implemention. More information about this project can be found on its homepage: https://savas.ca/nomad. Star this repo if you're a fan!

## Install
This repository can be built by itself, but the easiest way to use it is alongside [Conan.io](https://conan.io/)

The package is hosted on Bintray: https://bintray.com/taurheim/nomad/NomadECS:taurheim

1. Follow the instructions here: https://docs.conan.io/en/latest/installation.html
1. Run `conan remote add nomad https://api.bintray.com/conan/taurheim/nomad`

Try building the example project by following instructions in the `example/` folder

## Disclaimer
This repository is still a work in progress - It's actually a simplified port of the more complex game engine I'm developing. This means that it might not cover every edge case or be the most performant in every scenario, instead it is primarily designed to show off ECS concepts and to accompany my blog posts at https://savas.ca/nomad.

Among the things still left to be done in this repo are:
- Fix memory ownership and add destructors
- Add unit tests
- Add component garbage collection (+ Blog post)
- Write demo game (+ Blog post)
- Support multiple worlds (+ Blog post)

Feel free to add issues for features that need adding or bugs that come up!
