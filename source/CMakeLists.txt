cmake_minimum_required(VERSION "3.21.0")

#[=====[ Basic Project Setup ]=====]

project("includify"
    LANGUAGES CXX
    VERSION "1.0.0"
    DESCRIPTION "A tool to convert arbitrary files into includable C++ headers"
)

enable_testing()

#[=====[ Conan Dependencies ]=====]

include("${PROJECT_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(TARGETS NO_OUTPUT_DIRS SKIP_STD)

#[=====[ CMake Dependencies ]=====]

include("Catch")

#[=====[ includify Library Target ]=====]

add_library("library"
    "${PROJECT_SOURCE_DIR}/lib/src/includify.cpp"
)

target_include_directories("library" PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features("library" PUBLIC
    "cxx_std_20"
)

target_compile_options("library" PRIVATE
    $<$<CXX_COMPILER_ID:Clang,GNU>:-Wall>
    $<$<CXX_COMPILER_ID:Clang,GNU>:-Wextra>
    $<$<CXX_COMPILER_ID:Clang,GNU>:-Werror>
    $<$<CXX_COMPILER_ID:Clang,GNU>:-pedantic-errors>
)

target_link_libraries("library" PUBLIC
    "CONAN_PKG::fmt"
)

set_target_properties("library" PROPERTIES
    "CXX_STANDARD_REQUIRED" YES
    "CXX_EXTENSIONS" OFF
    "OUTPUT_NAME" "includify"
)

add_library("includify::includify" ALIAS "library")

#[=====[ includify Executable Target ]=====]

add_executable("app"
    "${PROJECT_SOURCE_DIR}/app/src/main.cpp"
)

target_link_libraries("app" PRIVATE
    "includify::includify"
    "CONAN_PKG::lyra"
)

target_compile_options("app" PRIVATE
    $<$<CXX_COMPILER_ID:Clang,GNU>:-Wall>
    $<$<CXX_COMPILER_ID:Clang,GNU>:-Wextra>
    $<$<CXX_COMPILER_ID:Clang,GNU>:-Werror>
    $<$<CXX_COMPILER_ID:Clang,GNU>:-pedantic-errors>
)

set_target_properties("app" PROPERTIES
    "CXX_STANDARD_REQUIRED" YES
    "CXX_EXTENSIONS" OFF
    "OUTPUT_NAME" "includify"
)

#[=====[ includify Unit Tests ]=====]

file(GLOB TEST_SOURCES RELATIVE "${PROJECT_SOURCE_DIR}" CONFIGURE_DEPENDS "test/src/*.cpp")

add_executable("tests"
    ${TEST_SOURCES}
)

target_include_directories("tests" PRIVATE
    "${PROJECT_SOURCE_DIR}/test/include"
)

target_link_libraries("tests" PRIVATE
    "includify::includify"
    "CONAN_PKG::catch2"
)

target_compile_options("tests" PRIVATE
    $<$<CXX_COMPILER_ID:Clang,GNU>:-Wall>
    $<$<CXX_COMPILER_ID:Clang,GNU>:-Wextra>
    $<$<CXX_COMPILER_ID:Clang,GNU>:-Werror>
    $<$<CXX_COMPILER_ID:Clang,GNU>:-pedantic-errors>
)

set_target_properties("tests" PROPERTIES
    "CXX_STANDARD_REQUIRED" YES
    "CXX_EXTENSIONS" OFF
    "OUTPUT_NAME" "unit-tests"
)

catch_discover_tests("tests")

#[=====[ includify Installation ]=====]

install(TARGETS "app" "library"
    EXPORT "${PROJECT_NAME}Targets"
    PUBLIC_HEADER DESTINATION "include"
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/lib/include/"
    DESTINATION "include"
)