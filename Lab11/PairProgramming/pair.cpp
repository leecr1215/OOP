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
		cout << "�п�";
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
		cout << "±±";
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
	Retriver re(15, "��Ʈ����");
	Dog* retriver = &re;

	Poodle po(7, "Ǫ��");
	Dog* poodle = &po;

	Pomerania pom(9, "���޶�Ͼ�");
	Dog* pomerania = &pom;

	Dog* fast = &poodle->operator>(*retriver);
	fast = &pomerania->operator>(*fast);

	cout << "���� �������� �ӵ�: " <<fast->GetSpeed() << "\n";

	Parrot pa(10, "�޹���");
	Bird* parrot = &pa;

	Duck du(30, "����");
	Bird* duck = &du;

	Chick ch(5, "���Ƹ�");
	Bird* chick = &ch;

	Bird* big = &(&parrot->operator>(*duck))->operator>(*chick);
	cout << "����ū���� ũ��: " << big->GetSize();


}

//Animal Ŭ���� �����    xxxx
//Dog Ŭ���� �����       xxxx
//
//Bird Ŭ���� �����		xxxx
//
//Dog123 Ŭ���� �����		xxxx
//
//Bird123 Ŭ���������	    xxxx
//
//���� ���� ����

