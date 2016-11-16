#include <iostream>
#include "Integer.h"
using namespace std;

int main(int argc, char const *argv[])
{
	Integer a(3);
	Integer b(5);
	Integer c;
    cout<<"a+b= "<< a+b <<endl;
    cout<<"Please enter an integer: ";
    cin>>c;
    cout<<"c= "<<c<<endl;
	return 0;
}
