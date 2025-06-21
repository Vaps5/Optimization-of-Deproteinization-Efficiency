# Optimization-of-Deproteinization-Efficiency
This repository contains the implementation of the algorithms in C++ programming language used for the analysis developed in the paper “Optimization of Deproteinization Efficiency in Chitin Hydrolysis using Sodium Hydroxide”. The algorithms model and optimize the deproteinization efficiency in chitin hydrolysis using sodium hydroxide (NaOH), based on a literature review of ten distincts scientific experiments. The project uses **Least Squares Fitting**, **Exhaustive Search**, and a **Beam Search** methos to find the optimal NaOH molarity, temperature, and processing time for chitin hydrolysis.

## 📘 Project Structure
# LeastSquares.cpp
Least Squares fitting for finding undteermined coefficients of the function that models the problem. This algorithm uses Gaussian Elimination method with partial pivoting.  
# BeamSearch.cpp
Machine learning technique for optimizing the modeling. 
# ExhaustiveSearch.cpp
Exhaustive Search solution for optimizing the modeling. The algorithm searches the optimum points by increasing all variables by 0.01 units for better precision.

### Prerequisites

- [VS Code](https://code.visualstudio.com/)
- C++ compiler (e.g., `g++`, `clang++`)
- CMake (optional, for build configuration)
- GNU Make (if using Makefile)

### Build Instructions

You can compile the file with the g++ command:

make LeastSquares

Once the program is compiled, you can run it by entering the name of the file.
