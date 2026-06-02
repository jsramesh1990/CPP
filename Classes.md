# Classes in C++ (Object-Oriented Programming)

## Table of Contents

1. [Introduction](#introduction)
2. [What is a Class?](#what-is-a-class)
3. [Why do we use Classes?](#why-do-we-use-classes)
4. [Class vs Object](#class-vs-object)
5. [Syntax of a Class](#syntax-of-a-class)
6. [Class Members](#class-members)
7. [Access Specifiers](#access-specifiers)
8. [Creating Objects](#creating-objects)
9. [Constructors](#constructors)
10. [Destructors](#destructors)
11. [Member Functions](#member-functions)
12. [this Pointer](#this-pointer)
13. [Static Members](#static-members)
14. [Classes in Embedded Systems](#classes-in-embedded-systems)
15. [Advantages and Disadvantages](#advantages-and-disadvantages)
16. [Interview Questions](#interview-questions)
17. [Conclusion](#conclusion)

---

# Introduction

C++ is an **Object-Oriented Programming (OOP)** language.

The main building block of OOP is a **Class**.

A class allows us to combine:

* Data (Variables)
* Functions (Methods)

into a single unit.

---

# What is a Class?

### Definition

> A class is a user-defined data type that contains data members and member functions.

---

## Simple Meaning

A class acts as a **blueprint** for creating objects.

---

## Real-Life Example

```text
Class = Car Design

Object 1 = Honda City
Object 2 = Hyundai i20
Object 3 = BMW X5
```

---

# Why do we use Classes?

✔ Code reusability

✔ Data hiding

✔ Encapsulation

✔ Easy maintenance

✔ Better organization

✔ Real-world modeling

---

# Class vs Object

| Class               | Object           |
| ------------------- | ---------------- |
| Blueprint           | Real instance    |
| No memory allocated | Memory allocated |
| Defines properties  | Uses properties  |

---

## Example

```cpp
class Car
{
};
```

Car is a class.

---

```cpp
Car myCar;
```

myCar is an object.

---

# Syntax of a Class

```cpp
class ClassName
{
    // Data Members

    // Member Functions
};
```

---

## Example

```cpp
class Car
{
public:
    int speed;

    void display()
    {
        cout << speed;
    }
};
```

---

# Class Members

A class contains:

## 1. Data Members

Variables inside class.

```cpp
class Car
{
public:
    int speed;
    int gear;
};
```

---

## 2. Member Functions

Functions inside class.

```cpp
void start()
{
    cout << "Car Started";
}
```

---

# Access Specifiers

Used to control access.

---

## 1. Public

Accessible everywhere.

```cpp
public:
    int speed;
```

---

## 2. Private

Accessible only inside class.

```cpp
private:
    int speed;
```

---

## 3. Protected

Accessible inside class and derived class.

```cpp
protected:
    int speed;
```

---

## Access Specifier Table

| Specifier | Same Class | Derived Class | Outside Class |
| --------- | ---------- | ------------- | ------------- |
| private   | Yes        | No            | No            |
| protected | Yes        | Yes           | No            |
| public    | Yes        | Yes           | Yes           |

---

# Creating Objects

```cpp
class Car
{
public:
    int speed;
};

int main()
{
    Car c1;
}
```

---

## What happens when code hits this?

```cpp
Car c1;
```

### Internally

```text
1. Memory allocated for c1
2. Data members created
3. Constructor called (if available)
4. Object becomes ready
```

---

# Constructors

### Definition

> A constructor is a special member function automatically called when an object is created.

---

## Syntax

```cpp
class Car
{
public:
    Car()
    {
        cout << "Constructor Called";
    }
};
```

---

## Example

```cpp
Car c1;
```

### What happens?

```text
1. Memory allocated
2. Constructor executes automatically
3. Object initialized
```

---

# Destructors

### Definition

> A destructor is automatically called when an object is destroyed.

---

## Syntax

```cpp
~Car()
{
    cout << "Destructor Called";
}
```

---

## What happens?

```text
Program ends
↓
Object removed
↓
Destructor executes
↓
Memory cleaned
```

---

# Member Functions

Functions inside class.

---

## Example

```cpp
class Car
{
public:
    void start()
    {
        cout << "Started";
    }
};
```

---

## Call

```cpp
Car c1;
c1.start();
```

---

## What happens when code hits it?

```text
1. Object address found
2. Function called
3. 'this' pointer passed automatically
4. Function executes
```

---

# this Pointer

### Definition

> `this` is a hidden pointer that points to the current object.

---

## Example

```cpp
class Car
{
public:
    int speed;

    void setSpeed(int speed)
    {
        this->speed = speed;
    }
};
```

---

## What happens?

```text
this → address of current object
```

---

# Static Members

Shared by all objects.

---

## Example

```cpp
class Car
{
public:
    static int count;
};

int Car::count = 0;
```

---

## What happens?

```text
Only one copy exists
Shared by all objects
```

---

# Classes in Embedded Systems

Classes are heavily used in:

## 1. Device Drivers

```cpp
class UART
{
public:
    void send();
};
```

---

## 2. Sensor Interfaces

```cpp
class TemperatureSensor
{
public:
    float readTemp();
};
```

---

## 3. Hardware Abstraction Layer (HAL)

```cpp
class GPIO
{
public:
    void setPin();
};
```

---

## 4. Automotive Software

Used in:

* ADAS
* Infotainment
* AUTOSAR Components

---

## 5. Embedded Linux

Used in:

* Drivers
* Middleware
* Frameworks

---

# Advantages and Disadvantages

## Advantages

✔ Encapsulation

✔ Code reuse

✔ Better organization

✔ Easy maintenance

✔ Security through data hiding

✔ Real-world modeling

---

## Disadvantages

✘ More memory usage

✘ Slightly slower than pure C

✘ Complexity for small projects

✘ Object creation overhead

---

# Interview Questions

## What is a Class?

A class is a user-defined data type that combines data and functions into a single unit.

---

## What is an Object?

An object is an instance of a class.

---

## Difference between Class and Object?

| Class     | Object           |
| --------- | ---------------- |
| Blueprint | Instance         |
| No memory | Memory allocated |

---

## What is Constructor?

A special function automatically called during object creation.

---

## What is Destructor?

A special function automatically called when object is destroyed.

---

## What is this Pointer?

A hidden pointer that points to the current object.

---

## Why use Classes in Embedded Systems?

Classes provide abstraction, modularity, code reuse, and easier hardware management through object-oriented design.

---

# Most Asked Interview Question

## Explain Class in C++ with a real-time example.

A class is a user-defined blueprint that combines data and functions into a single unit. For example, in an embedded system, a UART driver can be implemented as a class containing baud rate, transmit, and receive functions. Objects created from the class represent actual UART peripherals. Classes improve code organization, reusability, and maintainability, making them widely used in embedded software, automotive systems, and device drivers.

---

# Quick Revision

```text
Class = Blueprint

Object = Instance

Features:
- Data Members
- Member Functions
- Constructors
- Destructors
- Encapsulation

Used in:
- Drivers
- HAL
- Automotive
- Embedded Linux
```

---

# Conclusion

Classes are the foundation of Object-Oriented Programming in C++. They help organize code, improve reusability, and provide abstraction. In embedded systems, classes are widely used for drivers, hardware abstraction layers, sensor interfaces, and automotive software, making them a key topic for both development and interviews.
