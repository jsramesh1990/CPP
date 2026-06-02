# Objects in C++ (Object-Oriented Programming)

## Table of Contents

1. [Introduction](#introduction)
2. [What is an Object?](#what-is-an-object)
3. [Why do we use Objects?](#why-do-we-use-objects)
4. [Relationship between Class and Object](#relationship-between-class-and-object)
5. [Object Creation](#object-creation)
6. [How Objects Work Internally](#how-objects-work-internally)
7. [Object Memory Layout](#object-memory-layout)
8. [Accessing Object Members](#accessing-object-members)
9. [Object Initialization](#object-initialization)
10. [Object Lifetime](#object-lifetime)
11. [Types of Objects](#types-of-objects)
12. [Objects in Embedded Systems](#objects-in-embedded-systems)
13. [Advantages and Disadvantages](#advantages-and-disadvantages)
14. [Interview Questions](#interview-questions)
15. [Conclusion](#conclusion)

---

# Introduction

In C++, a class is only a **blueprint**.

To actually use the class, we create an **Object**.

An object represents a real instance of a class and occupies memory.

---

# What is an Object?

### Definition

> An object is an instance of a class that contains its own copy of data members and can access the class member functions.

---

## Simple Meaning

```text
Class = Blueprint

Object = Real Thing Created From Blueprint
```

---

## Real-Life Example

```text
Class = Car

Objects:
Honda City
Hyundai i20
BMW X5
Tesla Model 3
```

All cars share the same design (class) but have different values.

---

# Why do we use Objects?

✔ Create real instances of classes

✔ Store data independently

✔ Access member functions

✔ Support Object-Oriented Programming

✔ Improve modularity and code reuse

---

# Relationship between Class and Object

## Class

```cpp
class Car
{
public:
    int speed;
};
```

---

## Object

```cpp
Car car1;
```

---

## Visualization

```text
Class
 ↓
Blueprint
 ↓
Object Creation
 ↓
Memory Allocated
 ↓
Object Ready
```

---

# Object Creation

## Syntax

```cpp
ClassName objectName;
```

---

## Example

```cpp
class Car
{
public:
    int speed;
};

Car car1;
```

---

# What Happens When Code Hits This?

```cpp
Car car1;
```

### Internal Steps

```text
1. Compiler checks class definition
2. Memory allocated for object
3. Data members created
4. Constructor called automatically
5. Object becomes usable
```

---

# How Objects Work Internally

## Example

```cpp
class Car
{
public:
    int speed;
    int gear;
};

Car car1;
```

---

## Memory Allocation

```text
car1
+------------+
| speed       |
| gear        |
+------------+
```

---

### Important

Member functions are NOT stored separately in each object.

Only data members consume object memory.

---

# Object Memory Layout

## Example

```cpp
class Car
{
public:
    int speed;
    char gear;
};
```

---

## Memory

```text
speed = 4 bytes
gear  = 1 byte

Total = May be 8 bytes
(due to padding)
```

---

## Why Padding?

To improve CPU access efficiency.

---

# Accessing Object Members

Use the dot (`.`) operator.

---

## Example

```cpp
Car car1;

car1.speed = 100;
car1.gear = 4;
```

---

## What Happens Internally?

```text
1. Find address of car1
2. Find offset of speed
3. Write value 100
```

---

# Object Initialization

## Method 1: Direct Assignment

```cpp
Car car1;

car1.speed = 100;
```

---

## Method 2: Constructor

```cpp
class Car
{
public:
    int speed;

    Car()
    {
        speed = 100;
    }
};
```

---

## What Happens?

```text
Object Created
↓
Constructor Called
↓
speed Initialized
```

---

# Object Lifetime

An object exists from creation until destruction.

---

## Example

```cpp
void test()
{
    Car car1;
}
```

---

## Flow

```text
Enter Function
↓
Object Created
↓
Constructor Called
↓
Function Ends
↓
Destructor Called
↓
Object Removed
```

---

# Types of Objects

## 1. Local Object (Stack Object)

```cpp
Car car1;
```

---

### Characteristics

✔ Created on stack

✔ Automatically destroyed

✔ Fast access

---

## 2. Global Object

```cpp
Car car1;
```

Outside all functions.

---

### Characteristics

✔ Created before main()

✔ Destroyed after program ends

---

## 3. Dynamic Object (Heap Object)

```cpp
Car* car1 = new Car();
```

---

### What Happens?

```text
Heap Memory Allocated
↓
Constructor Called
↓
Object Created
```

---

### Deletion

```cpp
delete car1;
```

---

# Objects in Embedded Systems

Objects are widely used in embedded C++ applications.

---

## 1. UART Driver

```cpp
class UART
{
public:
    void send();
};

UART uart1;
```

---

## 2. GPIO Driver

```cpp
GPIO led;
GPIO button;
```

---

## 3. Sensor Drivers

```cpp
TemperatureSensor temp;
```

---

## 4. Automotive Software

Objects represent:

* Sensors
* ECUs
* Communication modules
* Diagnostic services

---

## 5. Embedded Linux

Objects are used in:

* Device abstraction
* Middleware
* Service management

---

# Advantages and Disadvantages

## Advantages

✔ Encapsulation

✔ Modularity

✔ Code reuse

✔ Easy maintenance

✔ Real-world modeling

---

## Disadvantages

✘ Memory overhead

✘ Constructor overhead

✘ Dynamic objects may cause fragmentation

✘ More complex than procedural programming

---

# Interview Questions

## What is an Object?

An object is an instance of a class that occupies memory and can access the class members.

---

## Does a Class Occupy Memory?

No.

Only objects occupy memory.

---

## What Happens When an Object is Created?

```text
1. Memory allocated
2. Constructor called
3. Object initialized
```

---

## What is the Difference Between Class and Object?

| Class             | Object            |
| ----------------- | ----------------- |
| Blueprint         | Instance          |
| No memory         | Memory allocated  |
| Defines structure | Holds actual data |

---

## Do Member Functions Consume Object Memory?

No.

Only data members contribute to object size.

---

## Why are Objects Used in Embedded Systems?

Objects provide abstraction and modular design for peripherals, sensors, drivers, and communication modules.

---

# Most Asked Interview Question

## Explain Objects in C++ with a Real-Time Example.

An object is an instance of a class that contains actual data and can use the functions defined in the class. For example, a UART class may define transmit and receive operations, while UART1 and UART2 are objects representing actual hardware peripherals. When an object is created, memory is allocated for its data members and its constructor is automatically called. Objects help implement modular, reusable, and maintainable embedded software.

---

# Quick Revision

```text
Object = Instance of Class

Class → Blueprint
Object → Real Instance

Creation:
Car car1;

When Created:
1. Memory allocated
2. Constructor called
3. Object ready

Used in:
- Drivers
- Sensors
- HAL
- Automotive ECUs
```

---

# Conclusion

Objects are the runtime instances of classes and form the core of Object-Oriented Programming in C++. They allow data and behavior to be combined into reusable modules. In embedded systems, objects are commonly used for hardware abstraction, driver development, sensor interfaces, and automotive software architectures. Understanding objects is fundamental for C++ and embedded software interviews.
