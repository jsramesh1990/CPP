# Inheritance in C++ (Object-Oriented Programming)

## Table of Contents

1. [Introduction](#introduction)
2. [What is Inheritance?](#what-is-inheritance)
3. [Why do we use Inheritance?](#why-do-we-use-inheritance)
4. [Real-Time Example](#real-time-example)
5. [Syntax](#syntax)
6. [How Inheritance Works Internally](#how-inheritance-works-internally)
7. [Types of Inheritance](#types-of-inheritance)

   1. [Single Inheritance](#single-inheritance)
   2. [Multiple Inheritance](#multiple-inheritance)
   3. [Multilevel Inheritance](#multilevel-inheritance)
   4. [Hierarchical Inheritance](#hierarchical-inheritance)
   5. [Hybrid Inheritance](#hybrid-inheritance)
8. [Access Specifiers in Inheritance](#access-specifiers-in-inheritance)
9. [Constructor and Destructor Call Order](#constructor-and-destructor-call-order)
10. [Method Overriding](#method-overriding)
11. [The Diamond Problem](#the-diamond-problem)
12. [Virtual Inheritance](#virtual-inheritance)
13. [Inheritance in Embedded Systems](#inheritance-in-embedded-systems)
14. [Advantages and Disadvantages](#advantages-and-disadvantages)
15. [Interview Questions](#interview-questions)
16. [Conclusion](#conclusion)

---

# Introduction

Inheritance is one of the four pillars of Object-Oriented Programming (OOP).

```text
1. Encapsulation
2. Abstraction
3. Inheritance
4. Polymorphism
```

Inheritance allows a class to acquire properties and behaviors of another class.

---

# What is Inheritance?

### Definition

> Inheritance is a mechanism in C++ by which one class acquires the properties (data members) and behaviors (member functions) of another class.

---

## Simple Meaning

```text
Parent Class
      ↓
Child Class
```

The child automatically gets access to parent features.

---

## Real-Life Example

```text
Vehicle
   ↓
Car
   ↓
Electric Car
```

---

### Vehicle Properties

```text
speed
start()
stop()
```

---

### Car Gets Automatically

```text
speed
start()
stop()
```

plus its own features.

---

# Why do we use Inheritance?

✔ Code Reusability

✔ Reduced Code Duplication

✔ Easier Maintenance

✔ Extensible Design

✔ Supports Polymorphism

✔ Better Software Architecture

---

# Real-Time Example

Without inheritance:

```cpp
class Car
{
public:
    void start(){}
};

class Bike
{
public:
    void start(){}
};
```

Duplicate code.

---

With inheritance:

```cpp
class Vehicle
{
public:
    void start(){}
};

class Car : public Vehicle
{
};

class Bike : public Vehicle
{
};
```

Reusable code.

---

# Syntax

```cpp
class DerivedClass : access_specifier BaseClass
{
};
```

---

## Example

```cpp
class Vehicle
{
public:
    void start()
    {
        cout << "Vehicle Started";
    }
};

class Car : public Vehicle
{
};
```

---

# How Inheritance Works Internally

## Example

```cpp
Car c1;
```

---

### What Happens Internally?

```text
1. Memory allocated for Car
2. Base class members added
3. Derived class members added
4. Constructor chain executes
5. Object becomes ready
```

---

## Memory Layout

```text
Car Object

+----------------+
| Vehicle Data   |
+----------------+
| Car Data       |
+----------------+
```

Derived object contains base object.

---

# Types of Inheritance

# Single Inheritance

One parent and one child.

---

```cpp
class Vehicle
{
};

class Car : public Vehicle
{
};
```

---

## Diagram

```text
Vehicle
   ↓
 Car
```

---

# Multiple Inheritance

One child inherits from multiple parents.

---

```cpp
class Engine
{
};

class GPS
{
};

class Car : public Engine, public GPS
{
};
```

---

## Diagram

```text
Engine   GPS
    \   /
     Car
```

---

# Multilevel Inheritance

Inheritance chain.

---

```cpp
class Vehicle
{
};

class Car : public Vehicle
{
};

class SportsCar : public Car
{
};
```

---

## Diagram

```text
Vehicle
   ↓
 Car
   ↓
SportsCar
```

---

# Hierarchical Inheritance

One parent with multiple children.

---

```cpp
class Vehicle
{
};

class Car : public Vehicle
{
};

class Bike : public Vehicle
{
};
```

---

## Diagram

```text
      Vehicle
      /     \
    Car    Bike
```

---

# Hybrid Inheritance

Combination of multiple inheritance types.

---

```text
Vehicle
  ↓
Car
 / \
GPS Engine
```

---

# Access Specifiers in Inheritance

## Public Inheritance

```cpp
class Car : public Vehicle
{
};
```

---

### Conversion Table

| Base Member | Derived Access |
| ----------- | -------------- |
| public      | public         |
| protected   | protected      |
| private     | Not Accessible |

---

# Protected Inheritance

```cpp
class Car : protected Vehicle
{
};
```

---

| Base Member | Derived Access |
| ----------- | -------------- |
| public      | protected      |
| protected   | protected      |
| private     | Not Accessible |

---

# Private Inheritance

```cpp
class Car : private Vehicle
{
};
```

---

| Base Member | Derived Access |
| ----------- | -------------- |
| public      | private        |
| protected   | private        |
| private     | Not Accessible |

---

# Constructor and Destructor Call Order

Most Asked Interview Question

---

## Example

```cpp
class Vehicle
{
};

class Car : public Vehicle
{
};
```

---

## Object Creation

```cpp
Car c1;
```

---

### Constructor Order

```text
Vehicle Constructor
        ↓
Car Constructor
```

---

### Destructor Order

```text
Car Destructor
        ↓
Vehicle Destructor
```

---

## Easy Rule

```text
Construction:
Base → Derived

Destruction:
Derived → Base
```

---

# Method Overriding

Derived class provides its own implementation.

---

```cpp
class Vehicle
{
public:
    virtual void start()
    {
        cout << "Vehicle";
    }
};

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

# The Diamond Problem

Occurs in multiple inheritance.

---

## Example

```cpp
class A
{
};

class B : public A
{
};

class C : public A
{
};

class D : public B, public C
{
};
```

---

## Diagram

```text
      A
     / \
    B   C
     \ /
      D
```

---

### Problem

```text
D contains two copies of A
```

Ambiguity occurs.

---

# Virtual Inheritance

Solution for Diamond Problem.

---

## Example

```cpp
class A
{
};

class B : virtual public A
{
};

class C : virtual public A
{
};

class D : public B, public C
{
};
```

---

## Result

```text
Only One Copy Of A
```

---

# Inheritance in Embedded Systems

Inheritance is widely used in modern embedded C++.

---

# 1. Hardware Abstraction Layer (HAL)

```cpp
class UART
{
public:
    virtual void send() = 0;
};
```

---

## STM32 UART

```cpp
class STM32_UART : public UART
{
};
```

---

## ESP32 UART

```cpp
class ESP32_UART : public UART
{
};
```

---

## Benefit

Same API.

Different hardware implementation.

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

```cpp
class TemperatureSensor : public Sensor
{
};

class PressureSensor : public Sensor
{
};
```

---

# 3. Automotive Software

Used in:

* AUTOSAR Components
* CAN Drivers
* LIN Drivers
* ECU Services
* Diagnostics

---

# 4. Embedded Linux

Used in:

* Device Drivers
* Middleware
* Framework Design

---

# Advantages and Disadvantages

## Advantages

✔ Code Reusability

✔ Easy Maintenance

✔ Extensibility

✔ Better Organization

✔ Supports Polymorphism

✔ Reduced Duplication

---

## Disadvantages

✘ Increased Complexity

✘ Tight Coupling

✘ Diamond Problem

✘ More Memory Usage

✘ Deep Inheritance Hard to Maintain

---

# Interview Questions

## What is Inheritance?

Inheritance is a mechanism that allows one class to acquire properties and behaviors from another class.

---

## Why is Inheritance Used?

To promote code reuse and establish relationships between classes.

---

## How Many Types of Inheritance Exist?

```text
1. Single
2. Multiple
3. Multilevel
4. Hierarchical
5. Hybrid
```

---

## What is Method Overriding?

Providing a new implementation of a base class function in a derived class.

---

## What is the Diamond Problem?

When multiple inheritance creates multiple copies of the same base class, causing ambiguity.

---

## How is the Diamond Problem Solved?

Using virtual inheritance.

---

## What is Constructor Call Order?

```text
Base → Derived
```

---

## What is Destructor Call Order?

```text
Derived → Base
```

---

## What Happens When Code Hits This?

```cpp
Car c1;
```

### Internal Steps

```text
1. Memory allocated
2. Vehicle Constructor called
3. Car Constructor called
4. Object ready
```

---

# Most Asked Interview Question

## Explain Inheritance with a Real-Time Example.

Inheritance is an OOP mechanism that allows a derived class to reuse the properties and functions of a base class. For example, in an embedded Hardware Abstraction Layer, a base class `UART` may define common communication functions, while derived classes such as `STM32_UART` and `ESP32_UART` implement hardware-specific behavior. This approach improves code reuse, maintainability, and scalability while enabling polymorphism.

---

# Interview Answer (2-Minute Version)

Inheritance allows one class to inherit data members and member functions from another class. The existing class is called the base class, and the new class is called the derived class. It helps reduce code duplication, improves maintainability, and supports runtime polymorphism. Common types include single, multiple, multilevel, hierarchical, and hybrid inheritance. In embedded systems, inheritance is widely used in driver frameworks, HAL layers, sensor abstraction, and automotive software.

---

# Quick Revision

```text
Inheritance
      ↓
Code Reuse

Syntax:
class Child : public Parent

Types:
1. Single
2. Multiple
3. Multilevel
4. Hierarchical
5. Hybrid

Construction:
Base → Derived

Destruction:
Derived → Base

Problem:
Diamond Problem

Solution:
Virtual Inheritance

Used In:
- HAL
- Drivers
- Sensors
- AUTOSAR
- Embedded Linux
```

---

# Conclusion

Inheritance is one of the most important OOP concepts in C++. It enables code reuse, extensibility, and polymorphism by allowing derived classes to inherit features from base classes. In embedded systems, inheritance plays a key role in hardware abstraction, driver development, sensor frameworks, and automotive software architectures, making it a critical topic for both development and interviews.
