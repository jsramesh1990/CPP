# Dependency Management

## Table of Contents

1. [Introduction](#introduction)
2. [What is Dependency Management?](#what-is-dependency-management)
3. [Why Do We Need Dependency Management?](#why-do-we-need-dependency-management)
4. [Types of Dependencies](#types-of-dependencies)
5. [Direct vs Indirect Dependencies](#direct-vs-indirect-dependencies)
6. [Build-Time vs Run-Time Dependencies](#build-time-vs-run-time-dependencies)
7. [Dependency Management in C/C++](#dependency-management-in-cc)
8. [Dependency Management in CMake](#dependency-management-in-cmake)
9. [Dependency Resolution Process](#dependency-resolution-process)
10. [Static vs Dynamic Dependencies](#static-vs-dynamic-dependencies)
11. [Package Managers](#package-managers)
12. [Dependency Management in Embedded Linux](#dependency-management-in-embedded-linux)
13. [Dependency Management in Yocto](#dependency-management-in-yocto)
14. [Dependency Management in Automotive Software](#dependency-management-in-automotive-software)
15. [Version Management](#version-management)
16. [Common Dependency Problems](#common-dependency-problems)
17. [What Happens When Code Hits It?](#what-happens-when-code-hits-it)
18. [Real-Time Examples](#real-time-examples)
19. [Advantages and Disadvantages](#advantages-and-disadvantages)
20. [Interview Questions](#interview-questions)
21. [Quick Revision](#quick-revision)
22. [Conclusion](#conclusion)

---

# Introduction

Modern software is rarely built from scratch.

A project usually depends on:

```text
Libraries
Frameworks
Drivers
Middleware
Tools
SDKs
```

These external components are called **Dependencies**.

Managing them properly is called:

> **Dependency Management**

---

# What is Dependency Management?

Definition:

> Dependency Management is the process of identifying, tracking, downloading, configuring, building, linking, and maintaining software components required by an application.

---

Example:

```cpp
#include <opencv2/opencv.hpp>
#include <boost/asio.hpp>
```

Your application depends on:

```text
OpenCV
Boost
```

Without these libraries:

```text
Compilation Fails
Linking Fails
Application Fails
```

---

# Why Do We Need Dependency Management?

Imagine a project using:

```text
OpenCV
Boost
Qt
Pthread
SQLite
```

Manually managing:

```text
Library Paths
Header Paths
Versions
Build Options
Updates
```

becomes difficult.

Dependency management automates:

✔ Library Discovery

✔ Version Control

✔ Build Integration

✔ Package Installation

✔ Dependency Resolution

✔ Runtime Availability

---

# Types of Dependencies

---

## Internal Dependencies

Created within project.

Example:

```text
Camera Module
    ↓
Logging Module
```

---

## External Dependencies

Third-party libraries.

Example:

```text
OpenCV
Boost
Qt
SQLite
gRPC
```

---

# Direct vs Indirect Dependencies

---

## Direct Dependency

Application directly uses library.

```cpp
#include <opencv2/opencv.hpp>
```

Dependency:

```text
OpenCV
```

---

## Indirect Dependency

OpenCV itself may require:

```text
JPEG Library
PNG Library
Zlib
```

Your application doesn't use them directly.

Still required.

---

Example

```text
App
 ↓
OpenCV
 ↓
JPEG
 ↓
Zlib
```

---

# Build-Time vs Run-Time Dependencies

| Type       | Required When      |
| ---------- | ------------------ |
| Build-Time | During Compilation |
| Run-Time   | During Execution   |

---

## Build-Time Dependency

Example:

```cpp
#include <opencv2/opencv.hpp>
```

Need headers during compilation.

---

## Run-Time Dependency

Example:

```text
libopencv_core.so
```

Needed when application starts.

---

# Dependency Management in C/C++

Unlike Python or Java:

```text
No Built-in Dependency Manager
```

Common solutions:

```text
CMake
Conan
vcpkg
Yocto
APT
RPM
```

---

# Dependency Management in CMake

Example:

```cmake
find_package(OpenCV REQUIRED)

target_link_libraries(
    app
    PRIVATE
    ${OpenCV_LIBS}
)
```

---

What happens?

```text
CMake Searches OpenCV
 ↓
Find Headers
 ↓
Find Libraries
 ↓
Configure Build
```

---

# Dependency Resolution Process

Dependency resolution means:

> Finding all required dependencies and their versions.

---

Example

```text
Application
     ↓
OpenCV
     ↓
JPEG
     ↓
Zlib
```

System checks:

```text
Is OpenCV Installed?
Is JPEG Installed?
Is Zlib Installed?
```

---

If anything missing:

```text
Build Failure
```

---

# Static vs Dynamic Dependencies

---

## Static Dependency

Library copied into executable.

```text
Application
 + Library Code
 ↓
Single Binary
```

---

Example

```text
libmath.a
```

---

Advantages

✔ No External Dependency

✔ Easier Deployment

---

Disadvantages

✘ Larger Binary

---

## Dynamic Dependency

Library loaded at runtime.

```text
Application
 ↓
libmath.so
```

---

Advantages

✔ Smaller Binary

✔ Shared Libraries

---

Disadvantages

✘ Runtime Dependency Required

---

# Package Managers

Package managers automate dependency installation.

---

## Linux APT

Install OpenCV:

```bash
sudo apt install libopencv-dev
```

---

## RPM

Used in:

```text
RedHat
CentOS
Fedora
```

---

## Conan

Popular C++ package manager.

```bash
conan install .
```

---

Features:

```text
Version Control
Dependency Resolution
Cross Compilation
```

---

## vcpkg

Microsoft-supported C++ package manager.

```bash
vcpkg install boost
```

---

# Dependency Management in Embedded Linux

Embedded Linux projects often depend on:

```text
Qt
OpenCV
Boost
SQLite
Poco
```

---

Challenges:

```text
ARM Architecture
Cross Compilation
Limited Storage
Version Control
```

---

Need:

```text
Build Dependency
Runtime Dependency
Target Dependency
```

---

# Dependency Management in Yocto

Most Important Embedded Topic.

Yocto automatically handles dependencies.

---

Recipe Example

```bitbake
DEPENDS = "opencv"
```

Meaning:

```text
Build OpenCV First
Then Build My Application
```

---

Runtime Dependency

```bitbake
RDEPENDS:${PN} += "opencv"
```

Meaning:

```text
Install OpenCV
Before Running App
```

---

# Dependency Management in Automotive Software

Automotive systems depend on:

```text
Diagnostics
CAN Stack
Ethernet Stack
Security Libraries
Middleware
```

---

Example

```text
ADAS Application
      ↓
OpenCV
      ↓
TensorRT
      ↓
CUDA
```

All dependencies must match versions.

---

# Version Management

One of the biggest challenges.

---

Example

Application requires:

```text
OpenCV 4.8
```

System has:

```text
OpenCV 3.4
```

Result:

```text
Compilation Failure
Runtime Failure
```

---

Best Practice

```text
Lock Versions
Use Package Managers
Document Requirements
```

---

# Common Dependency Problems

---

## Missing Library

```text
Library Not Installed
```

Error:

```bash
cannot find -lopencv_core
```

---

## Missing Header

```bash
opencv.hpp: No such file
```

---

## Version Conflict

Library A:

```text
Boost 1.70
```

Library B:

```text
Boost 1.82
```

Conflict occurs.

---

## Runtime Error

Executable builds successfully.

But:

```bash
./app
```

Error:

```bash
libopencv_core.so not found
```

---

# What Happens When Code Hits It?

Example:

```cmake
find_package(OpenCV REQUIRED)
```

Execution:

```text
1. Search OpenCV

2. Find Include Paths

3. Find Libraries

4. Verify Version

5. Configure Build
```

---

Example:

```cmake
target_link_libraries(
    app
    OpenCV
)
```

Execution:

```text
1. Link OpenCV

2. Generate Build Files

3. Compile

4. Create Executable
```

---

At Runtime:

```bash
./app
```

Execution:

```text
1. Loader Starts

2. Searches Shared Libraries

3. Loads Dependencies

4. Resolves Symbols

5. Application Runs
```

---

# Real-Time Examples

## Example 1: Camera Application

```text
Camera App
    ↓
OpenCV
    ↓
JPEG
    ↓
Zlib
```

Dependency chain.

---

## Example 2: Embedded Linux

```text
Application
    ↓
Qt
    ↓
OpenGL
```

All required before execution.

---

## Example 3: ROS2

```text
ROS Node
     ↓
rclcpp
     ↓
FastDDS
```

Dependencies automatically resolved by build system.

---

## Example 4: Automotive ADAS

```text
ADAS
 ↓
OpenCV
 ↓
CUDA
 ↓
TensorRT
```

All versions must match.

---

# Advantages and Disadvantages

## Advantages

✔ Faster Development

✔ Code Reuse

✔ Reduced Maintenance

✔ Easier Updates

✔ Better Modularity

✔ Automated Builds

---

## Disadvantages

✘ Version Conflicts

✘ Dependency Hell

✘ Large Dependency Trees

✘ Runtime Issues

✘ Security Risks in Third-Party Libraries

---

# Interview Questions

## What is Dependency Management?

Dependency management is the process of handling external and internal software components required by an application during build time and runtime.

---

## Why Do We Need Dependency Management?

To automate dependency installation, version control, linking, and build integration while avoiding manual configuration errors.

---

## What is a Dependency?

A library, framework, SDK, or module that another software component requires to function.

---

## Difference Between Direct and Indirect Dependency?

| Direct              | Indirect                |
| ------------------- | ----------------------- |
| Used by Application | Used by Another Library |
| Explicitly Included | Automatically Required  |

---

## Difference Between DEPENDS and RDEPENDS in Yocto?

| DEPENDS                   | RDEPENDS                |
| ------------------------- | ----------------------- |
| Build-Time Dependency     | Runtime Dependency      |
| Needed During Compilation | Needed During Execution |

---

## What Happens When Code Hits It?

### Example

```cmake
find_package(OpenCV REQUIRED)
```

### Answer

```text
1. Search Package

2. Validate Installation

3. Find Headers

4. Find Libraries

5. Configure Build System
```

---

## What is Dependency Hell?

A situation where multiple libraries require incompatible versions of the same dependency.

---

## Difference Between Static and Dynamic Dependency?

| Static                     | Dynamic                   |
| -------------------------- | ------------------------- |
| Linked at Build Time       | Linked at Runtime         |
| Large Binary               | Small Binary              |
| No External Library Needed | Shared Libraries Required |

---

# Most Asked Interview Question

## Explain Dependency Management in an Embedded Linux Project.

In Embedded Linux, applications often depend on multiple libraries such as OpenCV, Qt, Boost, and middleware components. Dependency management ensures that all required libraries, headers, and runtime packages are available during build and execution. Tools like CMake, Yocto, Conan, and package managers automatically resolve dependencies, manage versions, and ensure compatibility across target architectures such as ARM. Proper dependency management reduces build failures, runtime errors, and maintenance effort.

---

# Interview Answer (2-Minute Version)

Dependency Management is the process of handling all software components required by an application, including libraries, frameworks, SDKs, and internal modules. It ensures that dependencies are correctly installed, versioned, linked, and available at runtime. In C++ and Embedded Linux environments, tools such as CMake, Conan, vcpkg, and Yocto are commonly used. Proper dependency management prevents version conflicts, missing libraries, and build failures while improving software maintainability and portability.

---

# Quick Revision

```text
Dependency Management

Purpose:
Manage Required Libraries

Types:
1. Internal
2. External

Dependencies:
1. Direct
2. Indirect

Timing:
1. Build-Time
2. Run-Time

Tools:
✔ CMake
✔ Conan
✔ vcpkg
✔ Yocto
✔ APT

Yocto:
DEPENDS  → Build-Time
RDEPENDS → Run-Time

Problems:
✔ Missing Library
✔ Missing Header
✔ Version Conflict
✔ Dependency Hell

Embedded Linux:
✔ OpenCV
✔ Qt
✔ Boost
✔ Middleware
✔ Drivers
```

---

# Conclusion

Dependency Management is a critical software engineering practice that ensures all required libraries, frameworks, and modules are correctly integrated into a project. It plays a vital role in C++, Embedded Linux, Automotive, ROS2, and large-scale software systems. Mastering dependency management concepts, package managers, CMake integration, and Yocto dependency handling is essential for both development and technical interviews.
