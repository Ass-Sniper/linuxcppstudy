#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	cout << *argv[0] << endl;
	int a = 3;
	float b = 5;
	int c = 6;
	/*Pointer to const*/
	const int* n = NULL; // n is a pointer, it points to const int
	n = &a;	
	//n = &b; // n can't point to non-int type
	//*n = 8; // variable which n points to can't be modified after initlization
	n = &c; // but n can change what it points to again after being initlized
	cout << &a << endl;
	cout << n  << endl;
	cout << *n << endl;	
	int const* m = NULL;// m is an ordinary pointer to an int that happens to be const
	m = &a;
	//m = &b; 
	m = &c;
	cout << m  << endl;
	cout << *m << endl;

	/*const pointer*/
	int* const k = &a;
	//k = &c; // k can't point to another variable after being initlized by using a
	//k = &c; // k can't change what it points to again after being initlized
	cout << "a before being modified : a=" << a  << endl;
	*k = 9;
	cout << "a after being modified : a=" << a <<endl;
	cout << k  << endl;
	cout << *k << endl;

	return 0;
}
