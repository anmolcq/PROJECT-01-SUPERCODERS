# Daily Development Journal

**Date:** 26 June 2026

---

## What I Worked On Today

Today was less about writing new features and more about understanding the design decisions behind my Redis Lite project. I spent a good amount of time improving the generic behavior of my `HashMap`, researching how hashing works internally, and restructuring the Redis Lite project into a cleaner architecture.

I also began studying how Redis actually processes commands. Instead of directly implementing the parser, I first wanted to understand the complete flow—from user input to command execution—so that I don't end up redesigning everything later.

---

## Work Completed

### Research on User Defined Hashing

Continued improving the generic hashing system.

Instead of only supporting primitive types, I explored how custom objects should be hashed and the different ways a user can provide hash functions.

There are mainly two approaches:

```text
Default Hasher

        OR

Custom Hasher Provided by User
```

This makes the `HashMap` flexible enough to support almost any user-defined object.

---

### Understanding Floating Point Hashing

While reviewing my floating-point hash implementation, I noticed that the FNV-1a algorithm uses very large constants.

Initially I thought using smaller numbers might make the implementation simpler.

Example:

```text
Large Prime Constants

        vs

Smaller Numbers
```

After comparing different approaches, I found that the original FNV-1a constants produce a much better distribution of hash values and reduce collisions significantly.

So I decided to keep the existing implementation.

---

### Understanding reinterpret_cast

Another topic I spent time researching was why floating-point hashing uses:

```cpp
reinterpret_cast
```

instead of

```cpp
static_cast
```

I learned that `static_cast` converts the numeric value itself, whereas `reinterpret_cast` allows the hash function to access the raw binary representation of the floating-point number.

Flow:

```text
Float Value

      │

Binary Bits

      │

reinterpret_cast

      │

Hash Function
```

This makes hashing much more reliable for floating-point values.

---

## Project Restructuring

Today I also reorganized the Redis Lite project into a cleaner structure.

Current project layout:

```text
RedisLite

│

├── include/

│      ├── DynamicArray.hpp
│      ├── LinkedList.hpp
│      ├── HashMap.hpp
│      └── RedisLite.hpp

│

├── src/
│      └── RedisLite.cpp

│

└── CMakeLists.txt
```

Separating interfaces and implementations makes the project easier to maintain as it grows.

---

## Setting up CMake

Started configuring the build system using CMake.

Basic flow:

```text
Source Files

      │

CMakeLists.txt

      │

Compiler

      │

Executable
```

Although I couldn't complete the build due to missing CMake installation and an older MinGW compiler, I now understand how the build process should be organized.

---

## Understanding Redis Command Flow

Instead of immediately writing the parser, I spent time understanding how Redis handles commands internally.

Basic execution flow:

```text
User Input

      │

"SET name John"

      │

Command Parser

      │

Command Object

      │

RedisLite::execute()

      │

HashMap
```

Breaking the process into multiple stages makes the implementation much cleaner and easier to extend later.

---

## Command Parser Research

I also researched how command parsing generally works.

Current understanding:

```text
Input String

        │

Split into Tokens

        │

Identify Command

        │

Validate Arguments

        │

Create Command Object

        │

Execute
```

I haven't implemented the parser yet, but I now have a much clearer idea of how to approach it.

---

## Current Architecture

```text
Application

      │

Command Parser

      │

Command Object

      │

RedisLite

      │

HashMap

      │

LinkedList

      │

DynamicArray
```

The project is slowly moving towards a layered architecture where every component has a single responsibility.

---

## Problems Faced

### 1. Choosing a Hashing Strategy

Initially I wasn't sure whether every custom class should have its own completely separate hash algorithm.

After researching different implementations, I understood that combining hashes of individual fields is a much cleaner and reusable approach.

---

### 2. Floating Point Hash Values

The large constants used in the FNV-1a algorithm looked confusing at first.

I compared multiple approaches and found that these constants are specifically chosen to improve bit distribution and reduce collisions.

---

### 3. Understanding Casts

I was confused about why

```cpp
reinterpret_cast
```

is used instead of

```cpp
static_cast
```

After studying both, I realized hashing requires access to the raw memory representation rather than converting the value itself.

---

### 4. CMake Configuration

While setting up the build system, I discovered that CMake wasn't installed on my machine.

I also noticed my MinGW compiler version is quite old, so I'll need to update the development environment before moving further.

---

### 5. Designing the Command Parser

Initially I wanted to directly start coding the parser.

Later I realized understanding the complete command flow first would make the implementation much cleaner.

So I spent time studying the architecture before writing any code.

---

## Concepts Learned Today

* User Defined Hashing
* Default vs Custom Hashers
* Floating Point Hashing
* FNV-1a Algorithm
* Bit Distribution
* `reinterpret_cast`
* Binary Representation of Floats
* Project Folder Organization
* CMake Basics
* Build Configuration
* Command Parsing
* Tokenization
* Layered Project Architecture
* Redis Command Flow

---

## Internal Flow

Hashing Flow:

```text
Float Value

      │

Binary Representation

      │

FNV-1a Hash

      │

Hash Value

      │

Bucket Number
```

Redis Command Flow:

```text
SET name John

        │

Command Parser

        │

Command Object

        │

RedisLite::execute()

        │

HashMap

        │

Stored Successfully
```

---

## Testing Summary

Today's work mainly involved research and project restructuring.

Verified:

* Generic hashing design
* Floating-point hashing logic
* Binary representation handling
* Project folder organization
* CMake project setup
* Overall Redis command execution flow
* Parser design approach

---
