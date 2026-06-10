# CMake

## Table of Contents

1. [Introduction](#introduction)
2. [What is CMake?](#what-is-cmake)
3. [Why Do We Need CMake?](#why-do-we-need-cmake)
4. [Build Process Overview](#build-process-overview)
5. [How CMake Works](#how-cmake-works)
6. [CMake Architecture](#cmake-architecture)
7. [CMakeLists.txt](#cmakeliststxt)
8. [Basic CMake Commands](#basic-cmake-commands)
9. [Building a Simple Project](#building-a-simple-project)
10. [Multiple Source Files](#multiple-source-files)
11. [Libraries in CMake](#libraries-in-cmake)
12. [Static vs Shared Libraries](#static-vs-shared-libraries)
13. [Include Directories](#include-directories)
14. [Target-Based CMake](#target-based-cmake)
15. [Cross Compilation](#cross-compilation)
16. [CMake for Embedded Linux](#cmake-for-embedded-linux)
17. [CMake Build Types](#cmake-build-types)
18. [Important CMake Commands](#important-cmake-commands)
19. [What Happens When Code Hits It?](#what-happens-when-code-hits-it)
20. [Real-Time Examples](#real-time-examples)
21. [Advantages and Disadvantages](#advantages-and-disadvantages)
22. [Interview Questions](#interview-questions)
23. [Quick Revision](#quick-revision)
24. [Conclusion](#conclusion)

---

# Introduction

**CMake** is one of the most widely used build systems in:

```text
C++
Embedded Linux
Automotive
ROS2
Qt
Linux Applications
Middleware
```

It helps developers:

```text
Generate Build Files
Compile Projects
Manage Dependencies
Support Multiple Platforms
```

---

# What is CMake?

Definition:

> CMake is a cross-platform build system generator that creates native build files such as Makefiles, Ninja files, Visual Studio projects, and Xcode projects.

---

## Important Point

CMake does NOT compile code directly.

It generates build files.

```text
Source Code
     ↓
CMake
     ↓
Makefile / Ninja
     ↓
Compiler
     ↓
Executable
```

---

# Why Do We Need CMake?

Without CMake:

```bash
g++ main.cpp sensor.cpp logger.cpp \
-Iinclude \
-o app
```

For large projects:

```text
100+ Source Files
10+ Libraries
Multiple Platforms
```

Managing manually becomes difficult.

---

CMake automates:

✔ Compilation

✔ Linking

✔ Dependencies

✔ Include Paths

✔ Library Management

✔ Cross Compilation

---

# Build Process Overview

```text
main.cpp
sensor.cpp
logger.cpp
      ↓
CMakeLists.txt
      ↓
CMake
      ↓
Makefile/Ninja
      ↓
g++
      ↓
app
```

---

# How CMake Works

Step 1

Create:

```text
CMakeLists.txt
```

---

Step 2

Run:

```bash
cmake .
```

---

Step 3

CMake generates:

```text
Makefile
```

or

```text
build.ninja
```

---

Step 4

Run:

```bash
make
```

or

```bash
ninja
```

---

Step 5

Compiler builds executable.

---

# CMake Architecture

```text
Source Files
      ↓
CMakeLists.txt
      ↓
CMake Engine
      ↓
Build Files
      ↓
Compiler
      ↓
Executable
```

---

# CMakeLists.txt

Main configuration file.

Every CMake project starts with:

```cmake
cmake_minimum_required(VERSION 3.20)

project(MyProject)

add_executable(app main.cpp)
```

---

## Explanation

### cmake_minimum_required()

Specifies minimum CMake version.

```cmake
cmake_minimum_required(VERSION 3.20)
```

---

### project()

Defines project name.

```cmake
project(CarCamera)
```

---

### add_executable()

Creates executable.

```cmake
add_executable(app main.cpp)
```

---

# Basic CMake Commands

---

## project()

```cmake
project(MyProject)
```

Creates project.

---

## add_executable()

```cmake
add_executable(app main.cpp)
```

Creates executable target.

---

## add_library()

```cmake
add_library(sensor STATIC sensor.cpp)
```

Creates library.

---

## target_link_libraries()

```cmake
target_link_libraries(app sensor)
```

Links libraries.

---

## target_include_directories()

```cmake
target_include_directories(
    app
    PRIVATE include
)
```

Adds header paths.

---

# Building a Simple Project

Directory:

```text
project/
│
├── main.cpp
└── CMakeLists.txt
```

---

main.cpp

```cpp
#include <iostream>

int main()
{
    std::cout<<"Hello";
}
```

---

CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.20)

project(HelloProject)

add_executable(
    hello
    main.cpp
)
```

---

Build

```bash
mkdir build

cd build

cmake ..

make
```

---

Run

```bash
./hello
```

Output

```text
Hello
```

---

# Multiple Source Files

Structure

```text
project/

main.cpp
sensor.cpp
sensor.h
```

---

CMake

```cmake
add_executable(
    app
    main.cpp
    sensor.cpp
)
```

---

CMake automatically compiles:

```text
main.cpp
sensor.cpp
```

and links them.

---

# Libraries in CMake

---

## Static Library

```cmake
add_library(
    sensor
    STATIC
    sensor.cpp
)
```

Output:

```text
libsensor.a
```

---

## Shared Library

```cmake
add_library(
    sensor
    SHARED
    sensor.cpp
)
```

Output:

```text
libsensor.so
```

---

# Static vs Shared Libraries

| Static               | Shared            |
| -------------------- | ----------------- |
| .a                   | .so               |
| Bigger Binary        | Smaller Binary    |
| Linked at Build Time | Linked at Runtime |
| Faster Startup       | Flexible Updates  |

---

# Include Directories

Headers:

```cpp
#include "sensor.h"
```

Need path.

---

Example

```cmake
target_include_directories(
    app
    PRIVATE
    include
)
```

---

Meaning:

```text
Compiler Searches

project/include
```

---

# Target-Based CMake

Modern CMake recommends:

```cmake
target_include_directories()

target_compile_options()

target_link_libraries()
```

instead of global settings.

---

Example

```cmake
target_link_libraries(
    app
    PRIVATE
    pthread
)
```

---

Benefits

✔ Cleaner

✔ Modular

✔ Scalable

---

# Cross Compilation

Most Important Embedded Topic.

---

Build on:

```text
x86 PC
```

Run on:

```text
ARM Board
```

---

Example

```text
Developer PC
      ↓
Cross Compiler
      ↓
ARM Executable
      ↓
Raspberry Pi
```

---

Toolchain File

```cmake
set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER arm-linux-gcc)

set(CMAKE_CXX_COMPILER arm-linux-g++)
```

---

Build

```bash
cmake \
-DCMAKE_TOOLCHAIN_FILE=toolchain.cmake
..
```

---

# CMake for Embedded Linux

Used heavily in:

```text
Yocto
ROS2
Automotive
Middleware
Qt Applications
```

---

Common Tasks

```text
Cross Compilation
Library Management
Package Integration
Dependency Tracking
```

---

# CMake Build Types

---

## Debug

```bash
cmake \
-DCMAKE_BUILD_TYPE=Debug
..
```

Includes:

```text
Debug Symbols
-g
```

---

## Release

```bash
cmake \
-DCMAKE_BUILD_TYPE=Release
..
```

Includes:

```text
Optimization
-O2
-O3
```

---

# Important CMake Commands

---

## message()

```cmake
message("Building...")
```

Prints message.

---

## set()

```cmake
set(VERSION 1.0)
```

Creates variable.

---

## find_package()

```cmake
find_package(OpenCV REQUIRED)
```

Finds library.

---

## install()

```cmake
install(
    TARGETS app
)
```

Installs executable.

---

# What Happens When Code Hits It?

## Example

```bash
cmake ..
```

Execution:

```text
1. Read CMakeLists.txt

2. Parse Commands

3. Check Compiler

4. Find Libraries

5. Generate Makefile
```

---

Then:

```bash
make
```

Execution:

```text
1. Read Makefile

2. Compile Sources

3. Create Object Files

4. Link Libraries

5. Generate Executable
```

---

# Real-Time Examples

## Example 1: Embedded Linux Application

```text
main.cpp
camera.cpp
network.cpp
```

CMake:

```cmake
add_executable(
    camera_app
    main.cpp
    camera.cpp
    network.cpp
)
```

---

## Example 2: ROS2

ROS2 packages use:

```text
CMake + colcon
```

---

Build

```bash
colcon build
```

Internally:

```text
CMake
↓
Make/Ninja
↓
Compiler
```

---

## Example 3: Automotive Middleware

Components:

```text
Diagnostics
CAN
Ethernet
Logging
```

Each module:

```cmake
add_library()
```

Final Application:

```cmake
target_link_libraries()
```

---

## Example 4: Yocto

Yocto recipes often invoke:

```bash
cmake
make
make install
```

to build packages.

---

# Advantages and Disadvantages

## Advantages

✔ Cross Platform

✔ Easy Dependency Management

✔ Supports Large Projects

✔ Embedded Friendly

✔ IDE Support

✔ Cross Compilation Support

✔ Industry Standard

---

## Disadvantages

✘ Learning Curve

✘ Syntax Can Be Confusing

✘ Debugging Build Issues Can Be Hard

---

# Interview Questions

## What is CMake?

CMake is a cross-platform build system generator that creates Makefiles, Ninja files, or IDE project files used to compile software.

---

## Why Do We Need CMake?

To automate compilation, linking, dependency management, and cross-platform builds.

---

## Does CMake Compile Code?

Most Important Interview Answer:

```text
NO
```

CMake generates build files.

Actual compilation is done by:

```text
gcc
g++
clang
MSVC
```

---

## What Happens When Code Hits It?

### Answer

```text
1. CMake Reads CMakeLists.txt

2. Generates Build Files

3. make/ninja Executes

4. Compiler Compiles Sources

5. Linker Creates Executable
```

---

## Difference Between Make and CMake?

| Make              | CMake                  |
| ----------------- | ---------------------- |
| Build Tool        | Build System Generator |
| Uses Makefile     | Generates Makefile     |
| Platform Specific | Cross Platform         |

---

## What is add_executable()?

Creates executable target.

```cmake
add_executable(app main.cpp)
```

---

## What is target_link_libraries()?

Links required libraries.

```cmake
target_link_libraries(app pthread)
```

---

## What is Cross Compilation?

Building software on one architecture and running it on another.

Example:

```text
Build: x86 PC

Run: ARM Board
```

---

## Why is CMake Popular in Embedded Linux?

Because it supports:

```text
Cross Compilation
Library Management
Large Projects
Yocto
ROS2
Qt
```

---

# Most Asked Interview Question

## Explain the Complete CMake Build Flow.

A developer writes source code and a `CMakeLists.txt` file describing the project structure. Running `cmake` parses the configuration and generates native build files such as Makefiles or Ninja files. When `make` or `ninja` is executed, the compiler compiles source files into object files and the linker combines them into an executable or library. CMake itself does not compile code; it generates the instructions used by the actual build tools.

---

# Interview Answer (2-Minute Version)

CMake is a cross-platform build system generator widely used in C++, Embedded Linux, ROS2, Qt, and Automotive software. Developers describe the project using a `CMakeLists.txt` file. CMake then generates platform-specific build files such as Makefiles or Ninja files. These build files invoke compilers and linkers to build executables and libraries. CMake simplifies dependency management, supports cross compilation, integrates with IDEs, and is heavily used in large-scale embedded and automotive projects.

---

# Quick Revision

```text
CMake

Purpose:
Generate Build Files

Does It Compile?
NO

Flow:
Source Code
    ↓
CMakeLists.txt
    ↓
CMake
    ↓
Makefile/Ninja
    ↓
Compiler
    ↓
Executable

Important Commands:
1. project()
2. add_executable()
3. add_library()
4. target_link_libraries()
5. target_include_directories()
6. find_package()

Embedded Usage:
✔ Yocto
✔ ROS2
✔ Qt
✔ Automotive
✔ Embedded Linux

Most Important:
CMake Generates
Build Files

Compiler Builds Code
```

---

# Conclusion

CMake is the industry-standard build system generator for modern C++ and Embedded Linux development. It simplifies project management, dependency handling, library integration, and cross compilation. Understanding `CMakeLists.txt`, targets, libraries, and build workflows is essential for Embedded Linux, Automotive, Middleware, ROS2, and modern C++ interviews, where questions about build systems are very common.
