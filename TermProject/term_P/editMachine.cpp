#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

void main() {
	vector<string> vec;
	string input, output;	// input�� txt ���� �� ����

	ifstream in("test1.txt");

	if (in.is_open()) {
		in >> input;
		cout << input << endl;
	}
	else {
		cout << "Can't find the file" << endl;
	}

	in.close();

	


}