#include <iostream>
#include "Integer.h"
#include "../require.h"

Integer::Integer(long ll) : i(ll)
{
	std::cout<< "Constructor called..." <<std::endl;
}

Integer::Integer(const Integer& h) : i(h.i)
{
	std::cout<< "Copy-constructor called..." <<std::endl;	
}

/*const Integer Integer::operator+(const Integer& right)
{
	cout<< "Member overloaded operator+ called..." <<endl;	
	return Integer(i + right.i);
}*/

/*const long Integer::operator<<(const Integer& param)
{
	return param.i;
}*/

const Integer operator+(const Integer& left, 
						const Integer& right)
{
	std::cout<< "Non-member overloaded operator+ called..." <<std::endl;
	// Integer tmp(left.i + right.i);
	// return tmp;	
	return Integer(left.i + right.i);	
}

std::ostream& operator<<(std::ostream& out, const Integer& param)
{
	out<< param.i;
	return out; 
}

std::istream& operator>>(std::istream& in, Integer& param)
{
	in >> param.i;
	return in;
}

Integer::~Integer()
{
	std::cout<< "Destructor called..." <<std::endl;
}