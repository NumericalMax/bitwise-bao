#include <iostream>
#include <chrono>
#include <ctime>

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
        // calculate sign of the result
        bool sign = greater(a, 0) ^ greater(b, 0);
        // if a is larger we iterate over b. if b is larger we iterate over a
        bool larger = greater(absolute(a), absolute(b))
        int result = 0;
        if(sign){
            if(larger){
                for (int k = 0; k < absolute(b); k = add(k, 1)) {
                    result = subtract(result, absolute(a));
                }
            }
            else{
                for (int k = 0; k < absolute(a); k = add(k, 1)) {
                    result = subtract(result, absolute(b));
                }
            }
        }
        else{
            if(larger){
                for (int k = 0; k < absolute(b); k = add(k, 1)) {
                    result = add(result, absolute(a));
                }
            }
            else{
                for (int k = 0; k < absolute(a); k = add(k, 1)) {
                    result = add(result, absolute(b));
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
		if (greater(absolute(b), absolute(a))) { return 0; }
        bool sign = greater(a, 0) ^ greater(b, 0);
		int result = 0;
        if(sign){
            while (greater(absolute(a) + 1, absolute(b))) {
                a = subtract(absolute(a), absolute(b));
                result = subtract(result, 1);
            }
        }
        else{
            while (greater(absolute(a) + 1, absolute(b))) {
                a = subtract(absolute(a), absolute(b));
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
    
    
    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;
    std::cout << "n = ";
    std::cin >> n;
    std::cout << std::endl;
    
    
    // we perform each experiment n times to obtain more stable results
    // SUMMATION
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = basics::add(a,b);
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " + " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    std::cout << "Elapsed time custom: " << elapsed_nanoseconds << " nanoseconds" << std::endl;
    
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = a + b;
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " + " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "Elapsed time builtin: " << elapsed_nanoseconds << " nanoseconds\n" << std::endl;
    
    
    // SUBTRACTION
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = basics::subtract(a,b);
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " - " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    std::cout << "Elapsed time custom: " << elapsed_nanoseconds << " nanoseconds" << std::endl;
    
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = a - b;
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " - " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "Elapsed time builtin: " << elapsed_nanoseconds << " nanoseconds\n" << std::endl;
    
    
    // MULTIPLICATION
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = basics::multiply(a,b);
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " * " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    std::cout << "Elapsed time custom: " << elapsed_nanoseconds << " nanoseconds" << std::endl;
    
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = a * b;
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " * " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "Elapsed time builtin: " << elapsed_nanoseconds << " nanoseconds\n" << std::endl;
    
    
    // DIVISION
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = basics::divide(a,b);
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " / " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    std::cout << "Elapsed time custom: " << elapsed_nanoseconds << " nanoseconds" << std::endl;
    
    start = std::chrono::system_clock::now();
    for(int k = 0; k < n; ++k){
        c = a / b;
    }
    end = std::chrono::system_clock::now();
    std::cout << a << " / " << b << " = " << c << std::endl;
    elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "Elapsed time builtin: " << elapsed_nanoseconds << " nanoseconds\n" << std::endl;
    
    
    return 0;
}
