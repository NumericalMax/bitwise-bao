# Basic arithmetic operations (bao) implemented with bitwise operators
This is an implementation of basic arithmetic functions (e.g. plus, minus) in C++ in which only bitwise operators are allowed. It is solely designed for the datatype integer.

# +
Summation of two integers a and b: a + b

# -
Subtraction of two integers a and b: a - b

# *
Multiplication of two integers a and b: a * b

# /
Division of two integers a and b without rest: a / b

# How to execute in the terminal:

```
git clone https://github.com/NumericalMax/bitwise-bao.git
cd bitwise-bao
g++ main.cpp -o main
./main
```
The program will ask you for three parameters:
1. a = First Number
2. b = Second Number
3. n = Number of computations performed for each basic algorithmic operation. You can set this parameter to 1, unless you want to perform time measurement. In the latter case large n will result in more stable time measurements.
