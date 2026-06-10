# Move Semantics

## Table of Contents

1. [Introduction](#introduction)
2. [Why Move Semantics Was Introduced](#why-move-semantics-was-introduced)
3. [Copy vs Move](#copy-vs-move)
4. [Lvalue and Rvalue](#lvalue-and-rvalue)
5. [Rvalue References](#rvalue-references)
6. [Move Constructor](#move-constructor)
7. [Move Assignment Operator](#move-assignment-operator)
8. [std::move](#stdmove)
9. [How Move Semantics Works Internally](#how-move-semantics-works-internally)
10. [Resource Ownership Transfer](#resource-ownership-transfer)
11. [Rule of Five](#rule-of-five)
12. [Move Semantics in STL](#move-semantics-in-stl)
13. [Move Semantics in Embedded Systems](#move-semantics-in-embedded-systems)
14. [Advantages and Disadvantages](#advantages-and-disadvantages)
15. [Interview Questions](#interview-questions)
16. [Real-Time Examples](#real-time-examples)
17. [Quick Revision](#quick-revision)
18. [Conclusion](#conclusion)

---

# Introduction

Move Semantics is one of the most important features introduced in:

```text
C++11
```

It allows:

```text
Transfer Resource Ownership
Instead of Copying Resources
```

which improves:

* Performance
* Memory Usage
* Execution Speed

---

# Why Move Semantics Was Introduced

Before C++11, objects were copied.

Example:

```cpp
std::vector<int> v1(1000000);

std::vector<int> v2 = v1;
```

---

## What Happens Internally?

```text
v1
 ↓
Allocate New Memory
 ↓
Copy 1,000,000 Elements
 ↓
Store in v2
```

Expensive operation.

---

Problems:

✔ Extra Memory

✔ Extra CPU Cycles

✔ Slower Execution

---

Solution:

```text
Move Resource Ownership
Instead of Copying Data
```

---

# Copy vs Move

## Copy Operation

```cpp
std::vector<int> v2 = v1;
```

Memory Layout:

```text
v1 -----> [DATA]

v2 -----> [NEW DATA]
            ↑
         Copied
```

---

## Move Operation

```cpp
std::vector<int> v2 = std::move(v1);
```

Memory Layout:

```text
Before

v1 -----> [DATA]

After Move

v1 -----> nullptr

v2 -----> [DATA]
```

No data copied.

Only ownership transferred.

---

# Lvalue and Rvalue

Understanding Move Semantics requires understanding these concepts.

---

## Lvalue

Has a memory address.

Example:

```cpp
int x = 10;
```

Here:

```cpp
x
```

is an lvalue.

---

## Rvalue

Temporary object.

Example:

```cpp
10
```

or

```cpp
x + y
```

These are rvalues.

---

Example:

```cpp
int a = 10;
int b = 20;

int c = a + b;
```

```text
a,b,c = Lvalues

a+b = Rvalue
```

---

# Rvalue References

Introduced in C++11.

Syntax:

```cpp
&&
```

Example:

```cpp
int&& ref = 100;
```

---

Meaning:

```text
Reference To Temporary Object
```

---

Why Needed?

Because move operations work on temporary objects.

---

# Move Constructor

Used when creating an object from another temporary object.

---

## Syntax

```cpp
ClassName(ClassName&& obj);
```

---

Example

```cpp
class Buffer
{
private:

    int* data;

public:

    Buffer(int size)
    {
        data = new int[size];
    }

    Buffer(Buffer&& obj)
    {
        data = obj.data;

        obj.data = nullptr;
    }
};
```

---

## What Happens When Code Hits This?

```cpp
Buffer b2(std::move(b1));
```

Execution:

```text
1. Move Constructor Called

2. b2.data = b1.data

3. b1.data = nullptr

4. Ownership Transferred
```

---

# Move Assignment Operator

Transfers resources after object creation.

---

## Syntax

```cpp
ClassName&
operator=(ClassName&& obj);
```

---

Example

```cpp
Buffer& operator=(Buffer&& obj)
{
    delete[] data;

    data = obj.data;

    obj.data = nullptr;

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
1. Old Resource Released

2. Resource Ownership Moved

3. Source Set To nullptr

4. No Data Copy
```

---

# std::move

Most Asked Interview Topic.

---

Definition:

```text
std::move does NOT move anything.
```

---

It simply converts:

```text
Lvalue
   ↓
Rvalue Reference
```

---

Example

```cpp
std::move(obj);
```

Internally similar to:

```cpp
static_cast<T&&>(obj);
```

---

## What Happens When Code Hits This?

```cpp
std::move(obj);
```

Compiler:

```text
Treat obj As Temporary Object
```

Then:

```text
Move Constructor
OR
Move Assignment
```

can be invoked.

---

# How Move Semantics Works Internally

Example

```cpp
std::vector<int> v2 =
std::move(v1);
```

---

Internal Steps

```text
Step 1

v1
 ↓
Pointer -> Data
```

---

```text
Step 2

Move Constructor Called
```

---

```text
Step 3

v2 Pointer = v1 Pointer
```

---

```text
Step 4

v1 Pointer = nullptr
```

---

```text
Result

No Data Copied
```

---

# Resource Ownership Transfer

Move semantics transfers ownership.

---

Example Resource Types

```text
Heap Memory
File Handles
Sockets
Mutexes
Buffers
Large STL Containers
```

---

Example

```cpp
std::unique_ptr<int> p1 =
std::make_unique<int>(100);

auto p2 =
std::move(p1);
```

---

After move:

```text
p1 -> nullptr

p2 -> Owns Resource
```

---

# Rule of Five

If class manages resources and defines one of:

```cpp
Destructor
Copy Constructor
Copy Assignment
Move Constructor
Move Assignment
```

Usually define all five.

---

Example

```cpp
class Buffer
{
public:

    ~Buffer();

    Buffer(const Buffer&);

    Buffer& operator=(const Buffer&);

    Buffer(Buffer&&);

    Buffer& operator=(Buffer&&);
};
```

---

# Move Semantics in STL

STL heavily uses move semantics.

---

Example

```cpp
std::vector<std::string> v;

v.push_back("Embedded");
```

---

What Happens?

```text
Temporary String Created
          ↓
Moved Into Vector
```

instead of copied.

---

Example

```cpp
v.emplace_back("Linux");
```

Even more efficient.

---

# Move Semantics in Embedded Systems

Very useful for:

### Embedded Linux

```text
Large Buffers
Network Packets
Sensor Data
```

---

### Automotive

```text
CAN Messages
Ethernet Frames
Radar Data
Camera Buffers
```

---

### Middleware

```text
IPC Messages
Shared Buffers
Log Packets
```

---

### ROS2

```text
Sensor Messages
Image Frames
Point Clouds
```

Move semantics reduces copying huge datasets.

---

# Real-Time Example 1

## Camera Frame Transfer

Without Move:

```text
Camera Buffer
       ↓
Copy
       ↓
Processing Module
```

Large delay.

---

With Move:

```text
Camera Buffer
       ↓
Ownership Transfer
       ↓
Processing Module
```

No copy.

---

Benefit:

```text
Faster ADAS Processing
```

---

# Real-Time Example 2

## Network Packet Processing

```cpp
Packet pkt =
receivePacket();

queue.push(std::move(pkt));
```

---

Execution:

```text
Packet Memory
       ↓
Ownership Moved
       ↓
Queue
```

No packet duplication.

---

# Real-Time Example 3

## Sensor Data Logger

```cpp
std::vector<float> sensorData;

logger.store(
std::move(sensorData));
```

---

Instead of copying:

```text
10000 Sensor Samples
```

ownership transferred instantly.

---

# Advantages and Disadvantages

## Advantages

✔ Faster Execution

✔ Less Memory Usage

✔ Reduced Copy Operations

✔ Better STL Performance

✔ Ideal For Large Objects

✔ Efficient Resource Handling

---

## Disadvantages

✘ More Complex Design

✘ Moved-From Objects Must Not Be Misused

✘ Requires Understanding of Ownership

---

# Interview Questions

## What is Move Semantics?

Move semantics transfers ownership of resources from one object to another instead of copying resources.

---

## Why Was Move Semantics Introduced?

To eliminate expensive deep copies and improve performance.

---

## What is std::move?

Most Important Answer:

```text
std::move does NOT move anything.
```

It only converts an object into an rvalue reference, enabling move operations.

---

## What Happens When Code Hits This?

```cpp
std::vector<int> v2 =
std::move(v1);
```

### Answer

```text
1. Move Constructor Called

2. Pointer Ownership Transferred

3. v1 Becomes Empty/Valid State

4. No Data Copied
```

---

## Difference Between Copy and Move?

| Copy            | Move                |
| --------------- | ------------------- |
| Duplicates Data | Transfers Ownership |
| Slow            | Fast                |
| Extra Memory    | No Extra Memory     |
| Deep Copy       | Pointer Transfer    |

---

## What is an Rvalue Reference?

A reference that binds to temporary objects and enables move semantics.

Syntax:

```cpp
T&&
```

---

## Why is Move Constructor Faster?

Because it transfers pointers/resources instead of copying actual data.

---

## What Happens to Source Object After Move?

It remains:

```text
Valid
But Unspecified
```

Usually set to:

```cpp
nullptr
```

for owned resources.

---

## What is Rule of Five?

If a class manages resources and defines one special member function related to copying/moving/destruction, it typically needs all five special member functions.

---

# Most Asked Interview Question

## Explain Move Semantics with Real Example.

Move semantics allows ownership transfer instead of resource copying. For example, when moving a large vector containing one million elements, the move operation transfers the internal memory pointer from one object to another without copying the elements. This significantly reduces memory usage and execution time. In embedded Linux, automotive systems, ROS2, and middleware applications, move semantics is used to efficiently transfer large sensor buffers, network packets, and image frames between modules.

---

# Interview Answer (2-Minute Version)

Move semantics is a C++11 feature that improves performance by transferring ownership of resources instead of copying them. It relies on rvalue references (`&&`), move constructors, and move assignment operators. The `std::move()` function converts an object into an rvalue reference, enabling resource transfer. Internally, move operations typically transfer pointers, file handles, sockets, or buffer ownership while leaving the source object in a valid but unspecified state. Move semantics is heavily used in STL containers, smart pointers, embedded Linux applications, automotive middleware, ROS2 frameworks, and high-performance systems where reducing memory copies is critical.

---

# Quick Revision

```text
Move Semantics

Purpose:
Transfer Ownership Instead of Copying

Introduced:
C++11

Key Components:
1. Rvalue References (&&)
2. std::move()
3. Move Constructor
4. Move Assignment Operator

Most Important:
std::move() DOES NOT MOVE
It Enables Move

Benefits:
✔ Faster
✔ Less Memory
✔ No Deep Copy

Used In:
✔ STL Containers
✔ unique_ptr
✔ ROS2
✔ Automotive
✔ Embedded Linux
✔ Sensor Frameworks
✔ Network Stacks
```

---

# Conclusion

Move Semantics is one of the most powerful features introduced in C++11. By transferring ownership rather than copying resources, it dramatically improves performance and memory efficiency. Understanding rvalue references, move constructors, move assignment operators, and `std::move()` is essential for modern C++ development and is a frequently asked topic in Embedded Linux, Automotive, Middleware, Robotics, and C++ interviews.
