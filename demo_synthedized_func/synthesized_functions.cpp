//: C14:synthesized_functions.cpp
// Functions that don't automatically inherit (1:constructor, 2:destructor, 3:operator=) 
// are syhthesized by the compiler
#include <iostream>

class GameBoard {
public:
	GameBoard() { std::cout<< "GameBoard()\n"; }
	GameBoard(const GameBoard&) { 
		std::cout<< "GameBoard(const GameBoard&)\n";
	}
	GameBoard& operator=(const GameBoard&) {  
		std::cout<< "GameBoard& operator=(const GameBoard&)\n";
		return *this;		
	}
	~GameBoard() { std::cout<< "~GameBoard()\n"; }
	
};

class Game {
	GameBoard gb; //Composition
public:
	//Default GameBoard constructor called
	Game() { std::cout<< "Game()\n"; }
	//Explicitly call the GameBoard copy-constructor or the GameBoard default constructor is auto-called instead
	Game(const Game& g): gb(g.gb) { std::cout<< "Game(const Game&)\n"; }
	Game(int) { std::cout<< "Game(int)\n"; }
	Game& operator=(const Game& g) {
		//Explicitly call the GameBoard assignment operator function or no assignment at all happens for gb !
		gb = g.gb;
		std::cout<< "Game& operator=(const Game& g)\n";
		return *this;
	}
	//Nested class
	class Other {};
	//Automatic type conversion
	operator Other() const {
		std::cout << "Automatic type conversion function: Game::operator Other() const\n";
		return Other();
	}
	~Game() { std::cout<< "~Game()\n"; }	
};

class Chess: public Game {};

void f(Game::Other) {}

class Checkers: public Game {
public:
	//Default base-class constructor called
	Checkers() { std::cout<< "Checkers()\n"; }
	Checkers(const Checkers& c): Game(c) {
		std::cout<< "Checkers(const Checkers& c)\n";
	}
	Checkers& operator=(const Checkers& c) {
		//Explicitly call the base-class oprtator=() function or no base-class assignment will happen
		Game::operator=(c);
		std::cout<< "Checkers::operator=(const Checkers& c)\n";
		return *this;
	} 
	~Checkers() { std::cout<< "~Checkers()\n"; };	
};

int main(int argc, char const *argv[])
{
	Chess cs1;
	Chess cs2(cs1);
	// Chess ch3(1); //Error:no int construtor
	cs1 = cs2; //operator= synthesized
	f(cs1); //type conversion is inherited
	// Game::Other go;
	// cs1 = go; //operator= not synthesized for differing types,but only synthesized for assigning objects of the same type
	Checkers ck1, ck2(ck1);
	ck1 = ck2;
	return 0;
} ///:~