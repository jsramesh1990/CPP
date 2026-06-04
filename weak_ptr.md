# weak_ptr in C++ (Smart Pointer Observer)

## Table of Contents

1. [Introduction](#introduction)
2. [What is weak_ptr?](#what-is-weak_ptr)
3. [Why do we use weak_ptr?](#why-do-we-use-weak_ptr)
4. [Need for weak_ptr](#need-for-weak_ptr)
5. [Relationship Between shared_ptr and weak_ptr](#relationship-between-shared_ptr-and-weak_ptr)
6. [How weak_ptr Works](#how-weak_ptr-works)
7. [Creating weak_ptr](#creating-weak_ptr)
8. [lock() Function](#lock-function)
9. [expired() Function](#expired-function)
10. [use_count() Function](#use_count-function)
11. [Circular Reference Problem](#circular-reference-problem)
12. [How weak_ptr Solves Circular References](#how-weak_ptr-solves-circular-references)
13. [Control Block Internals](#control-block-internals)
14. [How weak_ptr Works Internally](#how-weak_ptr-works-internally)
15. [weak_ptr in Embedded Systems](#weak_ptr-in-embedded-systems)
16. [Advantages and Disadvantages](#advantages-and-disadvantages)
17. [Interview Questions](#interview-questions)
18. [Conclusion](#conclusion)

---

# Introduction

C++ provides three major smart pointers:

```text
1. unique_ptr
2. shared_ptr
3. weak_ptr
```

Ownership Model:

```text
unique_ptr
    ↓
Single Owner

shared_ptr
    ↓
Multiple Owners

weak_ptr
    ↓
No Ownership
Observer Only
```

---

# What is weak_ptr?

### Definition

> `std::weak_ptr` is a smart pointer that observes an object managed by `std::shared_ptr` without increasing the reference count.

---

## Simple Meaning

```text
shared_ptr
     ↓
 Owns Object

weak_ptr
     ↓
 Watches Object
```

---

## Key Point

```text
weak_ptr
      ≠
Ownership
```

It only observes.

---

# Why do we use weak_ptr?

✔ Prevent Circular References

✔ Observe Shared Objects

✔ No Ownership Overhead

✔ Avoid Memory Leaks

✔ Safe Resource Monitoring

✔ Works with shared_ptr

---

# Need for weak_ptr

Suppose:

```cpp
auto p1 =
std::make_shared<int>(100);
```

Multiple modules need access.

Use:

```cpp
shared_ptr
```

---

Problem:

```text
Too many shared_ptr
      ↓
Reference Count Increases
      ↓
Object Lives Longer
```

---

Sometimes we only need:

```text
Observe
Not Own
```

---

Use:

```cpp
weak_ptr
```

---

# Relationship Between shared_ptr and weak_ptr

Most Important Interview Topic

---

```text
shared_ptr
      ↓
 Owns Object

weak_ptr
      ↓
 Observes Object
```

---

Memory Structure

```text
shared_ptr A
       │
shared_ptr B
       │
       ▼

+----------------+
| Actual Object  |
+----------------+

       ▲
       │

weak_ptr W
```

---

Reference Count:

```text
shared_ptr → Increases Count

weak_ptr → Does NOT Increase Count
```

---

# How weak_ptr Works

A weak pointer points to:

```text
Control Block
```

but does not own:

```text
Actual Object
```

---

Memory Layout

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

        ▲
        │

+----------------+
| weak_ptr       |
+----------------+
```

---

# Creating weak_ptr

Example

```cpp
auto sp =
std::make_shared<int>(100);

std::weak_ptr<int> wp = sp;
```

---

Reference Count

```text
sp = 1

wp = 0 owners
```

---

Ownership

```text
sp owns object

wp only observes
```

---

# lock() Function

Most Asked Interview Question

---

Converts weak_ptr to shared_ptr.

---

Example

```cpp
auto sp = wp.lock();
```

---

If object exists:

```text
shared_ptr returned
```

---

If object destroyed:

```text
nullptr returned
```

---

Complete Example

```cpp
auto sp =
std::make_shared<int>(100);

std::weak_ptr<int> wp = sp;

if(auto temp = wp.lock())
{
    std::cout << *temp;
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
auto temp = wp.lock();
```

### Internal Flow

```text
1. Check Object Alive?
2. If Yes
       Create shared_ptr
       Increase Ref Count
3. Return shared_ptr
```

---

# expired() Function

Checks whether object still exists.

---

Example

```cpp
wp.expired();
```

---

Returns:

```text
true
```

if object destroyed.

---

Example

```cpp
if(wp.expired())
{
    std::cout << "Object Deleted";
}
```

---

# use_count() Function

Returns current shared ownership count.

---

Example

```cpp
wp.use_count();
```

---

```cpp
auto sp =
std::make_shared<int>(10);

std::weak_ptr<int> wp = sp;
```

---

Output

```text
1
```

---

Because:

```text
Only shared_ptr counts
```

---

# Circular Reference Problem

Most Important Interview Question

---

Without weak_ptr:

```cpp
class B;

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

Memory

```text
A → B
↑   ↓
└───┘
```

---

Reference Counts

```text
A = 1
B = 1
```

---

After scope ends:

```text
A = 1
B = 1
```

Never reaches zero.

---

Result:

```text
Memory Leak
```

---

# How weak_ptr Solves Circular References

Replace one side.

---

Example

```cpp
class B;

class A
{
public:
    std::shared_ptr<B> ptr;
};

class B
{
public:
    std::weak_ptr<A> ptr;
};
```

---

Memory

```text
A ──shared_ptr──► B
▲
│
weak_ptr
│
└───────────────
```

---

Reference Count

```text
A = 1
B = 1
```

---

When scope ends:

```text
A = 0
B = 0
```

---

Result:

```text
Memory Released
```

---

# Control Block Internals

Both shared_ptr and weak_ptr use:

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
| Control Block  |
+----------------+
| Ref Count      |
| Weak Count     |
+----------------+
```

---

Example

```cpp
auto sp =
std::make_shared<int>(10);

std::weak_ptr<int> wp = sp;
```

---

Values

```text
Ref Count = 1

Weak Count = 1
```

---

# How weak_ptr Works Internally

Simplified Version

```cpp
template<typename T>
class weak_ptr
{
private:

    T* ptr;

    int* weakCount;

public:

    weak_ptr()
    {
    }
};
```

---

Real implementation stores:

```text
Control Block Pointer
```

instead of direct ownership.

---

# What Happens When Code Hits This?

```cpp
{
    auto sp =
    std::make_shared<int>(100);

    std::weak_ptr<int> wp = sp;
}
```

---

Internal Flow

```text
sp Created
      ↓
Ref Count = 1

wp Created
      ↓
Weak Count = 1

sp Destroyed
      ↓
Ref Count = 0

Object Deleted

Control Block Remains

wp Expires
```

---

# weak_ptr in Embedded Systems

Common in:

```text
Embedded Linux
AUTOSAR Adaptive
ROS2
Middleware
Large Applications
```

---

# Example 1: Sensor Monitoring

```cpp
std::shared_ptr<Sensor> sensor;

std::weak_ptr<Sensor> observer;
```

---

Logger can observe:

```text
Sensor State
```

without owning sensor.

---

# Example 2: Camera Framework

```text
Camera
   │
Image Processor
   │
Display
```

---

Observers use:

```text
weak_ptr
```

to avoid ownership cycles.

---

# Example 3: Automotive Middleware

Used in:

* Adaptive AUTOSAR
* Diagnostics
* Service Discovery
* Communication Frameworks

---

# Advantages and Disadvantages

## Advantages

✔ Prevents Circular References

✔ No Ownership Overhead

✔ Safe Observation

✔ Works with shared_ptr

✔ Prevents Memory Leaks

✔ Lightweight

---

## Disadvantages

✘ Cannot Access Object Directly

✘ Requires lock()

✘ Slightly More Complex

✘ Only Works with shared_ptr

---

# shared_ptr vs weak_ptr

| Feature               | shared_ptr | weak_ptr |
| --------------------- | ---------- | -------- |
| Owns Object           | Yes        | No       |
| Increases Ref Count   | Yes        | No       |
| Keeps Object Alive    | Yes        | No       |
| Direct Access         | Yes        | No       |
| Prevents Circular Ref | No         | Yes      |

---

# unique_ptr vs shared_ptr vs weak_ptr

| Feature      | unique_ptr      | shared_ptr   | weak_ptr |
| ------------ | --------------- | ------------ | -------- |
| Ownership    | Single          | Shared       | None     |
| Ref Count    | No              | Yes          | No       |
| Copy Allowed | No              | Yes          | Yes      |
| Auto Delete  | Yes             | Yes          | No       |
| Use Case     | Exclusive Owner | Shared Owner | Observer |

---

# Interview Questions

## What is weak_ptr?

A smart pointer that observes an object managed by `shared_ptr` without owning it.

---

## Why Use weak_ptr?

To observe shared objects and prevent circular references.

---

## Does weak_ptr Increase Reference Count?

No.

Only `shared_ptr` increases the reference count.

---

## What Happens When Code Hits This?

```cpp
auto temp = wp.lock();
```

### Answer

```text
1. Check if object exists
2. If alive:
      Create shared_ptr
      Increase Ref Count
3. Return shared_ptr
```

---

## Why Can't weak_ptr Access Object Directly?

Because it does not own the object.

Must first obtain:

```cpp
wp.lock()
```

---

## What Does expired() Do?

Checks whether the managed object has already been destroyed.

---

## How Does weak_ptr Prevent Memory Leaks?

By breaking circular references between shared_ptr objects.

---

## What is the Circular Reference Problem?

When two objects own each other using shared_ptr, reference counts never become zero, causing memory leaks.

---

## How Does weak_ptr Solve Circular References?

One side of the relationship is changed from shared_ptr to weak_ptr so ownership is not cyclic.

---

# Most Asked Interview Question

## Explain weak_ptr with a Real-Time Example.

`std::weak_ptr` is a smart pointer that observes an object managed by a `std::shared_ptr` without increasing its reference count. For example, in an automotive camera framework, the image processor may own a camera object through a `shared_ptr`, while diagnostic and monitoring modules only observe the camera status through `weak_ptr`. This avoids unnecessary ownership and prevents circular references while still allowing safe access through `lock()`.

---

# Interview Answer (2-Minute Version)

`std::weak_ptr` is a non-owning smart pointer used with `std::shared_ptr`. Unlike `shared_ptr`, it does not increase the reference count and therefore does not keep the object alive. Its primary purpose is to observe shared resources safely and prevent circular references that can cause memory leaks. To access the managed object, a `weak_ptr` must first be converted to a `shared_ptr` using the `lock()` function. `weak_ptr` is commonly used in middleware, automotive software, ROS2, and large C++ applications where object relationships can become complex.

---

# Quick Revision

```text
weak_ptr
      ↓
Observer Only

Features:
✔ No Ownership
✔ No Ref Count Increase
✔ Prevent Circular References
✔ Safe Observation

Functions:
✔ lock()
✔ expired()
✔ use_count()

Internally:
Control Block Access
No Object Ownership

Used With:
✔ shared_ptr

Cannot:
✘ Access Directly
✘ Keep Object Alive

Used In:
- Embedded Linux
- ROS2
- AUTOSAR Adaptive
- Middleware
```

---

# Conclusion

`std::weak_ptr` is a lightweight, non-owning smart pointer designed to work alongside `std::shared_ptr`. Its primary role is to observe shared resources without affecting their lifetime and to eliminate circular-reference memory leaks. Understanding `weak_ptr`, control blocks, `lock()`, and circular references is essential for modern C++ development and is a common topic in technical interviews for software, embedded Linux, robotics, and automotive engineering roles.
