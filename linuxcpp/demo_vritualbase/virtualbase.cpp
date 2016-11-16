//~C09 virtualbase.cpp
#include <iostream>
using namespace std;

class Top {
protected:
	int x;
public:
	Top(int n) { x = n; }
	virtual ~Top() {}
	friend ostream& operator<<(ostream &os, const Top &t) {
		return os << t.x;
	}
};


class Left: virtual public Top {
protected:
	int y;
public:
	Left(int m, int n): Top(m) { y = n; }	
};


class Right: virtual public Top {
protected:
	int z;
public:
	Right(int u, int v): Top(u) { z = v; }
};


class Bottom: public Left, public Right {
	int w;
public:
	Bottom(int i, int j, int k, int m): Top(i), Left(0, j), Right(0, k) { w = m;}
	friend ostream& operator<<(ostream &os, const Bottom &b) {
		return os << b.x << "," << b.y << "," << b.z << "," << b.w;
	}
};

int main(int argc, char const *argv[])
{
	Bottom b(1,2,3,4);
	cout << "sizeof(Top):" << sizeof(Top) << ";sizeof(Left):" << sizeof(Left)
		 << ";sizeof(Right):" << sizeof(Right) << ";sizeof(Bottom):" << sizeof(b) << endl;
	cout << b << endl;
	cout << static_cast<void*>(&b) << endl;
	Top *p = static_cast<Top*>(&b);
	cout << *p << endl;
	cout << static_cast<void*>(p) << endl;
	cout << dynamic_cast<void*>(p) << endl;	
	return 0;
}