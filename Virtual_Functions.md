# Virtual Functions in C++ (Polymorphism)

## Table of Contents

1. [Introduction](#introduction)
2. [What is a Virtual Function?](#what-is-a-virtual-function)
3. [Why do we use Virtual Functions?](#why-do-we-use-virtual-functions)
4. [Need for Virtual Functions](#need-for-virtual-functions)
5. [How Virtual Functions Work Internally](#how-virtual-functions-work-internally)
6. [Syntax](#syntax)
7. [Example Without Virtual Function](#example-without-virtual-function)
8. [Example With Virtual Function](#example-with-virtual-function)
9. [vTable and vPtr](#vtable-and-vptr)
10. [Runtime Polymorphism](#runtime-polymorphism)
11. [Pure Virtual Functions](#pure-virtual-functions)
12. [Abstract Classes](#abstract-classes)
13. [Virtual Destructor](#virtual-destructor)
14. [Virtual Functions in Embedded Systems](#virtual-functions-in-embedded-systems)
15. [Advantages and Disadvantages](#advantages-and-disadvantages)
16. [Interview Questions](#interview-questions)
17. [Conclusion](#conclusion)

---

# Introduction

One of the most powerful features of C++ is **Polymorphism**.

Polymorphism means:

```text
One Interface
Multiple Behaviors
```

Virtual functions enable **Runtime Polymorphism**.

---

# What is a Virtual Function?

### Definition

> A virtual function is a member function declared with the `virtual` keyword in the base class and overridden in derived classes to achieve runtime polymorphism.

---

## Simple Meaning

A virtual function allows the program to decide **which function to call at runtime**, based on the actual object type.

---

# Why do we use Virtual Functions?

✔ Runtime Polymorphism

✔ Flexible Design

✔ Extensible Code

✔ Common Interface

✔ Dynamic Behavior Selection

✔ Widely used in Embedded Frameworks

---

# Need for Virtual Functions

Consider:

```cpp
class Animal
{
public:
    void sound()
    {
        cout << "Animal Sound";
    }
};

class Dog : public Animal
{
public:
    void sound()
    {
        cout << "Dog Bark";
    }
};
```

---

## Base Pointer

```cpp
Animal* ptr = new Dog();
ptr->sound();
```

---

## Output

```text
Animal Sound
```

---

### Problem

Even though the object is `Dog`, the base class function executes.

This happens because function binding occurs at compile time.

---

# How Virtual Functions Work Internally

Virtual functions enable:

```text
Late Binding
OR
Dynamic Binding
```

---

## Flow

```text
Base Pointer
     ↓
Actual Object Checked
     ↓
Correct Function Selected
     ↓
Function Executes
```

---

# Syntax

```cpp
class Base
{
public:
    virtual void show()
    {
    }
};
```

---

# Example Without Virtual Function

```cpp
#include <iostream>
using namespace std;

class Animal
{
public:
    void sound()
    {
        cout << "Animal Sound";
    }
};

class Dog : public Animal
{
public:
    void sound()
    {
        cout << "Dog Bark";
    }
};

int main()
{
    Animal* ptr = new Dog();

    ptr->sound();
}
```

---

## Output

```text
Animal Sound
```

---

## Why?

```text
Compiler sees:
Animal*

Calls:
Animal::sound()
```

---

# Example With Virtual Function

```cpp
#include <iostream>
using namespace std;

class Animal
{
public:
    virtual void sound()
    {
        cout << "Animal Sound";
    }
};

class Dog : public Animal
{
public:
    void sound() override
    {
        cout << "Dog Bark";
    }
};

int main()
{
    Animal* ptr = new Dog();

    ptr->sound();
}
```

---

## Output

```text
Dog Bark
```

---

## What Happens When Code Hits This?

```cpp
ptr->sound();
```

### Internally

```text
1. ptr is Animal*
2. Object is actually Dog
3. vPtr accessed
4. Dog::sound() found in vTable
5. Dog::sound() executed
```

---

# vTable and vPtr

Most Asked Interview Topic

---

## What is vTable?

> A Virtual Table (vTable) is a compiler-generated table containing addresses of virtual functions.

---

## What is vPtr?

> A Virtual Pointer (vPtr) is a hidden pointer added to objects that points to the class's vTable.

---

## Visualization

```text
Dog Object
+----------------+
| vPtr --------+ |
| data members | |
+--------------|-+
               |
               v

          vTable
    +----------------+
    | Dog::sound()   |
    | Dog::run()     |
    +----------------+
```

---

# Runtime Polymorphism

Virtual functions enable:

```cpp
Animal* ptr;

ptr = new Dog();
ptr = new Cat();
ptr = new Cow();
```

Same interface:

```cpp
ptr->sound();
```

Different outputs.

---

## Benefit

```text
Write Once
Use Many Behaviors
```

---

# Pure Virtual Functions

### Definition

A virtual function with no implementation.

---

## Syntax

```cpp
virtual void sound() = 0;
```

---

## Example

```cpp
class Animal
{
public:
    virtual void sound() = 0;
};
```

---

## Meaning

Derived classes MUST implement it.

---

# Abstract Classes

A class containing at least one pure virtual function.

---

## Example

```cpp
class Animal
{
public:
    virtual void sound() = 0;
};
```

---

## Invalid

```cpp
Animal a;
```

Cannot create object.

---

## Valid

```cpp
Dog d;
```

---

# Virtual Destructor

Always use virtual destructors in polymorphic base classes.

---

## Example

```cpp
class Base
{
public:
    virtual ~Base()
    {
    }
};
```

---

## Why?

```cpp
Base* ptr = new Derived();

delete ptr;
```

Without virtual destructor:

```text
Derived Destructor Not Called
```

Possible resource leak.

---

# Virtual Functions in Embedded Systems

Virtual functions are used in modern embedded C++ projects.

---

## 1. Hardware Abstraction Layer (HAL)

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
    }
};
```

---

## Benefit

Same API.

Different hardware implementations.

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

## Derived Sensors

```text
Temperature Sensor
Pressure Sensor
Humidity Sensor
```

---

# 3. Automotive Software

Used in:

* AUTOSAR Components
* Diagnostic Services
* Communication Stacks
* Sensor Abstraction

---

# 4. Embedded Linux

Used in:

* Device Drivers
* Middleware
* Framework Design

---

# Advantages and Disadvantages

## Advantages

✔ Runtime Polymorphism

✔ Extensible Design

✔ Hardware Abstraction

✔ Reusable Code

✔ Flexible Architecture

---

## Disadvantages

✘ Slight memory overhead (vPtr)

✘ Slight runtime overhead (vTable lookup)

✘ Increased code size

✘ Can be avoided in ultra-low-memory MCUs

---

# Interview Questions

## What is a Virtual Function?

A virtual function is a function declared using the `virtual` keyword that supports runtime polymorphism.

---

## Why Use Virtual Functions?

To call the correct derived class function through a base class pointer or reference.

---

## What is Runtime Polymorphism?

The decision of which function to execute is made at runtime.

---

## What is a vTable?

A compiler-generated table storing addresses of virtual functions.

---

## What is a vPtr?

A hidden pointer inside an object that points to the vTable.

---

## What Happens When a Virtual Function is Called?

```text
1. vPtr accessed
2. vTable checked
3. Correct function address found
4. Function executed
```

---

## What is a Pure Virtual Function?

A virtual function with no implementation:

```cpp
virtual void show() = 0;
```

---

## What is an Abstract Class?

A class containing at least one pure virtual function.

---

## Why Should Base Class Destructors Be Virtual?

To ensure derived class destructors execute correctly when deleting through a base pointer.

---

# Most Asked Interview Question

## Explain Virtual Functions with a Real-Time Example.

A virtual function is a member function declared with the `virtual` keyword in a base class that allows derived classes to override its behavior. When a virtual function is called through a base class pointer, the function corresponding to the actual object type is executed at runtime. For example, in an embedded hardware abstraction layer, a common UART interface may define a virtual `send()` function, while STM32 and ESP32 provide their own implementations. This allows the same application code to work across different hardware platforms without modification.

---

# Quick Revision

```text
Virtual Function
↓
Runtime Polymorphism

Keyword:
virtual

Internally:
Object → vPtr → vTable → Function

Important Topics:
✔ Runtime Polymorphism
✔ vTable
✔ vPtr
✔ Pure Virtual Function
✔ Abstract Class
✔ Virtual Destructor

Used In:
- HAL
- Drivers
- AUTOSAR
- Embedded Linux
```

---

# Conclusion

Virtual functions are a fundamental C++ feature that enables runtime polymorphism and flexible software architectures. They are heavily used in embedded systems, hardware abstraction layers, automotive software, and framework design. Understanding virtual functions, vTables, vPtrs, and abstract classes is essential for advanced C++ development and technical interviews.
