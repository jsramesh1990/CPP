# Polymorphism in C++ (Object-Oriented Programming)

## Table of Contents

1. [Introduction](#introduction)
2. [What is Polymorphism?](#what-is-polymorphism)
3. [Why do we use Polymorphism?](#why-do-we-use-polymorphism)
4. [Real-Time Example](#real-time-example)
5. [Types of Polymorphism](#types-of-polymorphism)

   1. [Compile-Time Polymorphism](#compile-time-polymorphism)
   2. [Run-Time Polymorphism](#run-time-polymorphism)
6. [Function Overloading](#function-overloading)
7. [Operator Overloading](#operator-overloading)
8. [Virtual Functions](#virtual-functions)
9. [Method Overriding](#method-overriding)
10. [How Polymorphism Works Internally](#how-polymorphism-works-internally)
11. [vTable and vPtr](#vtable-and-vptr)
12. [Polymorphism in Embedded Systems](#polymorphism-in-embedded-systems)
13. [Advantages and Disadvantages](#advantages-and-disadvantages)
14. [Interview Questions](#interview-questions)
15. [Conclusion](#conclusion)

---

# Introduction

Polymorphism is one of the four pillars of OOP.

```text
1. Encapsulation
2. Abstraction
3. Inheritance
4. Polymorphism
```

The word Polymorphism comes from:

```text
Poly = Many

Morph = Forms
```

Meaning:

```text
One Interface
Many Forms
```

---

# What is Polymorphism?

### Definition

> Polymorphism is the ability of a function, object, or interface to take multiple forms depending on the context.

---

## Simple Meaning

Same function call can produce different behaviors.

---

## Example

```cpp
start();
```

May start:

```text
Car Engine
Bike Engine
Truck Engine
```

depending on the object.

---

# Why do we use Polymorphism?

✔ Code Reusability

✔ Flexibility

✔ Scalability

✔ Easy Maintenance

✔ Hardware Abstraction

✔ Common Interface

✔ Runtime Decision Making

---

# Real-Time Example

Consider a sensor framework.

Without polymorphism:

```cpp
readTemperature();
readPressure();
readHumidity();
```

Different APIs.

---

With polymorphism:

```cpp
sensor->read();
```

Same API.

Different behavior.

---

# Types of Polymorphism

```text
Polymorphism
    |
    +------------------+
    |                  |
Compile Time      Run Time
Polymorphism      Polymorphism
```

---

# Compile-Time Polymorphism

Also called:

```text
Static Polymorphism
Early Binding
```

Compiler decides function at compile time.

---

## Types

1. Function Overloading
2. Operator Overloading

---

# Function Overloading

Multiple functions with same name but different parameters.

---

## Example

```cpp
class Math
{
public:

    int add(int a, int b)
    {
        return a + b;
    }

    float add(float a, float b)
    {
        return a + b;
    }
};
```

---

## What Happens When Code Hits This?

```cpp
add(10,20);
```

Compiler selects:

```cpp
add(int,int)
```

at compile time.

---

# Operator Overloading

Allows operators to work with user-defined types.

---

## Example

```cpp
class Complex
{
public:
    int real;

    Complex operator +(Complex obj)
    {
        Complex temp;
        temp.real = real + obj.real;
        return temp;
    }
};
```

---

## Usage

```cpp
c3 = c1 + c2;
```

---

## Internally

```cpp
c3 = c1.operator+(c2);
```

---

# Run-Time Polymorphism

Also called:

```text
Dynamic Polymorphism
Late Binding
```

Decision happens during runtime.

---

## Achieved Using

```text
Inheritance
+
Virtual Functions
```

---

# Virtual Functions

Base class:

```cpp
class Vehicle
{
public:
    virtual void start()
    {
        cout << "Vehicle";
    }
};
```

---

Derived class:

```cpp
class Car : public Vehicle
{
public:
    void start() override
    {
        cout << "Car";
    }
};
```

---

# Method Overriding

Derived class replaces base class implementation.

---

## Example

```cpp
Vehicle* ptr = new Car();

ptr->start();
```

---

## Output

```text
Car
```

---

## Why?

Runtime identifies actual object type.

---

# How Polymorphism Works Internally

Most Asked Interview Topic

---

## Example

```cpp
Vehicle* ptr = new Car();

ptr->start();
```

---

## Internal Flow

```text
1. ptr is Vehicle*
2. Actual object is Car
3. vPtr accessed
4. vTable checked
5. Car::start() found
6. Function executed
```

---

# vTable and vPtr

## What is vTable?

A compiler-generated table storing addresses of virtual functions.

---

## What is vPtr?

A hidden pointer stored inside every object containing virtual functions.

---

## Diagram

```text
Car Object

+----------------+
| vPtr --------+ |
| Data Members | |
+--------------|-+
               |
               ▼

           vTable

+----------------------+
| Car::start()         |
| Car::stop()          |
+----------------------+
```

---

# What Happens When Code Hits This?

```cpp
ptr->start();
```

### Internally

```text
1. Object's vPtr accessed
2. vTable located
3. Function address retrieved
4. Correct function executed
```

---

# Compile-Time vs Run-Time Polymorphism

| Feature               | Compile Time | Run Time        |
| --------------------- | ------------ | --------------- |
| Binding               | Early        | Late            |
| Speed                 | Faster       | Slightly Slower |
| Uses Virtual Function | No           | Yes             |
| Flexibility           | Less         | More            |
| Example               | Overloading  | Overriding      |

---

# Polymorphism in Embedded Systems

Polymorphism is heavily used in modern embedded C++ projects.

---

# 1. Hardware Abstraction Layer (HAL)

Base Interface:

```cpp
class UART
{
public:
    virtual void send() = 0;
};
```

---

STM32 Implementation:

```cpp
class STM32_UART : public UART
{
};
```

---

ESP32 Implementation:

```cpp
class ESP32_UART : public UART
{
};
```

---

Application Code:

```cpp
UART* uart;

uart->send();
```

---

Benefit:

```text
Same API
Different Hardware
```

---

# 2. Sensor Framework

```cpp
class Sensor
{
public:
    virtual float read() = 0;
};
```

---

Derived Sensors:

```cpp
TemperatureSensor
PressureSensor
HumiditySensor
```

---

Usage:

```cpp
Sensor* sensor;

sensor->read();
```

---

# 3. Automotive Systems

Used in:

* AUTOSAR
* ECU Software
* Diagnostic Services
* CAN Drivers
* Sensor Modules

---

# 4. Embedded Linux

Used in:

* Device Drivers
* Middleware
* Service Frameworks

---

# Advantages and Disadvantages

## Advantages

✔ Flexibility

✔ Scalability

✔ Code Reuse

✔ Cleaner Architecture

✔ Hardware Abstraction

✔ Easy Maintenance

---

## Disadvantages

✘ Slight Runtime Overhead

✘ Extra Memory (vPtr)

✘ Increased Complexity

✘ More Debugging Effort

---

# Interview Questions

## What is Polymorphism?

Polymorphism is the ability of the same interface to behave differently based on the object type.

---

## Why is Polymorphism Used?

To improve flexibility, reusability, and scalability.

---

## How Many Types of Polymorphism Exist?

```text
1. Compile-Time Polymorphism
2. Run-Time Polymorphism
```

---

## What is Compile-Time Polymorphism?

Polymorphism resolved during compilation using function overloading or operator overloading.

---

## What is Run-Time Polymorphism?

Polymorphism resolved during execution using inheritance and virtual functions.

---

## What is Method Overriding?

A derived class providing its own implementation of a virtual function.

---

## What is vTable?

A compiler-generated table containing virtual function addresses.

---

## What is vPtr?

A hidden pointer inside an object that points to the vTable.

---

## What Happens When Code Hits This?

```cpp
ptr->start();
```

### Answer

```text
1. vPtr accessed
2. vTable checked
3. Actual object's function found
4. Function executed
```

---

## Why is Polymorphism Important in Embedded Systems?

Polymorphism allows the same application code to work with different hardware implementations, improving portability and maintainability.

---

# Most Asked Interview Question

## Explain Polymorphism with a Real-Time Example.

Polymorphism is the ability of the same interface to exhibit different behaviors based on the object type. For example, in an embedded Hardware Abstraction Layer, a base class `UART` defines a virtual `send()` function. Different microcontrollers such as STM32 and ESP32 implement their own versions of `send()`. The application uses a `UART*` pointer and calls `send()` without knowing the actual hardware. At runtime, the correct implementation is selected using virtual functions, enabling code portability and scalability.

---

# Interview Answer (2-Minute Version)

Polymorphism means "one interface, many forms." It allows the same function call to behave differently depending on the object type. C++ supports two types of polymorphism: compile-time polymorphism using function and operator overloading, and runtime polymorphism using inheritance and virtual functions. Runtime polymorphism works through vTables and vPtrs, allowing the program to select the correct function during execution. In embedded systems, polymorphism is widely used in HAL layers, drivers, sensor frameworks, and automotive software to create portable and maintainable code.

---

# Quick Revision

```text
Polymorphism
      ↓
One Interface
Many Forms

Types:
1. Compile-Time
   - Function Overloading
   - Operator Overloading

2. Run-Time
   - Inheritance
   - Virtual Functions

Internally:
Object
 ↓
vPtr
 ↓
vTable
 ↓
Correct Function

Used In:
- HAL
- Drivers
- Sensors
- AUTOSAR
- Embedded Linux
```

---

# Conclusion

Polymorphism is a fundamental OOP concept that allows software to be flexible, reusable, and scalable. Compile-time polymorphism provides efficiency through overloading, while runtime polymorphism enables dynamic behavior using virtual functions and inheritance. In embedded systems and automotive software, polymorphism is essential for hardware abstraction, driver development, and framework design, making it one of the most important C++ interview topics.
