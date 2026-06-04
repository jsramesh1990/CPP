# shared_ptr in C++ (Smart Pointer & Shared Ownership)

## Table of Contents

1. [Introduction](#introduction)
2. [What is shared_ptr?](#what-is-shared_ptr)
3. [Why do we use shared_ptr?](#why-do-we-use-shared_ptr)
4. [Problems with Raw Pointers](#problems-with-raw-pointers)
5. [Need for Shared Ownership](#need-for-shared-ownership)
6. [How shared_ptr Works](#how-shared_ptr-works)
7. [Reference Counting](#reference-counting)
8. [Creating shared_ptr](#creating-shared_ptr)
9. [Copying shared_ptr](#copying-shared_ptr)
10. [Common Member Functions](#common-member-functions)
11. [Control Block](#control-block)
12. [Weak Pointer Relationship](#weak-pointer-relationship)
13. [Circular Reference Problem](#circular-reference-problem)
14. [How shared_ptr Works Internally](#how-shared_ptr-works-internally)
15. [shared_ptr in Embedded Systems](#shared_ptr-in-embedded-systems)
16. [Advantages and Disadvantages](#advantages-and-disadvantages)
17. [Interview Questions](#interview-questions)
18. [Conclusion](#conclusion)

---

# Introduction

C++ provides smart pointers for automatic memory management.

Main smart pointers:

```text
unique_ptr
shared_ptr
weak_ptr
```

---

Ownership Model:

```text
unique_ptr
     ↓
Single Owner

shared_ptr
     ↓
Multiple Owners
```

---

# What is shared_ptr?

### Definition

> `std::shared_ptr` is a smart pointer that allows multiple pointers to share ownership of the same dynamically allocated object.

The object is automatically destroyed when the last owner releases it.

---

## Simple Meaning

```text
Object
  ↑
  │
Many shared_ptr
```

All pointers share ownership.

---

# Why do we use shared_ptr?

✔ Shared Ownership

✔ Automatic Memory Management

✔ Prevent Memory Leaks

✔ Exception Safe

✔ RAII-Based

✔ No Manual delete

✔ Easy Resource Sharing

---

# Problems with Raw Pointers

Example:

```cpp
Sensor* sensor = new Sensor();
```

---

Pass to multiple modules:

```cpp
ModuleA(sensor);
ModuleB(sensor);
ModuleC(sensor);
```

---

Questions:

```text
Who owns sensor?
Who deletes sensor?
When should it be deleted?
```

---

Potential Issues:

```text
Memory Leak
Double Delete
Dangling Pointer
```

---

# Need for Shared Ownership

Suppose:

```text
Camera Module
      │
      ▼
Image Processor
      │
      ▼
Storage Manager
```

All modules need access to the same object.

Using raw pointers is dangerous.

Using shared_ptr:

```text
Multiple Owners
Automatic Cleanup
```

---

# How shared_ptr Works

Internally:

```text
Object
     +
Reference Counter
```

---

Memory Layout

```text
shared_ptr A
       │
shared_ptr B
       │
shared_ptr C
       │
       ▼

+----------------+
| Actual Object  |
+----------------+
| Ref Count = 3  |
+----------------+
```

---

When one pointer is destroyed:

```text
Ref Count = 2
```

Object remains alive.

---

When last pointer is destroyed:

```text
Ref Count = 0
      ↓
delete Object
```

---

# Reference Counting

Most Important Interview Topic

---

Example:

```cpp
auto p1 =
std::make_shared<int>(100);
```

Reference Count:

```text
1
```

---

Copy:

```cpp
auto p2 = p1;
```

Reference Count:

```text
2
```

---

Copy Again:

```cpp
auto p3 = p2;
```

Reference Count:

```text
3
```

---

Destroy p3:

```text
Count = 2
```

Destroy p2:

```text
Count = 1
```

Destroy p1:

```text
Count = 0
     ↓
Memory Deleted
```

---

# Creating shared_ptr

## Method 1

```cpp
std::shared_ptr<int> ptr(
    new int(10)
);
```

---

## Method 2 (Recommended)

```cpp
auto ptr =
std::make_shared<int>(10);
```

---

Why?

```text
Faster
Safer
Single Allocation
Exception Safe
```

---

# Example Program

```cpp
#include <iostream>
#include <memory>

int main()
{
    auto ptr =
    std::make_shared<int>(100);

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
auto ptr =
std::make_shared<int>(100);
```

### Internal Flow

```text
1. Allocate Memory
2. Create Object
3. Create Control Block
4. Ref Count = 1
5. Return shared_ptr
```

---

# Copying shared_ptr

Unlike unique_ptr:

```cpp
auto p2 = p1;
```

is allowed.

---

Example

```cpp
auto p1 =
std::make_shared<int>(10);

auto p2 = p1;
```

---

Memory View

```text
p1 ─┐
    │
p2 ─┘

Object
Count = 2
```

---

# Common Member Functions

# use_count()

Returns reference count.

```cpp
ptr.use_count();
```

---

Example

```cpp
std::cout
<< ptr.use_count();
```

---

# get()

Returns raw pointer.

```cpp
ptr.get();
```

---

# reset()

Releases ownership.

```cpp
ptr.reset();
```

---

Example

```cpp
ptr.reset();
```

Reference count decreases.

---

# swap()

Swaps ownership.

```cpp
ptr1.swap(ptr2);
```

---

# unique()

Checks if only one owner exists.

```cpp
ptr.unique();
```

---

Returns:

```text
true
```

if count is 1.

---

# Control Block

Most Asked Interview Topic

---

Every shared_ptr creates:

```text
Control Block
```

Contains:

```text
Reference Count
Weak Count
Custom Deleter
Allocator Info
```

---

Memory Structure

```text
+----------------+
| shared_ptr     |
+----------------+
        │
        ▼

+----------------+
| Control Block  |
| Ref Count      |
| Weak Count     |
+----------------+
        │
        ▼

+----------------+
| Actual Object  |
+----------------+
```

---

# Weak Pointer Relationship

Shared pointers can cause circular references.

Solution:

```cpp
std::weak_ptr
```

---

Weak pointer:

```text
Does Not Own Object
```

---

Used only for observation.

---

# Circular Reference Problem

Very Important Interview Question

---

Example:

```cpp
class A
{
public:
    std::shared_ptr<B> ptr;
};

class B
{
public:
    std::shared_ptr<A> ptr;
};
```

---

Memory:

```text
A → B
↑   ↓
└───┘
```

---

Reference Count Never Becomes Zero.

Result:

```text
Memory Leak
```

---

Solution:

```cpp
std::weak_ptr
```

---

Example

```cpp
class B
{
public:
    std::weak_ptr<A> ptr;
};
```

---

# How shared_ptr Works Internally

Simplified Version

```cpp
template<typename T>
class shared_ptr
{
private:

    T* ptr;

    int* refCount;

public:

    shared_ptr(T* p)
    {
        ptr = p;

        refCount = new int(1);
    }

    ~shared_ptr()
    {
        (*refCount)--;

        if(*refCount == 0)
        {
            delete ptr;
            delete refCount;
        }
    }
};
```

---

Actual implementation is much more complex.

---

# What Happens When Code Hits This?

```cpp
{
    auto p1 =
    std::make_shared<int>(100);

    auto p2 = p1;
}
```

---

Internal Flow

```text
p1 Created
      ↓
Count = 1

p2 Created
      ↓
Count = 2

p2 Destroyed
      ↓
Count = 1

p1 Destroyed
      ↓
Count = 0

Delete Object
Delete Control Block
```

---

# shared_ptr in Embedded Systems

Used mostly in:

```text
Embedded Linux
AUTOSAR Adaptive
Middleware
ROS2
High-Level Applications
```

---

# Example 1: Sensor Sharing

```cpp
auto sensor =
std::make_shared<Sensor>();
```

Shared among:

```text
Logger
Controller
Display
```

---

# Example 2: Camera Framework

```text
Camera
  │
  ├── Image Processor
  ├── Display
  └── Storage
```

Shared ownership required.

---

# Example 3: Automotive

Used in:

* Adaptive AUTOSAR
* Diagnostics
* Middleware
* Infotainment

---

# Why Not Always Use shared_ptr?

Reference counting requires:

```text
Extra Memory
Extra CPU Cycles
```

---

Small MCUs often avoid it.

---

# Advantages and Disadvantages

## Advantages

✔ Automatic Cleanup

✔ Shared Ownership

✔ Exception Safe

✔ RAII-Based

✔ Easy Resource Sharing

✔ Prevents Double Delete

---

## Disadvantages

✘ Reference Count Overhead

✘ Extra Memory Usage

✘ Slower than unique_ptr

✘ Circular Reference Risk

✘ More Complex

---

# unique_ptr vs shared_ptr

| Feature         | unique_ptr | shared_ptr |
| --------------- | ---------- | ---------- |
| Ownership       | Single     | Multiple   |
| Copy Allowed    | No         | Yes        |
| Move Allowed    | Yes        | Yes        |
| Reference Count | No         | Yes        |
| Speed           | Faster     | Slower     |
| Memory Usage    | Lower      | Higher     |

---

# shared_ptr vs weak_ptr

| Feature                 | shared_ptr | weak_ptr |
| ----------------------- | ---------- | -------- |
| Owns Object             | Yes        | No       |
| Ref Count Increase      | Yes        | No       |
| Keeps Object Alive      | Yes        | No       |
| Circular Reference Safe | No         | Yes      |

---

# Interview Questions

## What is shared_ptr?

A smart pointer that allows multiple owners for the same dynamically allocated object using reference counting.

---

## Why Use shared_ptr?

When multiple objects need access to the same resource and ownership must be shared.

---

## How Does shared_ptr Work?

Using:

```text
Reference Counting
```

The object is destroyed when the count becomes zero.

---

## What Happens When Code Hits This?

```cpp
auto p2 = p1;
```

### Answer

```text
1. Copy shared_ptr
2. Ref Count Incremented
3. Both Pointers Share Ownership
```

---

## What is a Control Block?

A memory structure that stores:

```text
Reference Count
Weak Count
Deleter
Allocator
```

for a shared_ptr.

---

## Why is make_shared Preferred?

Because:

```text
Single Allocation
Better Performance
Exception Safe
```

---

## What is the Circular Reference Problem?

When objects hold shared_ptr references to each other, the reference count never reaches zero, causing a memory leak.

---

## How to Solve Circular References?

Using:

```cpp
std::weak_ptr
```

---

## Is shared_ptr Thread Safe?

Reference count operations are thread-safe.

However:

```text
Object Access
```

must still be synchronized separately.

---

# Most Asked Interview Question

## Explain shared_ptr with a Real-Time Example.

`std::shared_ptr` is a smart pointer that enables multiple objects to share ownership of the same resource. For example, in an automotive infotainment system, a camera object may be used by the display manager, image processor, and storage manager simultaneously. Each module holds a `shared_ptr` to the camera object. The camera remains alive as long as at least one module is using it. Once the last `shared_ptr` is destroyed, the camera object is automatically deleted.

---

# Interview Answer (2-Minute Version)

`std::shared_ptr` is a smart pointer that manages shared ownership of dynamically allocated objects using reference counting. Every time a `shared_ptr` is copied, the reference count increases. When a `shared_ptr` is destroyed, the count decreases. Once the count reaches zero, the managed object and its control block are automatically deleted. `shared_ptr` is useful when multiple modules need access to the same resource, such as sensor data, camera streams, or middleware services. It provides automatic memory management and exception safety but introduces some memory and performance overhead due to reference counting.

---

# Quick Revision

```text
shared_ptr
      ↓
Shared Ownership

Features:
✔ Auto Delete
✔ Reference Counting
✔ RAII
✔ Exception Safe

Internally:
Object
  +
Control Block

Control Block:
✔ Ref Count
✔ Weak Count
✔ Deleter

Functions:
✔ use_count()
✔ get()
✔ reset()
✔ swap()

Problems:
✘ Circular References

Solution:
✔ weak_ptr

Used In:
- Embedded Linux
- ROS2
- AUTOSAR Adaptive
- Middleware
- Camera Frameworks
```

---

# Conclusion

`std::shared_ptr` is a powerful smart pointer that enables safe and automatic shared ownership of dynamically allocated resources. By using reference counting and RAII, it eliminates many memory-management issues found with raw pointers. It is widely used in modern C++, middleware, automotive software, robotics, and embedded Linux applications. Understanding control blocks, reference counting, circular references, and `weak_ptr` is essential for C++ interviews and real-world software development.
