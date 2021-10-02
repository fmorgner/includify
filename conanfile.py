from conans import ConanFile, CMake


class Includify(ConanFile):
    name = "includify"
    version = "1.0.0"
    license = "BSD-3-clause"
    description = "A tool to convert arbitrary files into includable C++ headers"
    url = "https://github.com/fmorgner/includify"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [False, True]
    }
    default_options = {
        "shared": False
    }
    exports_sources = "source/*"
    generators = "cmake"
    build_requires = [
        "catch2/[~=2.13]",
        "cmake/[~=3.21]",
        "fmt/[~=8.0]",
        "lyra/[~=1.5]",
    ]

    _cmake = None

    @property
    def cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = True
            self._cmake.configure(source_folder="source")
        return self._cmake
        

    def build(self):
        self.cmake.build()
        self.cmake.test(output_on_failure=True)

    def package(self):
        self.cmake.install()
        self.copy("LICENSE", dst="licenses", keep_path=False)
