# unique_ptr in C++ (Smart Pointer & RAII)

## Table of Contents

1. [Introduction](#introduction)
2. [What is unique_ptr?](#what-is-unique_ptr)
3. [Why do we use unique_ptr?](#why-do-we-use-unique_ptr)
4. [Problems with Raw Pointers](#problems-with-raw-pointers)
5. [How unique_ptr Works](#how-unique_ptr-works)
6. [Syntax](#syntax)
7. [Creating unique_ptr](#creating-uniqueptr)
8. [Ownership Concept](#ownership-concept)
9. [Move Semantics with unique_ptr](#move-semantics-with-uniqueptr)
10. [Common Member Functions](#common-member-functions)
11. [Custom Deleters](#custom-deleters)
12. [unique_ptr with Arrays](#uniqueptr-with-arrays)
13. [How unique_ptr Works Internally](#how-uniqueptr-works-internally)
14. [unique_ptr in Embedded Systems](#uniqueptr-in-embedded-systems)
15. [Advantages and Disadvantages](#advantages-and-disadvantages)
16. [Interview Questions](#interview-questions)
17. [Conclusion](#conclusion)

---

# Introduction

Before C++11, developers manually managed memory using:

```cpp
new
delete
```

Example:

```cpp
int* ptr = new int(10);

/* use */

delete ptr;
```

Problems:

```text
Memory Leaks
Double Delete
Dangling Pointers
Exception Issues
```

To solve these problems, C++ introduced:

```text
Smart Pointers
```

One of them is:

```text
std::unique_ptr
```

---

# What is unique_ptr?

### Definition

> `std::unique_ptr` is a smart pointer that owns a dynamically allocated object exclusively and automatically deletes it when it goes out of scope.

---

## Simple Meaning

```text
One Object
One Owner
```

Only one pointer can own the resource at a time.

---

# Why do we use unique_ptr?

✔ Automatic Memory Management

✔ Prevent Memory Leaks

✔ Exception Safe

✔ RAII-Based

✔ Zero Ownership Confusion

✔ Better Performance

✔ No Manual delete

---

# Problems with Raw Pointers

Example:

```cpp
void func()
{
    int* ptr = new int(100);

    return;
}
```

Problem:

```text
delete missing
      ↓
Memory Leak
```

---

Another Problem

```cpp
int* ptr = new int(10);

delete ptr;

delete ptr;
```

---

Result:

```text
Double Free Error
```

---

# How unique_ptr Works

Internally:

```text
Object Created
      ↓
unique_ptr Owns Object
      ↓
Scope Ends
      ↓
Destructor Called
      ↓
delete Executed Automatically
```

---

# Syntax

```cpp
#include <memory>

std::unique_ptr<DataType> ptr;
```

---

## Example

```cpp
std::unique_ptr<int> ptr;
```

---

# Creating unique_ptr

## Method 1

Using Constructor

```cpp
std::unique_ptr<int> ptr(new int(10));
```

---

## Method 2 (Recommended)

Using make_unique

```cpp
auto ptr = std::make_unique<int>(10);
```

---

Why?

```text
Safer
Cleaner
Exception Safe
```

---

# Example Program

```cpp
#include <iostream>
#include <memory>

int main()
{
    auto ptr = std::make_unique<int>(100);

    std::cout << *ptr;
}
```

---

Output

```text
100
```

---

# What Happens When Code Hits This?

```cpp
auto ptr = std::make_unique<int>(100);
```

### Internal Flow

```text
1. Allocate Heap Memory
2. Store 100
3. Create unique_ptr
4. Ownership Assigned
5. Return Pointer
```

---

# Ownership Concept

Most Important Interview Topic

---

## Example

```cpp
auto ptr1 = std::make_unique<int>(10);
```

Ownership:

```text
ptr1
 ↓
Heap Object
```

---

Now:

```cpp
auto ptr2 = ptr1;
```

Compilation Error.

---

Why?

```text
Two Owners Not Allowed
```

---

Rule:

```text
unique_ptr = Unique Ownership
```

---

# Move Semantics with unique_ptr

Ownership can be transferred.

---

## Example

```cpp
auto ptr1 = std::make_unique<int>(10);

auto ptr2 = std::move(ptr1);
```

---

Result

```text
ptr1 → nullptr

ptr2 → Owns Resource
```

---

Memory View

Before Move:

```text
ptr1
 ↓
Object
```

---

After Move:

```text
ptr1 → nullptr

ptr2
 ↓
Object
```

---

# Common Member Functions

# get()

Returns raw pointer.

```cpp
ptr.get();
```

---

Example

```cpp
int* raw = ptr.get();
```

---

# release()

Releases ownership.

```cpp
ptr.release();
```

---

Example

```cpp
int* raw = ptr.release();
```

---

Result

```text
unique_ptr no longer owns memory
```

You must manually delete.

---

# reset()

Deletes current object and assigns new one.

```cpp
ptr.reset();
```

---

Example

```cpp
ptr.reset(new int(20));
```

---

# swap()

Swaps ownership.

```cpp
ptr1.swap(ptr2);
```

---

# Custom Deleters

Used when special cleanup is required.

---

Example

```cpp
auto deleter = [](FILE* fp)
{
    fclose(fp);
};

std::unique_ptr<FILE, decltype(deleter)>
ptr(fopen("test.txt","r"), deleter);
```

---

Benefit

```text
Automatic File Close
```

---

# unique_ptr with Arrays

Normal delete:

```cpp
delete ptr;
```

---

Array delete:

```cpp
delete[] ptr;
```

---

Use:

```cpp
std::unique_ptr<int[]> arr(
    new int[10]
);
```

---

Access:

```cpp
arr[0] = 10;
```

---

# How unique_ptr Works Internally

Simplified implementation:

```cpp
template<typename T>
class unique_ptr
{
private:

    T* ptr;

public:

    unique_ptr(T* p)
    {
        ptr = p;
    }

    ~unique_ptr()
    {
        delete ptr;
    }
};
```

---

Real implementation is much more advanced.

---

# What Happens When Code Hits This?

```cpp
{
    auto ptr =
    std::make_unique<int>(100);
}
```

---

Internal Flow

```text
Enter Scope
      ↓
Heap Memory Allocated
      ↓
unique_ptr Created
      ↓
Object Used
      ↓
Scope Ends
      ↓
unique_ptr Destructor Called
      ↓
delete Executed
      ↓
Memory Released
```

---

# unique_ptr in Embedded Systems

Used mainly in:

```text
Embedded Linux
Automotive Systems
Middleware
RTOS Applications
```

---

# Example 1: Sensor Driver

```cpp
class Sensor
{
};
```

---

Usage

```cpp
auto sensor =
std::make_unique<Sensor>();
```

---

Automatic cleanup.

---

# Example 2: UART Driver

```cpp
auto uart =
std::make_unique<UART>();
```

---

When scope ends:

```text
UART Released Automatically
```

---

# Example 3: Automotive

Used in:

* AUTOSAR Adaptive
* Diagnostics
* Communication Stacks
* Middleware

---

# Why Not Always Use unique_ptr in MCUs?

Small microcontrollers may avoid:

```text
Dynamic Memory Allocation
```

because of:

```text
Heap Fragmentation
```

---

Thus:

```text
STM32 Bare Metal
AVR
8051
```

often use static memory.

---

# Advantages and Disadvantages

## Advantages

✔ Automatic Cleanup

✔ Prevents Memory Leaks

✔ Fast

✔ Lightweight

✔ Exclusive Ownership

✔ Exception Safe

✔ RAII-Based

---

## Disadvantages

✘ Cannot Copy

✘ Only One Owner

✘ Uses Dynamic Memory

✘ Move Semantics Required

---

# unique_ptr vs Raw Pointer

| Feature                | Raw Pointer | unique_ptr |
| ---------------------- | ----------- | ---------- |
| Auto Delete            | No          | Yes        |
| Memory Leak Protection | No          | Yes        |
| Exception Safe         | No          | Yes        |
| Ownership Tracking     | No          | Yes        |
| RAII                   | No          | Yes        |

---

# unique_ptr vs shared_ptr

| Feature         | unique_ptr          | shared_ptr       |
| --------------- | ------------------- | ---------------- |
| Ownership       | Single              | Multiple         |
| Reference Count | No                  | Yes              |
| Performance     | Faster              | Slightly Slower  |
| Memory Usage    | Less                | More             |
| Use Case        | Exclusive Ownership | Shared Ownership |

---

# Interview Questions

## What is unique_ptr?

A smart pointer that provides exclusive ownership of a dynamically allocated object and automatically deletes it when it goes out of scope.

---

## Why Do We Use unique_ptr?

To prevent memory leaks and implement RAII-based automatic memory management.

---

## Can unique_ptr Be Copied?

No.

```cpp
auto p2 = p1;
```

Compilation Error.

---

## Why Can't unique_ptr Be Copied?

Because it enforces exclusive ownership.

Only one pointer may own a resource.

---

## How Can Ownership Be Transferred?

Using:

```cpp
std::move()
```

Example:

```cpp
auto p2 = std::move(p1);
```

---

## What Happens When Code Hits This?

```cpp
auto ptr =
std::make_unique<int>(100);
```

### Answer

```text
1. Heap memory allocated
2. Value initialized
3. unique_ptr created
4. Ownership assigned
```

---

## What Happens When Scope Ends?

```text
1. unique_ptr Destructor Called
2. delete Executed
3. Memory Released
```

---

## Difference Between unique_ptr and shared_ptr?

```text
unique_ptr
     ↓
Single Owner

shared_ptr
     ↓
Multiple Owners
```

---

## Is unique_ptr Faster Than shared_ptr?

Yes.

Because:

```text
No Reference Counting
```

---

# Most Asked Interview Question

## Explain unique_ptr with a Real-Time Example.

`std::unique_ptr` is a smart pointer that provides exclusive ownership of dynamically allocated memory. For example, in an embedded Linux application, a sensor driver object can be created using `std::make_unique<Sensor>()`. The object remains valid as long as the `unique_ptr` exists. When the pointer goes out of scope, its destructor automatically releases the memory. This prevents memory leaks and ensures exception-safe resource management using the RAII principle.

---

# Interview Answer (2-Minute Version)

`std::unique_ptr` is a C++ smart pointer that manages dynamically allocated memory through exclusive ownership. Only one `unique_ptr` can own a resource at a time, preventing ownership ambiguity. It automatically releases memory when the pointer goes out of scope, eliminating the need for manual `delete` operations. Ownership can be transferred using `std::move()`, but copying is not allowed. `unique_ptr` is lightweight, fast, RAII-based, and commonly used in modern C++, embedded Linux, automotive middleware, and resource management frameworks.

---

# Quick Revision

```text
unique_ptr
      ↓
Exclusive Ownership

Features:
✔ Auto Delete
✔ RAII
✔ Fast
✔ Exception Safe

Cannot Copy:
✘ ptr2 = ptr1

Can Move:
✔ ptr2 = std::move(ptr1)

Functions:
✔ get()
✔ release()
✔ reset()
✔ swap()

Internally:
Constructor
      ↓
Acquire Resource

Destructor
      ↓
delete Resource

Used In:
- Embedded Linux
- AUTOSAR Adaptive
- Middleware
- Driver Frameworks
```

---

# Conclusion

`std::unique_ptr` is the preferred smart pointer when a resource has a single owner. It provides automatic memory management, prevents memory leaks, and follows the RAII principle. Because it has minimal overhead and clear ownership semantics, it is widely used in modern C++, embedded Linux, automotive software, middleware frameworks, and high-reliability applications. Understanding `unique_ptr`, move semantics, and ownership transfer is essential for C++ development and technical interviews.
