from conans import ConanFile, CMake, tools


class NomadEcsConan(ConanFile):
    name = "NomadECS"
    version = "0.0.2"
    license = "MIT"
    url = "https://github.com/taurheim/nomadecs"
    homepage = "https://savas.ca/nomad"
    blog = "https://medium.com/@savas"
    description = "Barebones entity component system for game engines"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = "src/*"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="src")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include/nomadecs", src="src")
        self.copy("*nomadecs.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["nomadecs"]

