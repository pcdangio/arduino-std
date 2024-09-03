# arduino-std
A Standard Library implementation for use with Arduino.

**Important Notes:**
- This is a work in progress; new features will be continually added. Others are welcome to [contribute new features](#6-contributing).
- Not all Standard Library features are possible on Arduino.
- Many features implemented in this library are reduced and/or slightly modified to fit within the constraints of Arduino.

## Table of Contents
1. [Introduction](#1-introduction) - An overview of this library.
2. [Features](#2-features) - A description of features available in this library.
3. [Installation](#3-installation) - How to install and use this library.
4. [Examples](#4-examples) - How to use this library in your projects.
5. [Documentation](#5-documentation) - How to view the documentation for this library.
6. [Contributing](#6-contributing) - Instructions for contributing to this project.
7. [License](#7-license) - License information for this library.

## 1: Introduction

Currently, Arduino does not support the Standard Library due to various performance constraints of the underlying microcontroller. This library provides a lightweight subset of Standard Library functionality compatible with Arduino. It mirrors the Standard Library interface and functionality as closely as possible, with slight modifications to maintain compatibility and utilize memory efficiently.

## 2: Features

**NOTE: Please check the release page for updates on newly-added features**

- [Containers](#21-containers): Data structures that store and manage collections of objects.
- [Memory](#22-memory): Data structures and functions that provide dynamic memory management.
- [Utility](#23-utility): Utility functions and classes.
- [Definitions](#24-definitions): Type definitions.

### 2.1: Containers

**NOTE: All dynamically-sized containers take a `capacity` at construction, which limit their maximum achievable size to provide better control over usage of Arduino's limited memory.**

- `std::array`: A fixed-size array stored sequentially in memory. Closely follows the Standard Library.

- `std::iterator` and `std::const_iterator`: An iterator pointing to an element in a container. Currently implemented as typedefs over direct pointers to elements in the container. Reverse iterators are not yet implemented.

- `std::map`: An associative container mapping keys and values. Currently implemented as key/value pairs stored contiguously in memory, with linear key searching. Maps are not sorted or implemented as trees, and pairs are ordered based on when they were added to the map. Due to the capacity limitation and lack of exceptions, `std::map::at` and `std::map::operator[]` are not implemented.

- `std::set`: A container of unique values. Currently implemented with values stored contiguously in memory, with linear searching. Values are ordered based on when they were added to the set. Interface closely follows the Standard Library.

- `std::vector`: A dynamically-sized array stored sequentially in memory. Closely follows the Standard Library, with the exception of capacity specification and handling when adding elements to the vector (e.g. `std::vector::push_back` returns a boolean).

### 2.2 Memory

- `std::unique_ptr`: A smart pointer with sole ownership over a managed object. Closely follows the Standard Library.

- `std::shared_ptr`: A smart pointer with shared ownership over a managed object. Closely follows the Standard Library.

### 2.3: Utility

- `std::forward`: Preserves the lvalue/rvalue category for arguments passed to another function. Minimal functional implementation.

- `std::move`: Indicates that an object should be moved. Minimal functional implementation.

- `std::pair`: A pair of heterogeneous objects. Closely follows the Standard Library. `std::make_pair` not yet implemented due to lack of `std::decay`.

### 2.4: Definitions

- `std::size_t`: The type used for sizes and counts of objects in memory.

## 3: Installation

**NOTE: This library is not (yet) available through the Arduino IDE Library Manager.**

To install this library, you simply need to clone this repository to your `Arduino/Libraries` directory. When cloning, please name the directory as `std`.

```bash
# Using http:
git clone https://github.com/pcdangio/arduino-std.git <USER_DIRECTORY>/Arduino/Libraries/std

# OR:

# Using ssh:
git clone git@github.com:pcdangio/arduino-std.git <USER_DIRECTORY>/Arduino/Libraries/std
```

## 4: Examples

The following snippet provides a simple example of how to use this library. Please refer to the [documentation](#5-documentation) for full descriptions of this library's features.

```cpp
#include <std.hpp>

// Create an int vector with a maximum capacity of 10 elements.
std::vector<int> my_vector(10);

// Create a counter.
int i = 0;

void setup()
{
  // Wait 1000ms before starting program.
  delay(1000);

  // Initialize serial.
  Serial.begin(115200);
}

void loop()
{
  // Add current value of counter to the vector.
  bool success = my_vector.push_back(i);

  // Print result of the push_back operation.
  if(success)
  {
    Serial.print("Added ");
  }
  else
  {
    Serial.print("Failed to add ");
  }
  Serial.print(i);
  Serial.print(" to my_vector (size = ");
  Serial.print(my_vector.size());
  Serial.print(", capacity = ");
  Serial.println(my_vector.capacity());

  // Increment counter.
  i++;

  // Delay loop.
  delay(1000);
}
```

## 5: Documentation

This project uses [doxygen](https://www.doxygen.nl/) for generating documentation. A `doxyfile` is included in the project root directory for automatic generation:

```bash
# Navigate to the std library directory.
cd <USER_DIRECTORY>/Arduino/Libraries/std

# Using doxygen cli:
doxygen doxyfile

# HTML documentation is built in std/doc.
```

## 6: Contributing

The Standard Library is very large, so contribution is both welcomed and greatly appreciated. There are a few rules to help make contribution easy while maintaining a clean codebase/repository:

1. Make changes to a forked version of this repository, and submit a new pull request with suitable information about the changes.
2. Use the gitflow model for branch naming (e.g. `feature/string`)
3. Pull requests should merge into the `develop` branch.
4. Please follow the same style (e.g. coding case, naming conventions, organization, etc.) as what's currently in the repository.
5. Implement unit tests with AUnit under the `test` directory to prove the features/changes work.
6. Document the code with doxygen, and provide suitable comments within the code itself.
7. Document new/changed features in the [Features](#2-features) section of this README.

**NOTE: I may request changes in your PRs that must be fixed before I merge them. Please understand this is just to maintain the quality of the codebase/repository.**

## 7: License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.