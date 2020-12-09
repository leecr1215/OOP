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
	// 다음 페이지 출력
	// pageNum = 다음 페이지의 번호
public:
	
	void run(vector<string>& vec, int pageNum) {
		int index = 1;
		int len = 3;


		cout << " " << index << "|";

		// 벡터 출력해보기
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
	// 첫 번째 라인의 열 번째 단어 뒤에 hello 넣기
public:
	void run(vector<string>& vec, int pageNum, int line, int prevIndex, string target) {

	}
};

class DeleteText : public TextStrategy {
	// d(2,10)
	// 두 번째 라인의 열 번째 단어 삭제
public:
	void run(vector<string>& vec, int line, int deleteIndex) {
		
		int len = 3;
		int index = 1;	
		
		for (int i = 0; i < vec.size(); i++) {
			if (index == line) {	// 해당 라인이면
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
	// txt 파일에서 모든 hello를 bye로 변경
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
	// txt 파일의 처음부터 탐색해서 찾은 첫 번째 hello가 출력 창의 첫번째 라인에 위치하도록.

public:
	//벡터에서 target 찾기 전까지 계속 삭제.
	//target 찾으면 for문 끝내기.
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
	// 저장 후 종료
public:
	// 현재 벡터의 상태를 파일에 그대로 덮어쓰기.
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
	/*20줄 출력*/
	int vecLast = 0;
	int vecPrev = 0;
	int point = 3;
	int index = 1;	// line

	cout << " " << index << "|";

	// 벡터 출력해보기
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


	/*작업 메뉴*/
	printLine();
	cout << "\n" << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료" << endl;
	printLine();
	cout << "\n" << message << endl;
	printLine();

}



int main() {

	//locale::global(locale("ko_KR.UTF-8"));
	static vector<string> vec;
	string input, output;	// input에 txt 내용 다 저장
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
		cout << "\n입력: ";
		cin >> choose;
		printLine();

		if(*choose == 't'){
			break;
		}
		else if (*choose == 'n') {
			cout << "\n난 n이야" << endl;
			break;
		}
		else if (*choose == 'p') {

		}
		 else if (choose[0] == 'i') {
			cout << "\n난 i이야" << endl;
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


