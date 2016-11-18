#include <iostream>
#include <vector>
#include <time.h>
// #include <algorithm>
// #include <iterator>

// int main(int argc, char const *argv[])
// {
// 	std::vector<double> v;
// 	int nDims = 3;
// 	double coords[nDims];
// 	*coords = 1.0;
// 	*(coords + 1) = 2.0;
// 	*(coords + 2) = 3.0;
// 	copy(coords, coords + nDims, back_inserter(v));
// 	for (std::vector<double>::iterator i = v.begin(); i != v.end(); ++i)
// 	{
// 		std::cout << *i << "\t";
// 	}
// 	std::cout << "\n";
// 	return 0;
// }

using namespace std;

// typedef unsigned int uint;

/*struct empty_struct {
		
};

class empty_class {

};

//大小为0之独立（非附属）对象，通常C++官方勒令默默安插一个char到空对象内
class int_and_empty {
	int x;
	empty_class ec;
};

//前面一直在强调“独立（非附属）”对象的大小一定不为0，这个约束不适用于derived class对象内的base class成分，因为它们并非独立（非附属）
class int_derived_empty {
	int x;
};

class empty_derived_empty {

};*/


class Empty
{};
 
class Derived1 : public Empty
{};
 
class Derived2 : virtual public Empty
{};
 
class Derived3 : public Empty
{    
    char c;
};
 
class Derived4 : virtual public Empty
{
    char c;
};

class Derived5 : virtual public Empty
{
    int c;
};
 
class Dummy
{
    char c;
};


int main(int argc, char const *argv[])
{

/*	cout<< "sizeof('a')  = " << sizeof('a') << endl;  // 32-bit: 1;
	cout<< "sizeof(char) = " << sizeof(char) << endl; // 32-bit: 1;
	cout<< "sizeof(int)  = " << sizeof(int) << endl;  // 32-bit: 4;

	cout<< "sizeof(struct empty_struct) = " << sizeof(empty_struct) <<endl;	// 1
	cout<< "sizeof(class  empty_class)  = " << sizeof(empty_class) <<endl;	// 1
	cout<< "sizeof(class  int_and_empty)  = " << sizeof(int_and_empty) <<endl;	// 8
	cout<< "sizeof(class  int_derived_empty)  = " << sizeof(int_derived_empty) <<endl;	// 4
	cout<< "sizeof(class  empty_derived_empty)  = " << sizeof(empty_derived_empty) <<endl;	// 1*/

    cout << "sizeof(Empty) " << sizeof(Empty) << endl;		// 1
    cout << "sizeof(Derived1) " << sizeof(Derived1) << endl;// 1
    cout << "sizeof(Derived2) " << sizeof(Derived2) << endl;// 4 = vptr
    cout << "sizeof(Derived3) " << sizeof(Derived3) << endl;// 1
    cout << "sizeof(Derived4) " << sizeof(Derived4) << endl;// 8 = vptr + memory_align
    cout << "sizeof(Derived5) " << sizeof(Derived5) << endl;// 8   
    cout << "sizeof(Dummy) " << sizeof(Dummy) << endl;		// 1

	return 0;
}
