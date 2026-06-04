# STL Basics in C++ (Standard Template Library)

## Table of Contents

1. [Introduction](#introduction)
2. [What is STL?](#what-is-stl)
3. [Why do we use STL?](#why-do-we-use-stl)
4. [History of STL](#history-of-stl)
5. [Main Components of STL](#main-components-of-stl)
6. [Containers](#containers)

   1. [Sequence Containers](#sequence-containers)
   2. [Associative Containers](#associative-containers)
   3. [Unordered Containers](#unordered-containers)
   4. [Container Adapters](#container-adapters)
7. [Iterators](#iterators)
8. [Algorithms](#algorithms)
9. [Function Objects (Functors)](#function-objects-functors)
10. [Common STL Containers](#common-stl-containers)
11. [Time Complexity Table](#time-complexity-table)
12. [How STL Works Internally](#how-stl-works-internally)
13. [STL in Embedded Systems](#stl-in-embedded-systems)
14. [Advantages and Disadvantages](#advantages-and-disadvantages)
15. [Interview Questions](#interview-questions)
16. [Conclusion](#conclusion)

---

# Introduction

The Standard Template Library (STL) is one of the most powerful features of C++.

It provides:

```text
Ready-Made Data Structures
+
Ready-Made Algorithms
+
Generic Programming
```

Instead of writing data structures from scratch, STL provides optimized implementations.

---

# What is STL?

### Definition

> STL (Standard Template Library) is a collection of template-based classes and functions that provide generic containers, algorithms, iterators, and function objects.

---

## Simple Meaning

Instead of creating:

```cpp
Custom Array
Custom Linked List
Custom Stack
Custom Queue
```

Use:

```cpp
vector
list
stack
queue
```

directly.

---

# Why do we use STL?

✔ Faster Development

✔ Reusable Code

✔ Optimized Performance

✔ Generic Programming

✔ Reduced Bugs

✔ Standardized Library

✔ Cross-Platform Support

---

# History of STL

Developed by:

```text
Alexander Stepanov
```

Goal:

```text
Generic Programming
```

STL became part of the C++ Standard Library.

---

# Main Components of STL

STL consists of four major components.

```text
STL
 │
 ├── Containers
 ├── Iterators
 ├── Algorithms
 └── Functors
```

---

# Containers

Containers store data.

---

## Types of Containers

```text
Containers
   │
   ├── Sequence
   ├── Associative
   ├── Unordered
   └── Adapters
```

---

# Sequence Containers

Store elements sequentially.

---

## Vector

Dynamic array.

```cpp
#include <vector>

std::vector<int> nums;
```

---

### Features

✔ Dynamic Size

✔ Fast Random Access

✔ Contiguous Memory

---

### Example

```cpp
std::vector<int> v;

v.push_back(10);
v.push_back(20);
v.push_back(30);
```

---

Memory:

```text
+----+----+----+
| 10 | 20 | 30 |
+----+----+----+
```

---

## What Happens When Code Hits This?

```cpp
v.push_back(40);
```

### Internally

```text
1. Check capacity
2. Space available?
      Yes → Insert
      No  → Allocate larger memory
3. Copy old data
4. Free old memory
```

---

# List

Doubly Linked List.

```cpp
#include <list>

std::list<int> l;
```

---

Memory:

```text
10 <-> 20 <-> 30
```

---

### Features

✔ Fast Insertions

✔ Fast Deletions

✘ No Random Access

---

# Deque

Double Ended Queue.

```cpp
std::deque<int> d;
```

---

Supports:

```cpp
push_front()
push_back()
```

---

# Array

Fixed Size STL Array.

```cpp
std::array<int,5> arr;
```

---

# Forward List

Singly Linked List.

```cpp
std::forward_list<int> fl;
```

---

# Associative Containers

Stored in sorted order.

Usually implemented using:

```text
Red-Black Tree
```

---

# Set

Stores unique values.

```cpp
std::set<int> s;
```

---

Example:

```cpp
s.insert(10);
s.insert(20);
s.insert(10);
```

Output:

```text
10 20
```

Duplicate removed.

---

# Multiset

Allows duplicates.

```cpp
std::multiset<int> ms;
```

---

# Map

Key-Value pair container.

```cpp
std::map<int,string> m;
```

---

Example:

```cpp
m[1] = "John";
m[2] = "Alex";
```

---

Memory:

```text
1 → John
2 → Alex
```

---

# Multimap

Allows duplicate keys.

```cpp
std::multimap<int,string> mm;
```

---

# Unordered Containers

Implemented using:

```text
Hash Tables
```

---

# Unordered Set

```cpp
std::unordered_set<int> us;
```

---

Features

✔ Fast Lookup

✔ O(1) Average Search

✘ Not Sorted

---

# Unordered Map

```cpp
std::unordered_map<int,string> um;
```

---

# Container Adapters

Built on existing containers.

---

## Stack

LIFO

```cpp
std::stack<int> st;
```

---

Memory:

```text
Top
 ↓
30
20
10
```

---

## Queue

FIFO

```cpp
std::queue<int> q;
```

---

Memory:

```text
Front → 10 20 30 ← Rear
```

---

## Priority Queue

Heap-Based.

```cpp
std::priority_queue<int> pq;
```

---

Highest priority element first.

---

# Iterators

### Definition

Iterators are objects used to traverse containers.

---

## Example

```cpp
std::vector<int> v = {1,2,3};

for(auto it=v.begin(); it!=v.end(); ++it)
{
    cout << *it;
}
```

---

## Types

```text
Input Iterator
Output Iterator
Forward Iterator
Bidirectional Iterator
Random Access Iterator
```

---

# Algorithms

STL provides ready-made algorithms.

Header:

```cpp
#include <algorithm>
```

---

## Sort

```cpp
sort(v.begin(), v.end());
```

---

## Find

```cpp
find(v.begin(), v.end(), 10);
```

---

## Count

```cpp
count(v.begin(), v.end(), 5);
```

---

## Reverse

```cpp
reverse(v.begin(), v.end());
```

---

## Max Element

```cpp
max_element(v.begin(),v.end());
```

---

# Function Objects (Functors)

Objects behaving like functions.

---

## Example

```cpp
class Add
{
public:
    int operator()(int a,int b)
    {
        return a+b;
    }
};
```

---

Usage:

```cpp
Add obj;

obj(10,20);
```

---

# Common STL Containers

| Container      | Data Structure     |
| -------------- | ------------------ |
| vector         | Dynamic Array      |
| list           | Doubly Linked List |
| forward_list   | Singly Linked List |
| deque          | Double Ended Queue |
| set            | Red-Black Tree     |
| multiset       | Red-Black Tree     |
| map            | Red-Black Tree     |
| unordered_set  | Hash Table         |
| unordered_map  | Hash Table         |
| stack          | Adapter            |
| queue          | Adapter            |
| priority_queue | Heap               |

---

# Time Complexity Table

| Operation     | Vector | List | Set      | Unordered Set |
| ------------- | ------ | ---- | -------- | ------------- |
| Insert        | O(1)*  | O(1) | O(log n) | O(1) Avg      |
| Delete        | O(n)   | O(1) | O(log n) | O(1) Avg      |
| Search        | O(n)   | O(n) | O(log n) | O(1) Avg      |
| Random Access | O(1)   | O(n) | O(log n) | Not Supported |

*Amortized

---

# How STL Works Internally

Example:

```cpp
std::vector<int> v;
```

---

### Internally

```text
Pointer
Size
Capacity
```

Stored inside vector object.

---

## What Happens When Code Hits This?

```cpp
v.push_back(100);
```

### Internal Flow

```text
1. Check Capacity
2. Allocate Memory if Needed
3. Construct Element
4. Update Size
5. Return
```

---

# STL in Embedded Systems

STL usage depends on memory constraints.

---

# Commonly Used

✔ array

✔ vector

✔ algorithm

✔ string

✔ pair

✔ tuple

---

# Used In

### Embedded Linux

* Middleware
* Drivers
* Networking
* Applications

---

### Automotive

* AUTOSAR Adaptive
* ADAS
* Infotainment Systems

---

### Robotics

* ROS2
* Sensor Frameworks

---

# Avoided In Small MCUs

Because:

```text
Dynamic Memory
Heap Fragmentation
Larger Binary Size
```

---

# Advantages and Disadvantages

## Advantages

✔ Faster Development

✔ Generic Programming

✔ Optimized Code

✔ Reusable Components

✔ Standardized

✔ Cross Platform

---

## Disadvantages

✘ Increased Compile Time

✘ Dynamic Memory Usage

✘ Larger Binary Size

✘ Complex Error Messages

---

# Interview Questions

## What is STL?

STL is the Standard Template Library that provides generic containers, algorithms, iterators, and functors.

---

## What are the Four Components of STL?

```text
1. Containers
2. Iterators
3. Algorithms
4. Functors
```

---

## What is a Vector?

A dynamic array that can grow or shrink during runtime.

---

## Difference Between Vector and List?

| Vector             | List               |
| ------------------ | ------------------ |
| Dynamic Array      | Linked List        |
| Fast Random Access | Slow Random Access |
| Slow Middle Insert | Fast Middle Insert |

---

## Difference Between Map and Unordered Map?

| Map            | Unordered Map |
| -------------- | ------------- |
| Sorted         | Unsorted      |
| Red-Black Tree | Hash Table    |
| O(log n)       | O(1) Avg      |

---

## What Happens When Code Hits This?

```cpp
v.push_back(10);
```

### Answer

```text
1. Capacity checked
2. Memory allocated if needed
3. Element inserted
4. Size incremented
```

---

## Why is STL Less Preferred in Small Embedded Systems?

Because STL containers often use dynamic memory allocation, which may cause heap fragmentation and increase code size.

---

# Most Asked Interview Question

## Explain STL with a Real-Time Example.

STL is a collection of generic containers, algorithms, iterators, and functors that simplify C++ development. For example, instead of implementing a dynamic array manually, developers can use `std::vector`, which automatically handles memory allocation, resizing, and element access. STL improves productivity, reliability, and performance because the containers and algorithms are thoroughly optimized and tested.

---

# Interview Answer (2-Minute Version)

The Standard Template Library (STL) is a powerful C++ library that provides reusable implementations of data structures and algorithms. Its four major components are containers, iterators, algorithms, and functors. Common containers include vector, list, map, set, and unordered_map. STL uses templates to provide generic programming, allowing the same code to work with multiple data types. In embedded Linux, automotive software, robotics, and application development, STL greatly reduces development time and improves code quality. However, in small microcontrollers, STL usage is sometimes limited due to dynamic memory requirements.

---

# Quick Revision

```text
STL
 │
 ├── Containers
 │     ├─ vector
 │     ├─ list
 │     ├─ set
 │     ├─ map
 │     └─ unordered_map
 │
 ├── Iterators
 │
 ├── Algorithms
 │     ├─ sort()
 │     ├─ find()
 │     ├─ reverse()
 │     └─ count()
 │
 └── Functors

Popular:
✔ vector
✔ map
✔ set
✔ queue
✔ stack

Used In:
- Embedded Linux
- AUTOSAR Adaptive
- Robotics
- Networking
```

---

# Conclusion

The Standard Template Library (STL) is a cornerstone of modern C++ programming. It provides efficient, reusable, and generic implementations of containers and algorithms, significantly reducing development effort. Understanding STL containers, iterators, algorithms, and their internal working is essential for C++ developers and is one of the most frequently asked topics in technical interviews, especially for embedded Linux, automotive, and software engineering roles.
