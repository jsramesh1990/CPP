# Virtual Destructors in C++ (Polymorphism & Memory Management)

## Table of Contents

1. [Introduction](#introduction)
2. [What is a Virtual Destructor?](#what-is-a-virtual-destructor)
3. [Why do we use Virtual Destructors?](#why-do-we-use-virtual-destructors)
4. [Need for Virtual Destructors](#need-for-virtual-destructors)
5. [Problem Without Virtual Destructor](#problem-without-virtual-destructor)
6. [Solution Using Virtual Destructor](#solution-using-virtual-destructor)
7. [How Virtual Destructors Work Internally](#how-virtual-destructors-work-internally)
8. [Destructor Call Order](#destructor-call-order)
9. [Virtual Destructor vs Normal Destructor](#virtual-destructor-vs-normal-destructor)
10. [Virtual Destructors in Embedded Systems](#virtual-destructors-in-embedded-systems)
11. [Advantages and Disadvantages](#advantages-and-disadvantages)
12. [Interview Questions](#interview-questions)
13. [Conclusion](#conclusion)

---

# Introduction

In C++, polymorphism allows a base class pointer to point to a derived class object.

```cpp
Base* ptr = new Derived();
```

When deleting such objects, we must ensure that both:

* Derived class destructor
* Base class destructor

are executed properly.

This is achieved using a **Virtual Destructor**.

---

# What is a Virtual Destructor?

### Definition

> A virtual destructor is a destructor declared using the `virtual` keyword in the base class so that the correct destructor chain is called when deleting an object through a base class pointer.

---

## Syntax

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

## Simple Meaning

```text
Virtual Destructor
        ↓
Delete Through Base Pointer
        ↓
Derived Destructor Executes
        ↓
Base Destructor Executes
```

---

# Why do we use Virtual Destructors?

✔ Prevent memory leaks

✔ Proper cleanup of derived objects

✔ Support runtime polymorphism

✔ Safe deletion through base pointers

✔ Required in polymorphic classes

---

# Need for Virtual Destructors

Consider:

```cpp
Base* ptr = new Derived();
```

Later:

```cpp
delete ptr;
```

Question:

```text
Which destructor should execute?

Base?
Derived?
Both?
```

Correct Answer:

```text
Derived Destructor
↓
Base Destructor
```

Without a virtual destructor, this may not happen.

---

# Problem Without Virtual Destructor

## Example

```cpp
#include <iostream>
using namespace std;

class Base
{
public:
    ~Base()
    {
        cout << "Base Destructor\n";
    }
};

class Derived : public Base
{
public:
    ~Derived()
    {
        cout << "Derived Destructor\n";
    }
};

int main()
{
    Base* ptr = new Derived();

    delete ptr;
}
```

---

## Output

```text
Base Destructor
```

---

## Problem

```text
Derived Destructor Not Called
```

This can cause:

* Memory leaks
* Resource leaks
* File leaks
* Peripheral leaks

---

## What Happens Internally?

```text
delete ptr
      ↓
ptr type = Base*
      ↓
Compiler calls Base Destructor
      ↓
Derived Destructor skipped
```

---

# Solution Using Virtual Destructor

## Example

```cpp
#include <iostream>
using namespace std;

class Base
{
public:
    virtual ~Base()
    {
        cout << "Base Destructor\n";
    }
};

class Derived : public Base
{
public:
    ~Derived()
    {
        cout << "Derived Destructor\n";
    }
};

int main()
{
    Base* ptr = new Derived();

    delete ptr;
}
```

---

## Output

```text
Derived Destructor
Base Destructor
```

---

## What Happens Internally?

```text
delete ptr
      ↓
vPtr accessed
      ↓
Derived Destructor found
      ↓
Derived Destructor executes
      ↓
Base Destructor executes
```

---

# How Virtual Destructors Work Internally

Virtual destructors use:

## 1. vTable

Stores addresses of virtual functions.

---

## 2. vPtr

Hidden pointer inside object.

---

## Visualization

```text
Derived Object

+-------------------+
| vPtr ------------+|
| Derived Data     ||
+------------------||
                   ||
                   \/
              vTable

+----------------------+
| Derived Destructor   |
| Other Virtual Funcs  |
+----------------------+
```

---

## What Happens When Code Hits This?

```cpp
delete ptr;
```

### Internal Steps

```text
1. ptr points to Derived object
2. vPtr accessed
3. vTable checked
4. Derived Destructor located
5. Derived Destructor called
6. Base Destructor called
7. Memory released
```

---

# Destructor Call Order

## Creation Order

```cpp
Derived d;
```

---

### Internally

```text
Base Constructor
↓
Derived Constructor
```

---

## Destruction Order

```text
Derived Destructor
↓
Base Destructor
```

---

## Important Interview Point

```text
Construction:
Base → Derived

Destruction:
Derived → Base
```

---

# Virtual Destructor vs Normal Destructor

| Feature                    | Normal Destructor | Virtual Destructor |
| -------------------------- | ----------------- | ------------------ |
| Runtime Polymorphism       | No                | Yes                |
| Safe Base Pointer Deletion | No                | Yes                |
| Derived Destructor Called  | May Not           | Always             |
| Memory Leak Prevention     | Limited           | Better             |
| Uses vTable                | No                | Yes                |

---

# Virtual Destructors in Embedded Systems

Virtual destructors are important when using C++ polymorphism.

---

## 1. Hardware Abstraction Layer (HAL)

```cpp
class UART
{
public:
    virtual ~UART()
    {
    }
};
```

---

## STM32 Driver

```cpp
class STM32_UART : public UART
{
public:
    ~STM32_UART()
    {
        // Release DMA
    }
};
```

---

## ESP32 Driver

```cpp
class ESP32_UART : public UART
{
public:
    ~ESP32_UART()
    {
        // Release Buffers
    }
};
```

---

## Why?

```cpp
UART* uart = new STM32_UART();

delete uart;
```

Need proper cleanup.

---

# 2. Sensor Frameworks

```cpp
Sensor* sensor = new TemperatureSensor();

delete sensor;
```

Ensures sensor resources are released.

---

# 3. Automotive Software

Used in:

* AUTOSAR Components
* Diagnostics
* Communication Modules
* Sensor Abstraction Layers

---

# 4. Embedded Linux

Used in:

* Device Drivers
* Middleware
* Framework Objects

---

# Advantages and Disadvantages

## Advantages

✔ Proper object cleanup

✔ Prevents resource leaks

✔ Supports polymorphism

✔ Safe deletion through base pointers

✔ Essential for framework design

---

## Disadvantages

✘ Slight memory overhead (vPtr)

✘ Slight runtime overhead

✘ Not needed if no polymorphism exists

---

# Interview Questions

## What is a Virtual Destructor?

A virtual destructor is a destructor declared with the `virtual` keyword to ensure proper cleanup of derived objects when deleted through a base class pointer.

---

## Why Do We Need Virtual Destructors?

To ensure derived class destructors execute correctly during polymorphic deletion.

---

## What Happens Without Virtual Destructor?

Only the base class destructor may execute, causing resource leaks.

---

## Does a Virtual Destructor Use vTable?

Yes.

Like all virtual functions, it uses vTable and vPtr.

---

## When Should a Destructor Be Virtual?

Whenever a class contains at least one virtual function or is intended to be used polymorphically.

---

## What Happens When Code Hits This?

```cpp
delete ptr;
```

### Internal Flow

```text
1. vPtr accessed
2. vTable checked
3. Derived Destructor called
4. Base Destructor called
5. Memory released
```

---

## Can Constructors Be Virtual?

No.

Constructors cannot be virtual because the object is not fully created when the constructor starts.

---

## Can Destructors Be Virtual?

Yes.

This is a common and recommended practice.

---

# Most Asked Interview Question

## Why Should Base Class Destructors Be Virtual?

When a derived class object is deleted through a base class pointer, the compiler must know the actual object type at runtime. A virtual destructor enables runtime dispatch through the vTable, ensuring the derived destructor executes first, followed by the base destructor. Without a virtual destructor, only the base destructor may execute, causing memory leaks and incomplete resource cleanup.

---

# Interview Answer (2-Minute Version)

**Q: Explain Virtual Destructor in C++.**

A virtual destructor is a destructor declared with the `virtual` keyword in the base class. It ensures that when a derived class object is deleted through a base class pointer, the correct destructor chain is executed. First, the derived class destructor runs, then the base class destructor. This prevents memory and resource leaks and is essential whenever polymorphism is used. Internally, virtual destructors use the vTable and vPtr mechanism to determine the correct destructor at runtime.

---

# Quick Revision

```text
Virtual Destructor

Syntax:
virtual ~Base() {}

Purpose:
✔ Proper Cleanup
✔ Runtime Polymorphism
✔ Safe Base Pointer Deletion

Without Virtual:
delete Base*
      ↓
Only Base Destructor

With Virtual:
delete Base*
      ↓
Derived Destructor
      ↓
Base Destructor

Important Rule:
If a class has any virtual function,
make the destructor virtual.
```

---

# Conclusion

Virtual destructors are a critical part of C++ polymorphism and resource management. They ensure that derived objects are cleaned up correctly when accessed through base class pointers. In embedded systems, automotive software, HAL layers, and framework development, virtual destructors prevent resource leaks and guarantee reliable object destruction. Understanding them is essential for advanced C++ programming and technical interviews.
