#include <iostream>

namespace basics {
	int add(int a, int b) {
		if (b == 0) { return a; }
		int temp = a ^ b;
		b = (a & b) << 1;
		a = temp;
		return add(a, b);
	}
	int subtract(int a, int b) {
		a = add(a, ~b + 1);
		return a;
	}
	bool positive(int x) { return !((x & 0x80000000) >> 31 | !x); }
	bool greater(int a, int b) {
		if (positive(subtract(a, b))) { return true; }
		else { return false; }
	}
	int multiply(int a, int b) {
		if (b == 0 || a == 0) { return 0; }
		int result = 0;
		if (greater(a, b)) {
			for (int k = 0; k < b; k = add(k, 1)) {
				result = add(result, a);
			}
			return result;
		}
		for (int k = 0; k < a; k = add(k, 1)) {
			result = add(result, b);
		}
		return result;
	}
	int divide(int a, int b) {
		if (greater(b, a)) { return 0; }
		int result = 0;
		while (greater(a, 0)) {
			a = subtract(a, b);
			result = add(result, 1);
		}
		return result;
	}
}

int main(){
	int a = 27;
	int b = 3;
	std::cout << a << " + " << b << " = " << basics::add(a,b) << std::endl;
	std::cout << a << " - " << b << " = " << basics::subtract(a, b) << std::endl;
	std::cout << a << " * " << b << " = " << basics::multiply(a, b) << std::endl;
	std::cout << a << " / " << b << " = " << basics::divide(a, b) << std::endl;
	std::cout << a << " > " << b << " = " << basics::greater(a, b) << std::endl;
	std::cin >> a;
    return 0;
}