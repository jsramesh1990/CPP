# Abstraction in C++ (Object-Oriented Programming)

## Table of Contents

1. [Introduction](#introduction)
2. [What is Abstraction?](#what-is-abstraction)
3. [Why do we use Abstraction?](#why-do-we-use-abstraction)
4. [Real-Time Example](#real-time-example)
5. [How Abstraction Works](#how-abstraction-works)
6. [Types of Abstraction](#types-of-abstraction)
7. [Data Abstraction](#data-abstraction)
8. [Control Abstraction](#control-abstraction)
9. [Abstract Classes](#abstract-classes)
10. [Pure Virtual Functions](#pure-virtual-functions)
11. [Interface-Based Abstraction](#interface-based-abstraction)
12. [Abstraction vs Encapsulation](#abstraction-vs-encapsulation)
13. [How Abstraction Works Internally](#how-abstraction-works-internally)
14. [Abstraction in Embedded Systems](#abstraction-in-embedded-systems)
15. [Advantages and Disadvantages](#advantages-and-disadvantages)
16. [Interview Questions](#interview-questions)
17. [Conclusion](#conclusion)

---

# Introduction

Abstraction is one of the four pillars of Object-Oriented Programming (OOP).

```text
1. Encapsulation
2. Abstraction
3. Inheritance
4. Polymorphism
```

Abstraction helps us focus on:

```text
What an object does
NOT
How it does it
```

---

# What is Abstraction?

### Definition

> Abstraction is the process of hiding implementation details and showing only the essential features to the user.

---

## Simple Meaning

```text
Hide Complexity
Show Functionality
```

Users interact with features without knowing internal implementation.

---

# Why do we use Abstraction?

✔ Reduces Complexity

✔ Improves Security

✔ Easier Maintenance

✔ Better Code Reusability

✔ Hardware Independence

✔ Simplifies Development

✔ Supports Scalable Design

---

# Real-Time Example

## Car Example

When driving a car:

```text
You Know:
✔ Steering
✔ Brake
✔ Accelerator
```

You Do NOT Need To Know:

```text
✘ Engine Timing
✘ Fuel Injection
✘ Transmission Logic
✘ ECU Algorithms
```

This is abstraction.

---

## Mobile Phone Example

You use:

```text
Call()
Message()
Internet()
```

Without knowing:

```text
Baseband Processing
Signal Encoding
Protocol Stacks
```

---

# How Abstraction Works

Abstraction hides:

```text
Implementation Details
```

and exposes:

```text
Interfaces
```

---

## Diagram

```text
User
  ↓
Interface
  ↓
Implementation
```

---

# Types of Abstraction

```text
Abstraction
      |
      +----------------+
      |                |
Data Abstraction   Control Abstraction
```

---

# Data Abstraction

Hiding internal data representation.

---

## Example

```cpp
class BankAccount
{
private:
    int balance;

public:
    void deposit(int amount)
    {
        balance += amount;
    }

    int getBalance()
    {
        return balance;
    }
};
```

---

### User Can Access

```cpp
deposit();
getBalance();
```

---

### User Cannot Access

```cpp
balance
```

Directly.

---

# Control Abstraction

Hiding execution logic.

---

## Example

```cpp
uart.send("Hello");
```

User only sees:

```cpp
send();
```

---

Internally:

```text
Buffer Creation
DMA Setup
Interrupt Configuration
Transmission Logic
```

are hidden.

---

# Abstract Classes

### Definition

> A class containing at least one pure virtual function is called an abstract class.

---

## Example

```cpp
class Sensor
{
public:
    virtual float read() = 0;
};
```

---

## Characteristics

✔ Cannot create object

✔ Acts as interface

✔ Supports abstraction

---

## Invalid

```cpp
Sensor s;
```

Compilation error.

---

# Pure Virtual Functions

### Syntax

```cpp
virtual void show() = 0;
```

---

## Example

```cpp
class UART
{
public:
    virtual void send() = 0;
};
```

---

Derived classes must implement it.

---

# Interface-Based Abstraction

Most common modern approach.

---

## Interface

```cpp
class UART
{
public:
    virtual void send() = 0;
};
```

---

## STM32 Implementation

```cpp
class STM32_UART : public UART
{
public:
    void send() override
    {
        cout << "STM32 UART";
    }
};
```

---

## ESP32 Implementation

```cpp
class ESP32_UART : public UART
{
public:
    void send() override
    {
        cout << "ESP32 UART";
    }
};
```

---

## Application Code

```cpp
UART* uart;

uart->send();
```

---

Benefit:

```text
Application Does Not Know
Which Hardware Is Used
```

---

# Abstraction vs Encapsulation

Most Asked Interview Question

| Abstraction                                | Encapsulation                    |
| ------------------------------------------ | -------------------------------- |
| Hides implementation                       | Hides data                       |
| Focuses on what                            | Focuses on how data is protected |
| Achieved using abstract classes/interfaces | Achieved using access specifiers |
| User perspective                           | Developer perspective            |

---

## Example

### Encapsulation

```cpp
private:
    int balance;
```

Protecting data.

---

### Abstraction

```cpp
deposit();
withdraw();
```

Hiding internal working.

---

# How Abstraction Works Internally

## Example

```cpp
UART* uart = new STM32_UART();

uart->send();
```

---

### Internal Flow

```text
Application
     ↓
UART Interface
     ↓
Virtual Function
     ↓
vTable Lookup
     ↓
STM32_UART::send()
```

---

## What Happens When Code Hits This?

```cpp
uart->send();
```

### Internally

```text
1. Base pointer accessed
2. vPtr checked
3. vTable located
4. Correct implementation found
5. Function executed
```

---

# Abstraction in Embedded Systems

Abstraction is one of the most important concepts in embedded software.

---

# 1. Hardware Abstraction Layer (HAL)

```cpp
class GPIO
{
public:
    virtual void setPin() = 0;
};
```

---

Implementations:

```cpp
STM32_GPIO
ESP32_GPIO
NXP_GPIO
```

---

Application:

```cpp
gpio->setPin();
```

---

Benefit:

```text
Same Application
Different Hardware
```

---

# 2. Driver Frameworks

```cpp
class Sensor
{
public:
    virtual float read() = 0;
};
```

---

Derived Drivers

```text
Temperature Sensor
Pressure Sensor
Humidity Sensor
```

---

# 3. Automotive Systems

Used in:

* AUTOSAR
* ECU Services
* CAN Drivers
* Diagnostic Modules
* ADAS Systems

---

# 4. Embedded Linux

Used in:

* Device Drivers
* Middleware
* Service Layers
* Application Frameworks

---

# Advantages and Disadvantages

## Advantages

✔ Reduced Complexity

✔ Better Security

✔ Easier Maintenance

✔ Hardware Independence

✔ Scalability

✔ Cleaner Architecture

✔ Reusability

---

## Disadvantages

✘ Additional Design Complexity

✘ More Classes Required

✘ Virtual Function Overhead

✘ Slight Memory Increase

---

# Interview Questions

## What is Abstraction?

Abstraction is the process of hiding implementation details and exposing only essential functionality.

---

## Why is Abstraction Used?

To reduce complexity and provide a clean interface to users.

---

## How is Abstraction Achieved in C++?

Using:

```text
1. Abstract Classes
2. Pure Virtual Functions
3. Interfaces
```

---

## What is an Abstract Class?

A class containing at least one pure virtual function.

---

## Can We Create an Object of an Abstract Class?

No.

---

## What is a Pure Virtual Function?

A function declared using:

```cpp
virtual void show() = 0;
```

---

## What Happens When Code Hits This?

```cpp
uart->send();
```

### Answer

```text
1. vPtr accessed
2. vTable checked
3. Correct implementation found
4. Function executed
```

---

## Difference Between Abstraction and Encapsulation?

```text
Abstraction:
Hides Implementation

Encapsulation:
Hides Data
```

---

## Why is Abstraction Important in Embedded Systems?

Abstraction allows application code to remain independent of hardware-specific implementations, improving portability and maintainability.

---

# Most Asked Interview Question

## Explain Abstraction with a Real-Time Example.

Abstraction is the process of hiding implementation details while exposing only necessary functionality. For example, in a Hardware Abstraction Layer (HAL), an application calls `uart->send()` without knowing whether the hardware is STM32, ESP32, or NXP. The application interacts with a common interface, while hardware-specific details remain hidden. This reduces complexity, improves portability, and allows the same application code to run on different platforms.

---

# Interview Answer (2-Minute Version)

Abstraction is an OOP concept that hides implementation details and exposes only essential features. In C++, abstraction is achieved using abstract classes and pure virtual functions. It allows developers to interact with interfaces instead of implementation details. In embedded systems, abstraction is commonly used in HAL layers, sensor frameworks, and automotive software, enabling hardware-independent application development. Abstraction improves maintainability, scalability, and code reusability.

---

# Quick Revision

```text
Abstraction
      ↓
Hide Complexity
Show Functionality

Achieved Using:
✔ Abstract Classes
✔ Pure Virtual Functions
✔ Interfaces

Abstract Class:
Contains Pure Virtual Function

Syntax:
virtual void func() = 0;

Used In:
- HAL
- Drivers
- Sensors
- AUTOSAR
- Embedded Linux

Difference:
Abstraction → Hides Implementation
Encapsulation → Hides Data
```

---

# Conclusion

Abstraction is a fundamental OOP principle that simplifies software by hiding implementation details and exposing only necessary functionality. It is heavily used in embedded systems, hardware abstraction layers, driver development, automotive software, and framework design. Mastering abstraction is essential for writing scalable, maintainable, and portable C++ applications and is a frequently asked topic in technical interviews.
