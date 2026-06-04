# Templates in C++ (Generic Programming)

## Table of Contents

1. [Introduction](#introduction)
2. [What are Templates?](#what-are-templates)
3. [Why do we use Templates?](#why-do-we-use-templates)
4. [How Templates Work](#how-templates-work)
5. [Function Templates](#function-templates)
6. [Class Templates](#class-templates)
7. [Template Specialization](#template-specialization)
8. [Partial Specialization](#partial-specialization)
9. [Variadic Templates](#variadic-templates)
10. [Template Instantiation](#template-instantiation)
11. [Templates vs Macros](#templates-vs-macros)
12. [Templates in Embedded Systems](#templates-in-embedded-systems)
13. [Advantages and Disadvantages](#advantages-and-disadvantages)
14. [Interview Questions](#interview-questions)
15. [Conclusion](#conclusion)

---

# Introduction

Templates are one of the most powerful features of C++.

They enable:

```text
Generic Programming
```

which means:

```text
Write Once
Use for Multiple Data Types
```

Without templates, we often write duplicate code for different data types.

---

# What are Templates?

### Definition

> Templates allow functions and classes to operate with generic data types instead of specific data types.

---

## Simple Meaning

Instead of writing:

```cpp
int add(int a, int b);
float add(float a, float b);
double add(double a, double b);
```

We write:

```cpp
template<typename T>
T add(T a, T b);
```

One function works for all types.

---

# Why do we use Templates?

✔ Code Reusability

✔ Type Safety

✔ Reduced Code Duplication

✔ Better Performance

✔ Compile-Time Optimization

✔ Generic Libraries

---

## Real-Time Example

Without Template:

```cpp
int max(int a, int b);
float max(float a, float b);
double max(double a, double b);
```

---

With Template:

```cpp
template<typename T>
T max(T a, T b);
```

Single implementation.

---

# How Templates Work

Templates are processed at compile time.

---

## Flow

```text
Template Definition
        ↓
Compiler Sees Usage
        ↓
Specific Function Generated
        ↓
Executable Created
```

---

## Example

```cpp
template<typename T>
T add(T a, T b)
{
    return a + b;
}
```

Usage:

```cpp
add(10,20);
```

Compiler generates:

```cpp
int add(int,int)
{
    return a+b;
}
```

---

# Function Templates

Most common template type.

---

## Syntax

```cpp
template<typename T>
return_type function_name(parameters)
{
}
```

---

## Example

```cpp
#include <iostream>
using namespace std;

template<typename T>
T add(T a, T b)
{
    return a + b;
}

int main()
{
    cout << add(10,20) << endl;

    cout << add(10.5,20.5);
}
```

---

## Output

```text
30
31
```

---

## What Happens When Code Hits This?

```cpp
add(10,20);
```

### Internally

```text
1. Compiler sees T = int
2. Creates int version
3. Function executes
4. Returns result
```

---

# Class Templates

Templates can also create generic classes.

---

## Syntax

```cpp
template<typename T>
class ClassName
{
};
```

---

## Example

```cpp
template<typename T>
class Storage
{
private:
    T value;

public:

    void set(T v)
    {
        value = v;
    }

    T get()
    {
        return value;
    }
};
```

---

## Usage

```cpp
Storage<int> s1;

Storage<float> s2;
```

---

## What Happens Internally?

Compiler creates:

```cpp
Storage<int>
Storage<float>
```

separately.

---

# Template Specialization

Used when a specific type requires special behavior.

---

## Generic Template

```cpp
template<typename T>
class Printer
{
public:
    void print()
    {
        cout << "Generic";
    }
};
```

---

## Specialized Template

```cpp
template<>
class Printer<char>
{
public:
    void print()
    {
        cout << "Character";
    }
};
```

---

## Usage

```cpp
Printer<int> p1;

Printer<char> p2;
```

---

Output:

```text
Generic
Character
```

---

# Partial Specialization

Specializes only part of template parameters.

---

## Example

```cpp
template<typename T, typename U>
class Pair
{
};
```

---

Specialization:

```cpp
template<typename T>
class Pair<T,int>
{
};
```

---

Useful for advanced generic programming.

---

# Variadic Templates

Introduced in C++11.

Allows variable number of arguments.

---

## Example

```cpp
template<typename... Args>
void print(Args... args)
{
}
```

---

## Usage

```cpp
print(10);

print(10,20);

print(10,20,"ABC");
```

---

## Why?

Flexible argument handling.

Used heavily in STL and libraries.

---

# Template Instantiation

### Definition

The process of generating actual code from a template.

---

## Example

```cpp
add(10,20);
```

Compiler creates:

```cpp
int add(int,int);
```

---

Usage:

```cpp
add(2.5,4.5);
```

Compiler creates:

```cpp
double add(double,double);
```

---

## Important Interview Point

Templates do NOT exist in final executable.

Only instantiated versions exist.

---

# Templates vs Macros

| Template            | Macro              |
| ------------------- | ------------------ |
| Type Safe           | Not Type Safe      |
| Checked by Compiler | Text Replacement   |
| Debuggable          | Difficult to Debug |
| Supports Classes    | No                 |
| Modern C++          | Legacy C Feature   |

---

## Macro Example

```cpp
#define MAX(a,b) ((a)>(b)?(a):(b))
```

---

## Template Example

```cpp
template<typename T>
T max(T a,T b)
{
    return (a>b)?a:b;
}
```

Templates are preferred.

---

# Templates in Embedded Systems

Templates are heavily used in modern embedded C++.

---

# 1. GPIO Drivers

```cpp
template<int PIN>
class GPIO
{
public:
    void set()
    {
    }
};
```

---

Usage:

```cpp
GPIO<13> led;
```

---

Benefit:

```text
Compile-Time Configuration
No Runtime Overhead
```

---

# 2. UART Drivers

```cpp
template<int BaudRate>
class UART
{
};
```

---

Usage:

```cpp
UART<115200> uart;
```

---

# 3. Sensor Frameworks

```cpp
template<typename SensorType>
class SensorManager
{
};
```

---

Supports:

```text
Temperature Sensor
Pressure Sensor
Humidity Sensor
```

---

# 4. Automotive Software

Used in:

* AUTOSAR
* ECU Software
* CAN Drivers
* Communication Stacks

---

# 5. Embedded Linux

Used in:

* Middleware
* Frameworks
* STL Containers

---

# Advantages and Disadvantages

## Advantages

✔ Code Reusability

✔ Type Safety

✔ Compile-Time Optimization

✔ No Runtime Cost

✔ Generic Programming

✔ Better Maintainability

---

## Disadvantages

✘ Larger Compile Time

✘ Complex Error Messages

✘ Increased Binary Size

✘ Difficult for Beginners

---

# Interview Questions

## What is a Template?

A template is a mechanism that allows writing generic functions and classes that work with multiple data types.

---

## Why are Templates Used?

To avoid code duplication and support generic programming.

---

## What is a Function Template?

A generic function that works with different data types.

---

## What is a Class Template?

A generic class that works with different data types.

---

## What is Template Specialization?

Providing a custom implementation for a specific data type.

---

## What is Variadic Template?

A template that accepts a variable number of arguments.

---

## What Happens When Code Hits This?

```cpp
add(10,20);
```

### Answer

```text
1. Compiler deduces T = int
2. Creates int version
3. Executes function
4. Returns result
```

---

## Are Templates Runtime or Compile-Time Features?

Compile-Time.

---

## Why are Templates Faster Than Virtual Functions?

Templates generate direct code at compile time, while virtual functions require runtime vTable lookups.

---

# Most Asked Interview Question

## Explain Templates with a Real-Time Example.

Templates allow writing generic code that works with multiple data types without duplication. For example, a single template function `add()` can operate on integers, floats, and doubles. During compilation, the compiler generates specific versions of the function for each data type used. In embedded systems, templates are commonly used for compile-time hardware configuration, GPIO drivers, UART drivers, and sensor frameworks because they provide flexibility without runtime overhead.

---

# Interview Answer (2-Minute Version)

Templates are a C++ feature that supports generic programming by allowing functions and classes to operate on multiple data types. They eliminate code duplication and improve maintainability. Templates are processed at compile time, where the compiler generates type-specific versions through template instantiation. Common types include function templates, class templates, template specialization, and variadic templates. In embedded systems, templates are widely used for compile-time configuration and zero-overhead abstractions, making them more efficient than many runtime techniques.

---

# Quick Revision

```text
Templates
      ↓
Generic Programming

Purpose:
✔ Reuse Code
✔ Type Safety
✔ Compile-Time Optimization

Types:
1. Function Template
2. Class Template
3. Template Specialization
4. Variadic Template

Syntax:
template<typename T>

Internally:
Template
   ↓
Instantiation
   ↓
Generated Code

Used In:
- GPIO Drivers
- UART Drivers
- Sensor Frameworks
- AUTOSAR
- Embedded Linux
- STL
```

---

# Conclusion

Templates are one of the most powerful features in C++, enabling generic programming, type safety, and high-performance abstractions. They allow developers to write reusable code that works with multiple data types while maintaining compile-time efficiency. In embedded systems, templates are extensively used for hardware abstraction, compile-time configuration, and zero-overhead design patterns, making them a critical topic for advanced C++ development and technical interviews.
