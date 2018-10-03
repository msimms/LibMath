# LibMath
A collection of commonly used math routines, in C, C++, Python, and Rust programming languages.

## Rationale
This is a collection of small, and quick, math routines I've written for other hobby projects over the years. I decided to organize them and place them all in one library so that they would be easier to reuse in the future. They're also available for anyone else that wants to use this code, isntead of a larger, heaveyweight math library.

## Features
This library is primarily focused on C and C++. However, I have started adding Python and Rust implementations where appropriate, or when needed.

### Distance Calculations
* Hamming Distance (C, C++, Rust)
* Levenshtein Distance (C, C++, Rust)
* Basic Euclidian Distances (C, C++, Rust)
* Haversine Distance (C, C++, Rust, Python)

### Linear Algebra
* Basic Matrix Operations - with optimizations for square matrices (C, C++, Rust)
* Basic Vector Operations (C, C++, Rust)

### Statistical Functions
* Mean, Standard Deviation, and Variance (C, C++, Rust)
* Min, Max (C, C++, Rust)

### K-Means
* One dimensional K-Means (C, C++, Rust)

### Peak Finding
* Find peaks that rise more than one standard deviation above the mean for at least three consecutive points on the x axis. (C++)

## Using
Add this project as a submodule to your project and then add the files to your build, or just copy the source files.

## License
This library is released under the MIT license, see LICENSE for details.
