//: C13:NoMemory.cpp
// Constructor isn't called if new fails
#include <iostream>
#include <new> //bad_alloc definition

class NoMemory
{
public:
	NoMemory();
	~NoMemory();
	void* operator new(size_t sz) throw(std::bad_alloc);
};

NoMemory::NoMemory() {
	std::cout<< "NoMemory::NoMemory()" << std::endl;
}

void* NoMemory::operator new(size_t sz) throw(std::bad_alloc) {
	std::cout<< "NoMemory::operator new" <<std::endl;
	throw std::bad_alloc();
}


int main(int argc, char const *argv[])
{
	NoMemory* nm = 0;
	try {
		nm = new NoMemory;
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	std::cout<< "nm = " << nm <<std::endl;
	return 0;
}