#include <iostream>
#include <vector>

typedef unsigned int uint;

class Subject;

class Observer
{
public:
	virtual ~Observer() {};
	virtual void update(Subject *observee) = 0;

};

class Subject
{
public:
	virtual ~Subject() {};
	// Add obs to the set of observers
	virtual void addOberver(Observer *obs)
	{
		observers.push_back(obs);
	}
	// Remove obs from the set of observers
	virtual void removeObserver(Observer *obs)
	{
		for (uint i = 0; i < observers.size(); ++i)
		{
			if (observers[i] == obs) {
				observers[i] = observers.back();
				observers.pop_back();
				i--;
			}
		}
	}
	// Call the update method for all observers
	virtual void notifyAll()
	{
		for (uint i = 0; i < observers.size(); ++i)
		{
			observers[i]->update(this);
		}
	}

private:
	std::vector<Observer *> observers;
};

class Timer: public Subject
{
public:
	void tick()
	{
		notifyAll();
	}

};

class Echo: public Observer
{
public:
	Echo(uint id, Timer *t): myId(id), observee(t)
	{
		observee->addOberver(this);
	}
	~Echo()
	{
		observee->removeObserver(this);
	}
	virtual void update(Subject *s)
	{
		using std::cout;
		using std::endl;
		if (observee == s)
		{
			cout << myId << endl;
		}
	}

private:
	uint myId;
	Subject *observee; // subject observed
};


void testEcho12(Timer & t)
{
	using std::cout;
	using std::endl;
	Echo e1(1, &t);
	Echo e2(2, &t);

	cout << "Expectin1g 1 and 2 to respond." << endl;
	t.tick( );
	cout << "1 and 2 disappear." << endl;
}

int main()
{
	using std::cout;
	using std::endl;
	Timer t;
	Timer other;

	testEcho12(t);   // 1 and 2 should respond

	Echo e3(3, &t);
	Echo e4(4, &t);
	Echo e5(5, &other);  // registered with other, not t

	cout << "Only 3 and 4 are currently observable." << endl;
	cout << "Expecting 3 and 4 to respond." << endl;
	t.tick();

	return 0;
}
