#include <iostream>
using namespace std;

class Animal {
public:
	virtual void bark() = 0;
	virtual int NumOfLeg() = 0;
};

class Dog : public Animal {
public:
	virtual int GetSpeed() = 0;
	virtual Dog& operator>(Dog& d) = 0;

	void bark() override {
		cout << "왈왈";
	}
	int NumOfLeg() override {
		return 4;
	}

};

class Bird : public Animal {
public:
	virtual int GetSize() = 0;
	virtual Bird& operator>(Bird& b) = 0;

	void bark() override {
		cout << "짹짹";
	}
	int NumOfLeg() override {
		return 2;
	}

};

class Retriver : public Dog {
public:
	Retriver(int speed, string name) {
		this->speed = speed;
		this->name = name;
	}
	int GetSpeed() {
		return this->speed;
	}
	string GetName() {
		return name;
	}
	Dog& operator>(Dog& d) {
		if (this->GetSpeed() > d.GetSpeed()) {
			return *this;
		}
		else {
			return d;
		}
	}

private:
	int speed;
	string name;
};

class Poodle : public Dog {
public:
	Poodle(int speed, string name) {
		this->speed = speed;
		this->name = name;
	}
	int GetSpeed() {
		return this->speed;
	}
	string GetName() {
		return name;
	}
	Dog& operator>(Dog& d) {
		if (this->GetSpeed() > d.GetSpeed()) {
			return *this;
		}
		else {
			return d;
		}
	}

private:
	int speed;
	string name;
};

class Pomerania : public Dog {
public:
	Pomerania(int speed, string name) {
		this->speed = speed;
		this->name = name;
	}
	int GetSpeed() {
		return this->speed;
	}
	string GetName() {
		return name;
	}
	Dog& operator>(Dog& d) {
		if (this->GetSpeed() > d.GetSpeed()) {
			return *this;
		}
		else {
			return d;
		}
	}
private:
	int speed;
	string name;
};

class Parrot : public Bird {
public:
	Parrot(int size, string name) {
		this->size = size;
		this->name = name;
	}

	int GetSize(){
		return this->size;
	}

	Bird& operator>(Bird& b){
		if (this->GetSize() > b.GetSize()) {
			return *this;
		}
		else {
			return b;
		}
	}

private:
	int size;
	string name;
};

class Duck : public Bird {
public:
	Duck(int size, string name) {
		this->size = size;
		this->name = name;
	}

	int GetSize(){
		return this->size;
	}

	Bird& operator>(Bird& b){
		if (this->GetSize() > b.GetSize()) {
			return *this;
		}
		else {
			return b;
		}
	}

private:
	int size;
	string name;
};

class Chick : public Bird {
public:
	Chick(int size, string name) {
		this->size = size;
		this->name = name;
	}

	int GetSize(){
		return this->size;
	}

	Bird& operator>(Bird& b){
		if (this->GetSize() > b.GetSize()) {
			return *this;
		}
		else {
			return b;
		}
	}

private:
	int size;
	string name;
};

int main(void) {
	Retriver re(15, "리트리버");
	Dog* retriver = &re;

	Poodle po(7, "푸들");
	Dog* poodle = &po;

	Pomerania pom(9, "포메라니언");
	Dog* pomerania = &pom;

	Dog* fast = &poodle->operator>(*retriver);
	fast = &pomerania->operator>(*fast);

	cout << "빠른 강아지의 속도: " <<fast->GetSpeed() << "\n";

	Parrot pa(10, "앵무새");
	Bird* parrot = &pa;

	Duck du(30, "오리");
	Bird* duck = &du;

	Chick ch(5, "병아리");
	Bird* chick = &ch;

	Bird* big = &(&parrot->operator>(*duck))->operator>(*chick);
	cout << "가장큰새의 크기: " << big->GetSize();


}

//Animal 클래스 만들기    xxxx
//Dog 클래스 만들기       xxxx
//
//Bird 클래스 만들기		xxxx
//
//Dog123 클래스 만들기		xxxx
//
//Bird123 클래스만들기	    xxxx
//
//실행 오류 점검

