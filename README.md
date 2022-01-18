# open.mp Pawn native example

## Tools

* [CMake 3.19+](https://cmake.org/)
* [Conan 1.33+](https://conan.io/)

## Tools on Windows

* [Visual Studio 2019+](https://www.visualstudio.com/)

Visual Studio needs the `Desktop development with C++` workload with the `MSVC v142`, `Windows 10 SDK` and `C++ Clang tools for Windows` components.

## Sources

```bash
# With HTTPS:
git clone --recursive https://github.com/Cheaterman/open.mp-pawn-native-example.git
# With SSH:
git clone --recursive git@github.com:Cheaterman/open.mp-pawn-native-example.git
```

Note the use of the `--recursive` argument, because this repository contains submodules.

## Building on Windows

```bash
cd open.mp-pawn-native-example
mkdir build
cd build
cmake .. -A Win32 -T ClangCL
```

Open Visual Studio and build the solution.

## Building on Linux

```bash
cd open.mp-pawn-native-example
# Adjust CC/CXX to your clang/clang++ paths
./build.sh
```
