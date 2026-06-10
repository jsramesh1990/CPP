# C++20 Features (The Biggest C++ Update Since C++11)

## Table of Contents

1. [Introduction](#introduction)
2. [Why C++20 Was Introduced](#why-c20-was-introduced)
3. [Major C++20 Features Overview](#major-c20-features-overview)
4. [Concepts](#concepts)
5. [Requires Clause](#requires-clause)
6. [Ranges Library](#ranges-library)
7. [Coroutines](#coroutines)
8. [Modules](#modules)
9. [Three-Way Comparison Operator (Spaceship)](#three-way-comparison-operator-spaceship)
10. [Designated Initializers](#designated-initializers)
11. [consteval](#consteval)
12. [constinit](#constinit)
13. [Enhanced constexpr](#enhanced-constexpr)
14. [Lambda Improvements](#lambda-improvements)
15. [std::span](#stdspan)
16. [jthread](#jthread)
17. [Source Location](#source-location)
18. [Format Library](#format-library)
19. [How C++20 Works Internally](#how-c20-works-internally)
20. [C++20 in Embedded Systems](#c20-in-embedded-systems)
21. [Advantages and Disadvantages](#advantages-and-disadvantages)
22. [Interview Questions](#interview-questions)
23. [Quick Revision](#quick-revision)
24. [Conclusion](#conclusion)

---

# Introduction

C++20 was released in:

```text
2020
```

It is considered:

```text
The Biggest C++ Update Since C++11
```

because it introduced major language changes such as:

* Concepts
* Coroutines
* Modules
* Ranges
* Three-Way Comparison

---

# Why C++20 Was Introduced

Previous versions had issues:

```text
Complex Templates
Long Compilation Times
Poor Error Messages
Header File Problems
Complex Iteration Logic
```

Goals:

✔ Better Template Programming

✔ Faster Compilation

✔ Cleaner Code

✔ Better Concurrency

✔ Safer Programming

✔ Improved STL

---

# Major C++20 Features Overview

```text
1. Concepts
2. Requires Clause
3. Ranges
4. Coroutines
5. Modules
6. Spaceship Operator
7. Designated Initializers
8. consteval
9. constinit
10. Enhanced constexpr
11. Lambda Improvements
12. std::span
13. jthread
14. source_location
15. format
```

---

# Concepts

Most Important C++20 Feature.

---

## Problem Before C++20

Template errors were huge.

```cpp
template<typename T>
T add(T a, T b)
{
    return a + b;
}
```

If type doesn't support `+`:

```text
Hundreds of lines of compiler errors
```

---

## C++20 Solution

```cpp
#include <concepts>

template<typename T>
requires std::integral<T>
T add(T a, T b)
{
    return a + b;
}
```

---

## What Happens When Code Hits This?

```cpp
add(10,20);
```

Compiler checks:

```text
Is T integral?
```

If yes:

```text
Compile
```

Else:

```text
Compilation Error
```

with clear message.

---

## Benefits

✔ Cleaner Errors

✔ Safer Templates

✔ Better Readability

---

# Requires Clause

Used with Concepts.

---

Example

```cpp
template<typename T>
requires (sizeof(T) > 4)
void process(T value)
{
}
```

---

Compiler verifies condition at compile time.

---

Useful for:

```text
Template Restrictions
API Validation
Generic Libraries
```

---

# Ranges Library

Most Used Modern STL Feature.

---

Before

```cpp
std::sort(
v.begin(),
v.end()
);
```

---

C++20

```cpp
std::ranges::sort(v);
```

---

Filtering Example

```cpp
auto result =
v
| std::views::filter(
[](int x)
{
    return x % 2 == 0;
});
```

---

Output

```text
Only Even Numbers
```

---

## Benefits

✔ Cleaner Code

✔ Functional Style

✔ Safer Iteration

---

# Coroutines

Most Asked Interview Topic

---

Allows:

```text
Pause Function
Resume Function
```

without blocking thread.

---

Example

```cpp
task readSensor()
{
    co_await sensorReady();
}
```

---

Keywords

```cpp
co_await
co_yield
co_return
```

---

## Real-Time Example

Sensor driver:

```text
Read Sensor
      ↓
Wait for Data
      ↓
Continue Later
```

without blocking CPU.

---

## Benefits

✔ Asynchronous Programming

✔ Better Performance

✔ Less Thread Overhead

---

# Modules

Replaces Header Files.

---

## Before

```cpp
#include "sensor.h"
```

Problems:

```text
Slow Compilation
Macro Issues
Duplicate Parsing
```

---

## C++20

Module File

```cpp
export module sensor;
```

---

Use

```cpp
import sensor;
```

---

Benefits

✔ Faster Build Times

✔ Better Encapsulation

✔ No Header Problems

---

# Three-Way Comparison Operator (Spaceship)

Symbol:

```cpp
<=>
```

---

Before

Need:

```cpp
==
!=
<
>
<=
>=
```

all separately.

---

C++20

```cpp
class Data
{
public:

auto operator<=>
(const Data&) const = default;
};
```

---

Compiler generates all comparisons.

---

## Benefits

✔ Less Code

✔ Consistent Comparisons

---

# Designated Initializers

Inspired by C.

---

Before

```cpp
struct Sensor
{
    int id;
    float value;
};

Sensor s{1,25.5};
```

---

C++20

```cpp
Sensor s
{
    .id = 1,
    .value = 25.5
};
```

---

Benefits

✔ Readability

✔ Fewer Initialization Errors

---

# consteval

Forces compile-time execution.

---

Example

```cpp
consteval int square(int x)
{
    return x*x;
}
```

---

Usage

```cpp
constexpr int x =
square(5);
```

---

Compiler computes:

```text
25
```

during compilation.

---

## Difference

| Feature   | Meaning                  |
| --------- | ------------------------ |
| constexpr | Compile-time if possible |
| consteval | Compile-time mandatory   |

---

# constinit

Guarantees static initialization.

---

Example

```cpp
constinit int counter = 0;
```

---

Used for:

```text
Global Variables
Embedded Systems
Startup Safety
```

---

# Enhanced constexpr

C++20 greatly expanded constexpr.

---

Now supports:

```text
Loops
Conditions
Dynamic Allocations (limited)
More STL Support
```

---

Example

```cpp
constexpr int factorial(int n)
{
    int result = 1;

    for(int i=1;i<=n;i++)
    {
        result *= i;
    }

    return result;
}
```

---

# Lambda Improvements

Template Lambdas.

---

Example

```cpp
auto func =
[]<typename T>(T value)
{
};
```

---

Benefits

✔ Cleaner Generic Code

✔ Better Type Control

---

# std::span

Most Important Embedded Feature

---

Problem

Passing arrays:

```cpp
void process(
int* data,
size_t size
);
```

---

Issues:

```text
Size Mismatch
Unsafe Access
```

---

C++20

```cpp
void process(
std::span<int> data
);
```

---

Usage

```cpp
int arr[5];

process(arr);
```

---

Benefits

✔ Safe Array Access

✔ No Copy

✔ Size Included

---

# jthread

Improved thread class.

---

Before

```cpp
std::thread t(func);
```

Need:

```cpp
t.join();
```

manually.

---

C++20

```cpp
std::jthread t(func);
```

Automatically joins.

---

Benefits

✔ RAII

✔ Safer Threading

---

# Source Location

Get file and line information.

---

Example

```cpp
#include <source_location>

void log(
const std::source_location&
loc =
std::source_location::current()
)
{
}
```

---

Provides:

```text
File Name
Line Number
Function Name
```

---

Useful for:

```text
Logging
Debugging
Diagnostics
```

---

# Format Library

Modern replacement for printf.

---

Example

```cpp
#include <format>

std::format(
"Value = {}",
100
);
```

Output

```text
Value = 100
```

---

Benefits

✔ Type Safe

✔ Cleaner Syntax

✔ Faster Development

---

# How C++20 Works Internally

## Concepts

```cpp
requires std::integral<T>
```

Compiler checks constraints before template instantiation.

---

## std::span

```cpp
std::span<int>
```

Internally stores:

```text
Pointer
Length
```

---

## Modules

```cpp
import sensor;
```

Compiler loads precompiled module instead of reparsing header files.

---

# C++20 in Embedded Systems

Widely Used In:

```text
Embedded Linux
AUTOSAR Adaptive
ROS2
Middleware
High-Performance Systems
```

---

# Example 1: Sensor Framework

```cpp
std::span<uint8_t>
packet;
```

Safe packet access.

---

# Example 2: CAN Protocol

```cpp
std::ranges
```

for message filtering.

---

# Example 3: Diagnostics

```cpp
std::source_location
```

for logging.

---

# Example 4: Async Sensor Reads

```cpp
co_await
```

for non-blocking operations.

---

# Example 5: Automotive Middleware

Used in:

* Adaptive AUTOSAR
* Infotainment
* OTA Updates
* Diagnostics

---

# Advantages and Disadvantages

## Advantages

✔ Better Template Programming

✔ Faster Compilation (Modules)

✔ Cleaner STL

✔ Better Concurrency

✔ Safer Arrays

✔ Easier Maintenance

✔ Modern Design

---

## Disadvantages

✘ Requires New Compiler

✘ Steeper Learning Curve

✘ Coroutine Complexity

✘ Partial Compiler Support on Older Toolchains

---

# Interview Questions

## What is the Biggest C++20 Feature?

Most interviewers expect:

```text
Concepts
```

or

```text
Coroutines
```

or

```text
Modules
```

---

## What Happens When Code Hits This?

```cpp
template<typename T>
requires std::integral<T>
```

### Answer

Compiler verifies whether T satisfies the integral concept before generating template code.

---

## Difference Between constexpr and consteval?

| constexpr                | consteval              |
| ------------------------ | ---------------------- |
| Compile-time if possible | Compile-time mandatory |
| Flexible                 | Strict                 |

---

## What is std::span?

A lightweight, non-owning view of contiguous memory that stores a pointer and size.

---

## Why Are Modules Better Than Headers?

Modules eliminate repeated parsing, reduce compile times, and improve encapsulation.

---

## What Are Coroutines?

Functions that can suspend and resume execution without blocking threads.

---

## Why Use Concepts?

To constrain template parameters and provide better compile-time diagnostics.

---

# Most Asked Interview Question

## Explain Important C++20 Features Used in Embedded Systems.

C++20 introduced several features that significantly improve embedded software development. Concepts provide safer template programming with clear compile-time validation. `std::span` offers safe access to arrays and buffers without copying data, making it ideal for communication stacks and sensor drivers. Coroutines enable efficient asynchronous operations such as non-blocking sensor reads and network communication. Modules reduce build times and improve code organization. `std::source_location` simplifies diagnostics and logging. These features help create safer, faster, and more maintainable embedded and automotive applications.

---

# Interview Answer (2-Minute Version)

C++20 is one of the most significant updates to the language since C++11. It introduced concepts, requires clauses, ranges, coroutines, modules, the spaceship operator, designated initializers, consteval, constinit, enhanced constexpr, std::span, jthread, source_location, and the format library. Concepts improve template safety, coroutines simplify asynchronous programming, modules reduce compilation times, and std::span provides safer buffer handling. In embedded Linux, AUTOSAR Adaptive, middleware, and robotics applications, these features improve performance, maintainability, and reliability while reducing code complexity.

---

# Quick Revision

```text
C++20 Features

1. Concepts
2. Requires Clause
3. Ranges
4. Coroutines
5. Modules
6. Spaceship Operator
7. Designated Initializers
8. consteval
9. constinit
10. Enhanced constexpr
11. Lambda Improvements
12. std::span
13. jthread
14. source_location
15. format

Most Important:
✔ Concepts
✔ Coroutines
✔ Modules
✔ std::span
✔ Ranges

Embedded Usage:
✔ Sensor Drivers
✔ Communication Stacks
✔ Middleware
✔ Embedded Linux
✔ AUTOSAR Adaptive
✔ Robotics
```

---

# Conclusion

C++20 represents a major leap forward in modern C++ development. Features such as Concepts, Coroutines, Modules, Ranges, and `std::span` address long-standing challenges related to template complexity, asynchronous programming, compilation speed, and memory safety. These improvements are especially valuable in Embedded Linux, Automotive, Middleware, Robotics, and High-Performance Computing. Understanding C++20 features is increasingly important for modern C++ developers and is becoming a common topic in advanced technical interviews.
