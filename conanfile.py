import re
import subprocess
import sys

from conans import CMake, ConanFile


class Includify(ConanFile):
    name = "includify"
    version = "1.0.0"
    license = "BSD-3-Clause"
    description = "A tool to convert arbitrary files into includable C++ headers"
    url = "https://github.com/fmorgner/includify"
    settings = {
        "os": None,
        "compiler": {
            "gcc": {
                "version": ["11", "11.1"],
                "libcxx": ["libstdc++11"],
                "cppstd": ["20", "23"],
            },
            "apple-clang": None,
        },
        "build_type": None,
        "arch": ["x86_64"],
    }
    options = {"shared": [False, True]}
    default_options = {"shared": False}
    exports_sources = "source/*"
    generators = "cmake"
    build_requires = [
        "catch2/[~=2.13]",
        "fmt/[~=8.0]",
        "lyra/[~=1.5]",
    ]

    _cmake = None

    @property
    def cmake(self) -> CMake:
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = True
            self._cmake.configure(source_folder="source")
        return self._cmake

    def build_requirements(self) -> None:
        compiler = self.settings.get_safe("compiler")
        real_compiler_version = subprocess.run(
            ["clang" if compiler == "apple-clang" else compiler, "--version"],
            capture_output=True,
            text=True,
            check=True,
        )
        gcc_version_pattern = re.compile(
            r"^\s*gcc\s*\([^)]*\)\s*([0-9]+\.[0-9]+\.[0-9]+)\s*$"
        )
        for line in real_compiler_version.stdout.splitlines():
            match = gcc_version_pattern.match(line)
            if match is not None:
                print(f"Found GCC version: {match.group(1)}")
                return

        print(real_compiler_version.stdout)
        sys.exit("Failed compiler check!")

    def build(self) -> None:
        self.cmake.build()
        self.cmake.test(output_on_failure=True)

    def package(self) -> None:
        self.cmake.install()
        self.copy("LICENSE", dst="licenses", keep_path=False)
