# Rule of 5

## Table of Contents

1. [Introduction](#introduction)
2. [Why Rule of 5 Was Introduced](#why-rule-of-5-was-introduced)
3. [Relationship Between Rule of 3 and Rule of 5](#relationship-between-rule-of-3-and-rule-of-5)
4. [The Five Special Member Functions](#the-five-special-member-functions)
5. [Destructor](#destructor)
6. [Copy Constructor](#copy-constructor)
7. [Copy Assignment Operator](#copy-assignment-operator)
8. [Move Constructor](#move-constructor)
9. [Move Assignment Operator](#move-assignment-operator)
10. [Complete Rule of 5 Example](#complete-rule-of-5-example)
11. [What Happens Internally](#what-happens-internally)
12. [Copy vs Move Operations](#copy-vs-move-operations)
13. [Resource Ownership Transfer](#resource-ownership-transfer)
14. [Rule of 5 in STL](#rule-of-5-in-stl)
15. [Rule of 5 in Embedded Systems](#rule-of-5-in-embedded-systems)
16. [Advantages and Disadvantages](#advantages-and-disadvantages)
17. [Interview Questions](#interview-questions)
18. [Real-Time Examples](#real-time-examples)
19. [Rule of 0](#rule-of-0)
20. [Quick Revision](#quick-revision)
21. [Conclusion](#conclusion)

---

# Introduction

The **Rule of 5** is a modern C++ guideline introduced with **C++11 Move Semantics**.

It states:

> If a class defines one of the special member functions related to resource management, it will often need to define all five.

---

## Why?

Classes managing resources such as:

```text
Heap Memory
File Handles
Sockets
DMA Buffers
Mutexes
Hardware Resources
```

need proper:

* Copying
* Moving
* Cleanup

---

# Why Rule of 5 Was Introduced

Before C++11:

```text
Rule of 3
```

was enough because only copying existed.

---

After C++11:

```text
Move Constructor
Move Assignment Operator
```

were added.

Now resource-managing classes must handle:

```text
Copying
Moving
Destroying
```

correctly.

---

# Relationship Between Rule of 3 and Rule of 5

## Rule of 3 (C++03)

```cpp
Destructor
Copy Constructor
Copy Assignment Operator
```

---

## Rule of 5 (C++11)

```cpp
Destructor
Copy Constructor
Copy Assignment Operator
Move Constructor
Move Assignment Operator
```

---

# The Five Special Member Functions

| Function         | Purpose                              |
| ---------------- | ------------------------------------ |
| Destructor       | Release Resources                    |
| Copy Constructor | Deep Copy                            |
| Copy Assignment  | Deep Copy Assignment                 |
| Move Constructor | Transfer Ownership During Creation   |
| Move Assignment  | Transfer Ownership During Assignment |

---

# Destructor

Responsible for resource cleanup.

---

## Syntax

```cpp
~Buffer()
{
    delete[] data;
}
```

---

## What Happens When Code Hits This?

```cpp
Buffer obj;
```

Leaving scope:

```cpp
}
```

Execution:

```text
Destructor Called
↓
Memory Released
↓
Object Destroyed
```

---

# Copy Constructor

Creates a new object from an existing object.

---

## Syntax

```cpp
Buffer(const Buffer& other);
```

---

Example

```cpp
Buffer(const Buffer& other)
{
    size = other.size;

    data = new int[size];

    std::copy(
        other.data,
        other.data + size,
        data
    );
}
```

---

## What Happens When Code Hits This?

```cpp
Buffer b2 = b1;
```

Execution:

```text
Copy Constructor Called
↓
Allocate New Memory
↓
Copy Data
```

---

# Copy Assignment Operator

Used when assigning existing objects.

---

## Syntax

```cpp
Buffer&
operator=(const Buffer& other);
```

---

Example

```cpp
Buffer&
operator=(const Buffer& other)
{
    if(this != &other)
    {
        delete[] data;

        size = other.size;

        data = new int[size];

        std::copy(
            other.data,
            other.data + size,
            data
        );
    }

    return *this;
}
```

---

## What Happens When Code Hits This?

```cpp
b2 = b1;
```

Execution:

```text
Old Memory Released
↓
New Memory Allocated
↓
Data Copied
```

---

# Move Constructor

Most Important Rule of 5 Addition.

Transfers ownership from temporary objects.

---

## Syntax

```cpp
Buffer(Buffer&& other);
```

---

Example

```cpp
Buffer(Buffer&& other)
{
    data = other.data;
    size = other.size;

    other.data = nullptr;
    other.size = 0;
}
```

---

## What Happens When Code Hits This?

```cpp
Buffer b2(std::move(b1));
```

Execution:

```text
Move Constructor Called
↓
Pointer Ownership Transferred
↓
b1.data = nullptr
↓
No Data Copy
```

---

Memory Layout

Before:

```text
b1 → [Memory]
```

After:

```text
b1 → nullptr

b2 → [Memory]
```

---

# Move Assignment Operator

Transfers ownership during assignment.

---

## Syntax

```cpp
Buffer&
operator=(Buffer&& other);
```

---

Example

```cpp
Buffer&
operator=(Buffer&& other)
{
    if(this != &other)
    {
        delete[] data;

        data = other.data;
        size = other.size;

        other.data = nullptr;
        other.size = 0;
    }

    return *this;
}
```

---

## What Happens When Code Hits This?

```cpp
b2 = std::move(b1);
```

Execution:

```text
Release Old Resource
↓
Take Ownership
↓
Set Source To Null
↓
No Copy Operation
```

---

# Complete Rule of 5 Example

```cpp
#include <iostream>
#include <algorithm>

class Buffer
{
private:

    int* data;
    size_t size;

public:

    Buffer(size_t s)
        : size(s)
    {
        data = new int[size];
    }

    ~Buffer()
    {
        delete[] data;
    }

    Buffer(const Buffer& other)
    {
        size = other.size;

        data = new int[size];

        std::copy(
            other.data,
            other.data + size,
            data
        );
    }

    Buffer&
    operator=(const Buffer& other)
    {
        if(this != &other)
        {
            delete[] data;

            size = other.size;

            data = new int[size];

            std::copy(
                other.data,
                other.data + size,
                data
            );
        }

        return *this;
    }

    Buffer(Buffer&& other)
    {
        data = other.data;
        size = other.size;

        other.data = nullptr;
        other.size = 0;
    }

    Buffer&
    operator=(Buffer&& other)
    {
        if(this != &other)
        {
            delete[] data;

            data = other.data;
            size = other.size;

            other.data = nullptr;
            other.size = 0;
        }

        return *this;
    }
};
```

---

# What Happens Internally

Example:

```cpp
Buffer b1(1000);

Buffer b2(std::move(b1));
```

---

Step 1

```text
b1.data → Memory
```

---

Step 2

Move Constructor Called

---

Step 3

```text
b2.data = b1.data
```

---

Step 4

```text
b1.data = nullptr
```

---

Result

```text
Ownership Transferred

No Memory Copy
```

---

# Copy vs Move Operations

| Copy           | Move                |
| -------------- | ------------------- |
| Deep Copy      | Ownership Transfer  |
| Slow           | Fast                |
| Extra Memory   | No Extra Memory     |
| Duplicate Data | Reuse Existing Data |

---

Example:

### Copy

```cpp
std::vector<int> v2 = v1;
```

Copies all elements.

---

### Move

```cpp
std::vector<int> v2 =
std::move(v1);
```

Transfers internal pointer.

---

# Resource Ownership Transfer

Move semantics is based on ownership transfer.

---

Resources:

```text
Heap Memory
Files
Sockets
DMA Buffers
Camera Buffers
Network Packets
```

---

Example

```cpp
std::unique_ptr<int> p1 =
std::make_unique<int>(10);

auto p2 =
std::move(p1);
```

After move:

```text
p1 = nullptr

p2 Owns Resource
```

---

# Rule of 5 in STL

STL heavily uses move semantics.

---

Example

```cpp
std::vector<std::string> names;

names.push_back("Linux");
```

Temporary string is moved.

---

Example

```cpp
return vectorData;
```

Compiler usually performs:

```text
Move
OR
Copy Elision
```

---

# Rule of 5 in Embedded Systems

Commonly used in:

```text
Embedded Linux
Automotive
ROS2
Middleware
Networking
```

---

Resource Types:

```text
Sensor Buffers
CAN Frames
Ethernet Packets
Camera Frames
Shared Memory
DMA Buffers
```

---

# Real-Time Example 1

## Camera Frame Processing

Without Move:

```text
Camera Buffer
↓
Copy
↓
Image Processing
```

Large overhead.

---

With Move:

```text
Camera Buffer
↓
Ownership Transfer
↓
Image Processing
```

Very fast.

---

# Real-Time Example 2

## Sensor Data Collection

```cpp
std::vector<float>
samples;

process(
std::move(samples)
);
```

No large data copy.

---

# Real-Time Example 3

## Network Stack

```cpp
Packet pkt;

queue.push(
std::move(pkt)
);
```

Packet memory ownership transferred.

---

# Advantages and Disadvantages

## Advantages

✔ Faster Performance

✔ Less Memory Usage

✔ Supports Move Semantics

✔ Efficient Resource Management

✔ Better STL Performance

✔ Ideal For Large Objects

---

## Disadvantages

✘ More Code

✘ More Complex

✘ Easy To Implement Incorrectly

✘ Moved-From Objects Require Care

---

# Interview Questions

## What is Rule of 5?

If a class defines one special member function for resource management, it often needs all five special member functions.

---

## List the Five Functions.

```cpp
Destructor

Copy Constructor

Copy Assignment Operator

Move Constructor

Move Assignment Operator
```

---

## Why Was Rule of 5 Introduced?

Because C++11 introduced move semantics.

Classes must now support both copying and moving.

---

## What Happens When Code Hits This?

```cpp
Buffer b2(
std::move(b1)
);
```

### Answer

```text
Move Constructor Called

Ownership Transferred

b1 Becomes Empty

No Data Copied
```

---

## Difference Between Copy Constructor and Move Constructor?

| Copy Constructor | Move Constructor       |
| ---------------- | ---------------------- |
| Copies Resources | Transfers Resources    |
| Slow             | Fast                   |
| Allocates Memory | Reuses Existing Memory |

---

## What is the State of Moved Object?

Most Important Interview Answer:

```text
Valid But Unspecified
```

You can destroy it or assign a new value to it.

---

## What is std::move?

Most Asked Question.

Answer:

```text
std::move does NOT move anything.

It converts an object into an rvalue reference,
allowing move operations.
```

---

## Rule of 3 vs Rule of 5?

| Rule of 3        | Rule of 5        |
| ---------------- | ---------------- |
| Destructor       | Destructor       |
| Copy Constructor | Copy Constructor |
| Copy Assignment  | Copy Assignment  |
| -                | Move Constructor |
| -                | Move Assignment  |

---

# Most Asked Interview Question

## Explain Rule of 5 with a Real-Time Example.

Rule of 5 is a C++11 resource management guideline stating that if a class manages resources such as heap memory, files, sockets, or hardware buffers, it should usually define a destructor, copy constructor, copy assignment operator, move constructor, and move assignment operator. The copy operations create independent copies of resources, while move operations transfer ownership without copying data. For example, in an automotive camera processing system, large image buffers can be moved between modules instead of copied, significantly improving performance and reducing memory usage.

---

# Interview Answer (2-Minute Version)

The Rule of 5 extends the Rule of 3 by adding move constructor and move assignment operator support introduced in C++11. It applies to classes that manage resources such as dynamic memory, files, sockets, or hardware buffers. The five special member functions ensure proper cleanup, copying, and ownership transfer. Copy operations perform deep copies, while move operations transfer ownership efficiently without duplicating resources. Rule of 5 is widely used in STL containers, smart pointers, embedded Linux applications, automotive software, ROS2 systems, and high-performance applications where minimizing memory copies is critical.

---

# Rule of 0

Modern C++ recommends:

```cpp
std::vector
std::string
std::unique_ptr
std::shared_ptr
```

instead of manual resource management.

Example:

```cpp
class Data
{
private:
    std::vector<int> values;
};
```

Compiler-generated functions are sufficient.

No Rule of 5 required.

---

# Quick Revision

```text
Rule of 5

Functions:
1. Destructor
2. Copy Constructor
3. Copy Assignment
4. Move Constructor
5. Move Assignment

Purpose:
Manage Resources Safely

Introduced:
C++11

Benefits:
✔ Fast
✔ Efficient
✔ Supports Move Semantics

Most Important:
std::move() DOES NOT MOVE
It Enables Move

Applies To:
✔ Heap Memory
✔ Files
✔ Sockets
✔ DMA Buffers
✔ Camera Frames
✔ Network Packets

Modern Alternative:
Rule of 0
```

---

# Conclusion

The Rule of 5 is a fundamental modern C++ concept that extends the Rule of 3 by incorporating move semantics. It ensures that classes managing resources correctly support destruction, copying, and ownership transfer. Understanding the Rule of 5 is essential for writing efficient, safe, and high-performance C++ code, especially in Embedded Linux, Automotive, Middleware, Networking, Robotics, and System Programming domains. It is also one of the most frequently asked topics in modern C++ interviews.
