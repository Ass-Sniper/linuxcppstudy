//: DEMO: GreaterThanN
#include <iostream>
using namespace std;

class gt_n {
	int value;
public:
	gt_n(int val) : value(val) {}
	bool operator()(int n) { return n > value; }
};

// TEST
int main(){
	gt_n f(4);
	cout << f(3) << endl; // cout << f.operator()(3) << endl;
	cout << f(5) << endl; // cout << f.operator()(5) << endl;
} ///:~
