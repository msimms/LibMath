[![asm_x86-64](https://img.shields.io/badge/asm-x86_64-brightgreen.svg)]() [![C](https://img.shields.io/badge/c-brightgreen.svg)]() [![C++](https://img.shields.io/badge/cpp-brightgreen.svg)]() [![Rust](https://img.shields.io/badge/rust-brightgreen.svg)](https://www.rust-lang.org) [![Python 2.7|3.7](https://img.shields.io/badge/python-2.7%2F3.7-brightgreen.svg)](https://www.python.org/) [![MIT license](http://img.shields.io/badge/license-MIT-brightgreen.svg)](http://opensource.org/licenses/MIT)

# LibMath
A collection of commonly used math routines, in C, C++, Python, Rust, and Julia programming languages.

## Rationale
This is a collection of small, and quick, math routines I've written for other hobby projects over the years. I decided to organize them and place them in one library so they would be easier to reuse in the future. They're also available for anyone else that wants to use this code, instead of a larger, heaveyweight math library. **There are no production project files in this library. It is just a loose collection of code. Include the files you need and ignore the ones you don't.** The project files and main files are included just for testing.

## Features
This library is primarily focused on C and C++. However, I have started adding Python and Rust implementations where appropriate, or when needed. As python already has a large collection of libraries, there simply isn't as much need for python implementations for many of these algorithms.

### Distance Calculations
* Hamming Distance (C, C++, Rust, Python, Julia)
* Levenshtein Distance (C, C++, Rust, Julia)
* Basic Euclidian Distances (C, C++, Rust, Python, Julia)
* Haversine Distance (C, C++, Rust, Python) - Distance between points on the Earth's surface.

### Graphics
* Quadratic Bezier Curve (C++)

### Linear Algebra
* Basic Matrix Operations - with optimizations for square matrices (C, C++, Rust)
* Basic Vector Operations (C, C++, Rust)

### Statistical Functions
* Mean, Standard Deviation, and Variance (C, C++, Rust, Python2 - unnecesary in Python3)
* Min, Max (C, C++, Rust)

### Signals Functions
* Simple Signal Smoothing (C, C++, Python, Julia)

### K-Means
* One dimensional K-Means (C, C++, Rust, Python)

### Peak Finding
* Find peaks that rise more than one standard deviation above the mean for at least three consecutive points on the x axis. (C++, Rust, Python)

### Power
* Find the nearest power of two (C, C++, Julia)

### Graphics
* Ray Casting (Python, Rust) - Determines if a point is within a polygon.

## Using
Add this respository as a submodule to your own project and then add the file you want directly to your build, or just copy the source files directly into your project. This library is just meant to be a loose collection of files that you can do whatever you want with. This way you don't have to add code for algorithms you don't need to your project.

## License
This library is released under the MIT license, see LICENSE for details.
