//: C12:Automatic type conversion
// Type conversion constructor
#include <iostream>

class One {
public:
	One() {}
};

class Two {
public:
	// Two(const One&) {
	// 	std::cout<< "class Two's constructor called..." <<std::endl;
	// };
	explicit Two(const One&) {
		std::cout<< "class Two's constructor called..." <<std::endl;
	}; // Prefacing with the keyword explicit,which only works with constructors, to disable the hidden constructor call.
	// So all conversion from class One to class Two must be explicitly rather implicitly.
};

void f(Two) {}

int main(int argc, char const *argv[])
{
	One one;
	// f(one); // exist hidden constructor call	
	f(Two(one));
	return 0;
}