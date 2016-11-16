//: C12:OperatorOverloadingConversion.cpp
#include <iostream>

class Three {
public:
	Three(int ii = 0, int i = 0): i(ii) {
		std::cout<< "class Three's constructor called..." <<std::endl;
	} 
private:
	int i;
};

class Four {
public:
	Four(int xx): x(xx) {
		std::cout<< "class Four's constructor called..." <<std::endl;		
	}
	// The return type is the name of the operator you're overloading
	operator Three() const {
		std::cout<< "class Four's operator overloading function called..." <<std::endl;
		return Three(x); 
	}
private:
	int x;
};

void g(Three) {}

int main(int argc, char const *argv[])
{
	Four four(1);
	g(four); // Calls class Four's operator overloading function
	// g(1); // Only calls Three(1, 0)
	return 0;
}