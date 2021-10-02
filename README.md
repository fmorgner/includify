# Includify!

*includify* is a tool to convert arbitrary files into includable C++ headers.

## Development Quick Start

*includify* relies on Conan and CMake for its build process.
To get started, make sure you have an up-to-date installation of both tools, and then run the following commands from the top level of your clone:

```bash
$ conan install --build=missing --install-folder=build .
$ conan build --build-folder=build .
```

After this point, you will be able to work on the project source code.
If you want to package *includify*, run the following command after the previous two

```bash
$ conan package --build-folder build .
```
