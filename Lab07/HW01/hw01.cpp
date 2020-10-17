#include <fstream>
#include <iostream>
#include <string>

class AnyString {
	std::string anyString;

public:
	AnyString(const std::string& anyString) : anyString(anyString) {}	// anyString 초기화
	std::string getAnyString() {
		return "Stored String :: " + anyString;
	}
	//함수 선언
	friend std::ostream& operator<<(std::ostream& os,  AnyString& a);
};


int main() {
	std::ofstream out("testOveroding.txt");
	AnyString a("Hello, this is operator overloading test!!!");
	//std::string output = a.getAnyString();
	//out<< output << std::endl;
	out << a << std::endl;

	return 0;
}

//함수 구현
std::ostream& operator<<(std::ostream& os,  AnyString& a)
{
	os << a.getAnyString();
	return os;
}
