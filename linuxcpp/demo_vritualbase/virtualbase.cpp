//~C09 virtualbase.cpp
#include <iostream>
using namespace std;

/*class Top {
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
};*/

/*-----------------------------------------------*/
/*
class A {
public:
	int a;
	virtual ~A() {};
	virtual void f() { cout << "A::f()\n"; }
};

class B: virtual public A {
public:
	int b;
	void f() { cout << "B::f()\n"; }
};

class C: public B {
public:
	int c;
//void f() { cout << "C::f()\n"; }	 	//if comment was removed, then output will become C::f()
};

class D: public C, virtual public A {
public:
	int d;
};*/



//--------------------------
// base class has virtual function
// common inheritance
class A {
public:
	char a;
	virtual void f() {};
};

class B: public A {
public:
	int b;
	virtual void m() {};
};
//--------------------------
// base class has no virtual function
// virtual inheritance
class C {
public:
	int c;
	void f() {};
};

class D: virtual public C {
public:
	int d;
	virtual void m() {};
};
//--------------------------
// base class has virtual function
// virtual inheritance
class E {
public:
	int e;
	virtual void f() {};
};

class F: virtual public E{
public:
	int f;
	virtual void m() {};
};

int main(int argc, char const *argv[])
{
	// test for showing virtual inheritance class object's memory layout
/*	Bottom b(1,2,3,4);
	cout << "sizeof(Top):" << sizeof(Top) << ";\nsizeof(Left):" << sizeof(Left)
		 << ";\nsizeof(Right):" << sizeof(Right) << ";\nsizeof(Bottom):" << sizeof(b) << endl;
	cout << b << endl;
	cout << "address of Bottom object:" << static_cast<void*>(&b) << endl;
	Top *p = static_cast<Top*>(&b);
	cout << *p << endl;
	cout << static_cast<void*>(p) << endl;
	cout << dynamic_cast<void*>(p) << endl;

	cout << *((Bottom *)&b) << endl;
	cout << *((Right *)&b) << endl;	
	cout << *((Left *)&b) << endl;
	cout << *((Top *)&b) << endl;	*/	

	// test virtual inheritance class's virtual function execution sequence
/*	B *p = new D;
	p->f();
	delete p;*/

/*	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;
	cout << sizeof(D) << endl;*/

	// test virtual inheritance class object's size
	B b;
	D d;
	F f;
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;
	cout << sizeof(D) << endl;
	cout << sizeof(E) << endl;
	cout << sizeof(F) << endl;

	/*
		sizeof(A) = 8
		sizeof(B) = 12
		sizeof(C) = 4
		sizeof(D) = 12
		sizeof(E) = 8
		sizeof(F) = 16

		Breakpoint 1, main (argc=1, argv=0xbfffeef4) at virtualbase.cpp:150
		150		cout << sizeof(F) << endl;
		(gdb) p *((A *)&b)
		$1 = {_vptr.A = 0x8048ab8 <vtable for B+8>, a = -14 '\362'}
		(gdb) p *((B *)&b)
		$2 = {<A> = {_vptr.A = 0x8048ab8 <vtable for B+8>, a = -14 '\362'}, b = 1}
		(gdb) p *((C *)&d)
		$3 = {c = -1210772307}
		(gdb) p *((D *)&d)
		$4 = {<C> = {c = -1210772307}, _vptr.D = 0x8048aa4 <vtable for D+12>, d = -1073746180}
		(gdb) p *((E *)&f)
		$5 = {_vptr.E = 0x8048a7c <vtable for F+28>, e = -1209233408}
		(gdb) p *((F *)&f)
		$6 = {<E> = {_vptr.E = 0x8048a7c <vtable for F+28>, e = -1209233408}, _vptr.F = 0x8048a6c <vtable for F+12>, 
		  f = -1207963648}
		(gdb) p ((A *)&b)
		$8 = (A *) 0xbfffee28
		(gdb) x/x 0xbfffee28
		0xbfffee28:	0x08048ab8  <== vptr.A = 0x8048ab8 <vtable for B+8>
	*/

	return 0;
}