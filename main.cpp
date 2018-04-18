#include <iostream>

/**
 main.cpp
 Purpose: Calculates basic mathematical operation using solely binary operators
 
 @author Max Kapsecker
 @version 1.0 18/04/18
*/

namespace basics {
    
    /**
     Checks if a number is positive
     
     @param An integer number (32 bit)
     @return A boolean whether the input number is positive
     */
    bool positive(int x) { return !((x & 0x80000000) >> 31 | !x); }
    
    /**
     Computes the absolute value of an signed integer
     
     @param A signed integer number (32 bit)
     @return The absolute value of the input number
     */
    int absolute(int x){ return (x >> 31 ^ x) - (x >> 31); }
    
    /**
     Adds two numbers and returns the sum
     
     @param First and second summand as integer
     @return The sum of the two input numbers
     */
	int add(int a, int b) {
		if (b == 0) { return a; }
		int temp = a ^ b;
		b = (a & b) << 1;
		a = temp;
		return add(a, b);
	}
    
    /**
     Subtracts two numbers and returns the signed difference
     
     @param Minuend and subtrahend as integer
     @return The signed difference of the two input numbers
     */
	int subtract(int a, int b) {
		a = add(a, ~b + 1);
		return a;
	}

    /**
     Determines whether one number is larger than the other
     
     @param two numbers as integer
     @return Boolean, whether the first number is larger than the second
     */
	bool greater(int a, int b) {
		if (positive(subtract(a, b))) { return true; }
		else { return false; }
	}
    
    /**
     Multiplies two numbers and returns the result
     
     @param first and second mulitplicator as integer
     @return a * b
     */
	int multiply(int a, int b) {
		if (b == 0 || a == 0) { return 0; }
        bool sign = greater(a, 0) ^ greater(b, 0);
		int result = 0;
        // TODO: Ask whether a or b is larger. Use the smaller for upper iteration range
        if(sign){
            for (int k = 0; k < absolute(b); k = add(k, 1)) {
                result = subtract(result, absolute(a));
            }
        }
        else{
            for (int k = 0; k < absolute(b); k = add(k, 1)) {
                result = add(result, absolute(a));
            }
        }
        return result;
	}
    
    /**
     Divides two numbers and returns the result
     
     @param Dividend and divisor as integer
     @return The result of a / b without rest
     */
	int divide(int a, int b) {
		if (greater(absolute(b), absolute(a))) { return 0; }
        bool sign = greater(a, 0) ^ greater(b, 0);
		int result = 0;
        if(sign){
            while (greater(a, 0)) {
                a = subtract(absolute(a), absolute(b));
                result = subtract(result, 1);
            }
        }
        else{
            while (greater(a, 0)) {
                a = subtract(absolute(a), absolute(b));
                result = add(result, 1);
            }
        }
		return result;
	}
}

int main(int argc, char** argv){
    int a, b;
    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;
    
	std::cout << a << " + " << b << " = " << basics::add(a,b) << std::endl;
	std::cout << a << " - " << b << " = " << basics::subtract(a, b) << std::endl;
	std::cout << a << " * " << b << " = " << basics::multiply(a, b) << std::endl;
	std::cout << a << " / " << b << " = " << basics::divide(a, b) << std::endl;
	std::cout << a << " > " << b << " = " << basics::greater(a, b) << std::endl;
    return 0;
}
