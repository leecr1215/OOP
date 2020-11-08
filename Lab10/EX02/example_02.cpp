#include <iostream>
#include <string>
#include <cassert>
/*ex01과 다르게 dynamic_cast 씀. 오류 발생*/
class Base {
	std::string s;

public:
	Base() : s("Base") { std::cout << "Base class constructor" << std::endl; }

	void what() { std::cout << s << std::endl; }
};

class Derived : public Base {
	std::string s;

public:
	Derived() : s("Derived"), Base() { std::cout << "Derived class constructor" << std::endl; }

	void what() { std::cout << s << std::endl; }
};
int main() {

	Base p;
	Derived c;

	std::cout << " === Pointer ===" << std::endl;
	Base* xx = &c;//OK.upcast
	Derived* yy = dynamic_cast<Derived*>(xx);
	yy->what();

	getchar();
	return 0;
}