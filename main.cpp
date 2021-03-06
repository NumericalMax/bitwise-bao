#include <iostream>
#include <stdexcept>
#include <chrono>
#include <ctime>

/**
 main.cpp
 Purpose: Calculates basic mathematical operation using solely bitwise operators
 
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
        // calculate sign of the result
        bool sign = greater(a, 0) ^ greater(b, 0);
        // if a is larger we iterate over b. if b is larger we iterate over a
        bool larger = greater(absolute(a), absolute(b));
        int result = 0;
        a = absolute(a);
        b = absolute(b);
        if(sign){
            if(larger){
                for (int k = 0; k < b; k = add(k, 1)) {
                    result = subtract(result, a);
                }
            }
            else{
                for (int k = 0; k < a; k = add(k, 1)) {
                    result = subtract(result, b);
                }
            }
        }
        else{
            if(larger){
                for (int k = 0; k < b; k = add(k, 1)) {
                    result = add(result, a);
                }
            }
            else{
                for (int k = 0; k < a; k = add(k, 1)) {
                    result = add(result, b);
                }
            }
        }
        return result;
     }
    
    /**
     Multiplies two numbers and returns the result / recursive Version
     
     @param first and second mulitplicator as integer
     @return a * b
     */
    int multiply_recursive(int a, int b){
        if (b == 0 || a == 0) { return 0; }
        if(greater(b, 0)){
            return (add(a, multiply(a, subtract(b, 1))));
        }else{
            return subtract(0, multiply(a, subtract(0, b)));
        }
        if(greater(a, 0)){
            return (add(b, multiply(b, subtract(a, 1))));
        }else{
            return subtract(0, multiply(b, subtract(0, a)));
        }
    }
    
    /**
     Divides two numbers and returns the result
     
     @param Dividend and divisor as integer
     @return The result of a / b without rest
    */
	int divide(int a, int b) {
        if (b == 0) { throw std::invalid_argument( "You cannot divide by zero!" ); }
		if (greater(absolute(b), absolute(a))) { return 0; }
        // calculate sign of the result
        bool sign = greater(a, 0) ^ greater(b, 0);
        b = absolute(b);
        a = absolute(a);
		int result = 0;
        if(sign){
            // we have to add 1 since it is a strict greater not a greater equal
            while (greater(a + 1, b)) {
                a = subtract(a, b);
                result = subtract(result, 1);
            }
        }
        else{
            while (greater(a + 1, b)) {
                a = subtract(a, b);
                result = add(result, 1);
            }
        }
		return result;
	}
}


int main(int argc, char** argv){
    
    int a, b, c, n, elapsed_nanoseconds;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::time_t end_time;
    
    // first number
    std::cout << "a = ";
    std::cin >> a;
    // second number
    std::cout << "b = ";
    std::cin >> b;
    // we perform each experiment n times to obtain more stable results
    std::cout << "n = ";
    std::cin >> n;
    std::cout << std::endl;
    
    
    // SUMMATION
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = basics::add(a,b);
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " + " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Elapsed time custom: " << elapsed_nanoseconds << " nanoseconds" << std::endl;
    
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = a + b;
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " + " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Elapsed time builtin: " << elapsed_nanoseconds << " nanoseconds\n" << std::endl;
    
    
    // SUBTRACTION
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = basics::subtract(a,b);
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " - " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Elapsed time custom: " << elapsed_nanoseconds << " nanoseconds" << std::endl;
    
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = a - b;
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " - " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Elapsed time builtin: " << elapsed_nanoseconds << " nanoseconds\n" << std::endl;
    
    
    // MULTIPLICATION
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = basics::multiply(a,b);
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " * " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Elapsed time custom: " << elapsed_nanoseconds << " nanoseconds" << std::endl;
    
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = a * b;
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " * " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Elapsed time builtin: " << elapsed_nanoseconds << " nanoseconds\n" << std::endl;
    
    
    // DIVISION
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = basics::divide(a,b);
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " / " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Elapsed time custom: " << elapsed_nanoseconds << " nanoseconds" << std::endl;
    
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = a / b;
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " / " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Elapsed time builtin: " << elapsed_nanoseconds << " nanoseconds\n" << std::endl;
    
    
    return 0;
}
