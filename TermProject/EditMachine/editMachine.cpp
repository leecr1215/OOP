#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
using namespace std;

class TextStrategy {
public:
	virtual void run(){};
	virtual void run(vector<string>& vec, int pageNum){};
	
};

class PrintPage : public TextStrategy {
	// ���� ������ ���
	// pageNum = ���� �������� ��ȣ
public:
	
	void run(vector<string>& vec, int pageNum) {
		int index = 1;
		int len = 3;


		cout << " " << index << "|";

		// ���� ����غ���
		for (int i = 0; i < vec.size(); i++) {
			len = len + 1 + vec[i].size();

			if (len <= 75 && 20*pageNum <= index) {

				cout << " " << vec[i];

			}
			else if(20 * pageNum <= index && len > 75){

				len = 3;
				index++;
				cout << "\n";
				if ((index/pageNum) < 21) {
					if ((index/pageNum) < 10) {
						cout << " " << index << "|";
					}
					else {
						cout << index << "|";
					}
				}
				else {
					
					break;
				}
				i--;
			}
		}

	}
};


class InsertText : public TextStrategy {
	// i(1,10,hello)
	// ù ��° ������ �� ��° �ܾ� �ڿ� hello �ֱ�
public:
	void run(vector<string>& vec, int pageNum, int line, int prevIndex, string target) {

	}
};

class DeleteText : public TextStrategy {
	// d(2,10)
	// �� ��° ������ �� ��° �ܾ� ����
public:
	void run(vector<string>& vec, int line, int deleteIndex) {
		
		int len = 3;
		int index = 1;	
		
		for (int i = 0; i < vec.size(); i++) {
			if (index == line) {	// �ش� �����̸�
				vec.erase(vec.begin()+i+deleteIndex-1);
				return;
			}
			len = len + 1 + vec[i].size();
			
			if(len > 76) {

				len = 3;
				index++;
				
				if (index > 21) {
					break;
				}
				
				i--;
			}
		}

	}

};

class ChangeText : public TextStrategy {
	// c(hello, bye)
	// txt ���Ͽ��� ��� hello�� bye�� ����
	void run(vector<string>& vec, string target, string changeData) {
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[i] == target) {
				vec[i] = changeData;
			}
			

		}
	}
};

class SearchText : public TextStrategy {
	// s(hello)
	// txt ������ ó������ Ž���ؼ� ã�� ù ��° hello�� ��� â�� ù��° ���ο� ��ġ�ϵ���.

public:
	//���Ϳ��� target ã�� ������ ��� ����.
	//target ã���� for�� ������.
	void run(vector<string>& vec, string target) {
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[0] == target) {
				break;
			}
			else {
				vec.erase(vec.begin());
			}
			
		}
	}

};

class StoreFile : public TextStrategy {
	// ���� �� ����
public:
	// ���� ������ ���¸� ���Ͽ� �״�� �����.
	void run(vector<string>& vec, string fileName) {

	}
};

class EditMachine {
public:
	EditMachine(TextStrategy *text) {
		textStrategy = text;
	}
	virtual void run() {

	}
	void run(vector<string>& vec, int pageNum) {	// NextText, PrevText

	}
	void setTextStrategy(TextStrategy* text) {
		textStrategy = text;
	}
protected:
	TextStrategy* textStrategy;
};



void printLine() {
	for (int i = 0; i < 75; i++) {
		cout << "-";
	}
}


void print(vector<string>& vec, string message) {
	//wcout.imbue(locale("kor"));
	/*20�� ���*/
	int vecLast = 0;
	int vecPrev = 0;
	int point = 3;
	int index = 1;	// line

	cout << " " << index << "|";

	// ���� ����غ���
	for (int i = 0; i < vec.size(); i++) {
		point = point + 1 + vec[i].size();
		if (point <= 75) {

			cout << " " << vec[i];

		}
		else {

			point = 3;
			index++;
			cout << "\n";
			if (index < 21) {
				if (index < 10) {
					cout << " " << index << "|";
				}
				else {
					cout << index << "|";
				}
			}
			else {
				vecLast = i - 1;
				break;
			}
			i--;
		}
	}


	/*�۾� �޴�*/
	printLine();
	cout << "\n" << "n:����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������" << endl;
	printLine();
	cout << "\n" << message << endl;
	printLine();

}



int main() {

	//locale::global(locale("ko_KR.UTF-8"));
	static vector<string> vec;
	string input, output;	// input�� txt ���� �� ����
	int page = 1;
	string st;

	ifstream in("test2.txt");

	if (in.is_open()) {
		while (!in.eof())
		{
			in >> input;
			st += input + " ";
			vec.push_back(input);

		}

	}
	else {
		cout << "Can't find the file" << endl;
	}

	
	
	string message = "no error";
	while (true) {
		char choose[100] = "\0";
		print(vec, message);
		cout << "\n�Է�: ";
		cin >> choose;
		printLine();

		if(*choose == 't'){
			break;
		}
		else if (*choose == 'n') {
			cout << "\n�� n�̾�" << endl;
			break;
		}
		else if (*choose == 'p') {

		}
		 else if (choose[0] == 'i') {
			cout << "\n�� i�̾�" << endl;
			break;
		 }
		 else if (choose[0] == 'd') {

		}
		 else if (choose[0] == 'c') {

		}
		 else if (choose[0] == 's') {

		}
		 
		

	}
	

	in.close();


	getchar();

	return 0;

	/*
	int line_count = 1;
    system("cls");
    string line = "";
    for (int i = 0; i < data.size(); i++)
    {
      line += data[i] + " ";
      if (line.size() + data[i].size() > 75) {
        if (page_count * 20 < line_count && line_count <= (page_count + 1) * 20)
        {
          cout << setw(2) << line_count << "| " << line << "\n";
        }
        line_count++;
        line = "";
      }
    }
	*/




}


