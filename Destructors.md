# Destructors in C++ (Object-Oriented Programming)

## Table of Contents

1. [Introduction](#introduction)
2. [What is a Destructor?](#what-is-a-destructor)
3. [Why do we use Destructors?](#why-do-we-use-destructors)
4. [Characteristics of Destructors](#characteristics-of-destructors)
5. [How Destructors Work Internally](#how-destructors-work-internally)
6. [Syntax](#syntax)
7. [Destructor Example](#destructor-example)
8. [Constructor vs Destructor](#constructor-vs-destructor)
9. [Destructor Call Order](#destructor-call-order)
10. [Virtual Destructors](#virtual-destructors)
11. [Pure Virtual Destructors](#pure-virtual-destructors)
12. [Destructors in Embedded Systems](#destructors-in-embedded-systems)
13. [Advantages and Disadvantages](#advantages-and-disadvantages)
14. [Interview Questions](#interview-questions)
15. [Conclusion](#conclusion)

---

# Introduction

When an object is created, a **constructor** initializes it.

When an object is destroyed, a **destructor** cleans up resources used by the object.

Destructors help prevent:

* Memory leaks
* Resource leaks
* File handle leaks
* Hardware resource locking

---

# What is a Destructor?

### Definition

> A destructor is a special member function that is automatically called when an object is destroyed.

---

## Simple Meaning

```text
Constructor → Object Starts Life

Destructor → Object Ends Life
```

---

## Real-Life Example

```text
Hotel Check-In  → Constructor

Hotel Check-Out → Destructor
```

When checking out, resources are released.

---

# Why do we use Destructors?

✔ Release memory

✔ Close files

✔ Release hardware resources

✔ Free dynamically allocated memory

✔ Prevent memory leaks

✔ Perform cleanup operations

---

# Characteristics of Destructors

### Rules

✔ Same name as class

✔ Prefixed with `~`

✔ No return type

✔ No parameters

✔ Automatically called

✔ Only one destructor per class

✔ Cannot be overloaded

---

# How Destructors Work Internally

## Example

```cpp
class Car
{
public:
    ~Car()
    {
        cout << "Destructor Called";
    }
};
```

---

## What Happens When Code Hits This?

```cpp
{
    Car c1;
}
```

### Internal Steps

```text
1. Object created
2. Constructor executes
3. Object used
4. Scope ends
5. Destructor automatically called
6. Memory released
```

---

# Syntax

```cpp
class ClassName
{
public:
    ~ClassName()
    {
        // Cleanup code
    }
};
```

---

# Destructor Example

## Simple Example

```cpp
#include <iostream>
using namespace std;

class Car
{
public:
    Car()
    {
        cout << "Constructor Called\n";
    }

    ~Car()
    {
        cout << "Destructor Called\n";
    }
};

int main()
{
    Car c1;
}
```

---

## Output

```text
Constructor Called
Destructor Called
```

---

## What Happens?

```text
main()
↓
Object Created
↓
Constructor Called
↓
Program Ends
↓
Destructor Called
```

---

# Constructor vs Destructor

| Constructor         | Destructor            |
| ------------------- | --------------------- |
| Initializes object  | Cleans object         |
| Called on creation  | Called on destruction |
| Same name as class  | `~ClassName()`        |
| Can be overloaded   | Cannot be overloaded  |
| Can have parameters | No parameters         |

---

# Destructor Call Order

## Single Object

```cpp
Car c1;
```

---

### Flow

```text
Constructor
↓
Object Usage
↓
Destructor
```

---

## Multiple Objects

```cpp
Car c1;
Car c2;
Car c3;
```

---

### Creation Order

```text
c1
c2
c3
```

---

### Destruction Order

```text
c3
c2
c1
```

---

## Important Interview Point

```text
Constructors:
First → Last

Destructors:
Last → First
```

---

# Dynamic Memory Example

## Without Destructor

```cpp
class Buffer
{
    int* ptr;

public:
    Buffer()
    {
        ptr = new int[100];
    }
};
```

Memory leak possible.

---

## With Destructor

```cpp
class Buffer
{
    int* ptr;

public:
    Buffer()
    {
        ptr = new int[100];
    }

    ~Buffer()
    {
        delete[] ptr;
    }
};
```

---

## What Happens?

```text
Object Created
↓
Memory Allocated
↓
Object Destroyed
↓
Memory Released
```

---

# Virtual Destructors

Very important in interviews.

---

## Problem Without Virtual Destructor

```cpp
class Base
{
public:
    ~Base()
    {
        cout << "Base Destructor";
    }
};

class Derived : public Base
{
public:
    ~Derived()
    {
        cout << "Derived Destructor";
    }
};

Base* ptr = new Derived();

delete ptr;
```

---

### Output

```text
Base Destructor
```

Derived destructor not called.

Resource leak possible.

---

# Solution: Virtual Destructor

```cpp
class Base
{
public:
    virtual ~Base()
    {
        cout << "Base Destructor";
    }
};
```

---

## Output

```text
Derived Destructor
Base Destructor
```

---

## Why Virtual Destructor?

```text
delete BasePointer
↓
Correct Derived Destructor Called
↓
Resources Released Properly
```

---

# Pure Virtual Destructor

Possible in abstract classes.

---

## Example

```cpp
class Base
{
public:
    virtual ~Base() = 0;
};

Base::~Base()
{
}
```

---

## Important

Even pure virtual destructors must have a definition.

---

# Destructors in Embedded Systems

Destructors are used for resource cleanup.

---

## 1. UART Driver

```cpp
class UART
{
public:
    ~UART()
    {
        // Disable UART
    }
};
```

---

## 2. GPIO Driver

```cpp
class GPIO
{
public:
    ~GPIO()
    {
        // Reset pin
    }
};
```

---

## 3. Sensor Drivers

```cpp
class Sensor
{
public:
    ~Sensor()
    {
        // Stop sensor
    }
};
```

---

## 4. Embedded Linux

Used for:

* File cleanup
* Thread cleanup
* Device cleanup

---

## 5. Automotive Software

Used in:

* ECU shutdown
* Communication cleanup
* Diagnostic module cleanup

---

# Advantages and Disadvantages

## Advantages

✔ Automatic cleanup

✔ Prevents memory leaks

✔ Better resource management

✔ Supports RAII design

✔ Improves reliability

---

## Disadvantages

✘ Destructor overhead

✘ Incorrect virtual destructor usage can cause bugs

✘ Cleanup timing may be difficult in large systems

---

# Interview Questions

## What is a Destructor?

A destructor is a special member function automatically called when an object is destroyed.

---

## Why is Destructor Used?

To release resources and perform cleanup operations.

---

## Can Destructor Have Parameters?

No.

---

## Can Destructor Be Overloaded?

No.

Only one destructor per class.

---

## What is Virtual Destructor?

A destructor declared using `virtual` to ensure proper cleanup through base class pointers.

---

## Why is Virtual Destructor Important?

Without it, derived class destructors may not execute when deleting through a base class pointer.

---

## What Happens When Scope Ends?

```text
Scope Ends
↓
Destructor Called Automatically
↓
Resources Released
```

---

## What is Destructor Call Order?

```text
Creation:
A → B → C

Destruction:
C → B → A
```

---

# Most Asked Interview Question

## Explain Destructor with a Real-Time Example.

A destructor is a special member function automatically called when an object is destroyed. It is used to release resources such as dynamically allocated memory, file handles, communication channels, and hardware resources. For example, in an embedded UART driver, the destructor may disable the UART peripheral and free allocated buffers when the object goes out of scope. This ensures proper resource management and prevents memory leaks.

---

# Quick Revision

```text
Destructor = Cleanup Function

Syntax:
~ClassName()

Rules:
✔ No return type
✔ No parameters
✔ Called automatically
✔ Cannot be overloaded

Important:
Use virtual destructor in base classes

Used in:
- Drivers
- UART
- GPIO
- Sensors
- Embedded Linux
```

---

# Conclusion

Destructors are an essential part of C++ object lifecycle management. They automatically release resources and perform cleanup when objects are destroyed. In embedded systems, destructors help manage memory, peripherals, communication interfaces, and operating system resources efficiently. Understanding destructors, especially virtual destructors, is critical for writing robust C++ applications and for succeeding in technical interviews.
