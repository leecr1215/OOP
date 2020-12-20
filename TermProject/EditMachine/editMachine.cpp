#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <sstream>
using namespace std;

static int page = 0;


class TextStrategy {
public:
	virtual void run(vector<string>& vec, string cmdInput) = 0;	//printpage
	void printPage(vector<string>&vec) {
		cout << "---------------------------------------------------------------------------" << endl;

		int index = 1;	// 현재 라인 길이
		string line = "";

		// 벡터 출력해보기
		for (int i = 0; i < vec.size(); i++)
		{
			if (4 + line.size() + vec[i].size() > 75) {	// 다음줄 출력
				if (page * 20 < index && index <= (page + 1) * 20)
				{
					if (index < 10) {
						cout << " " << index << "|" << line << "\n";
					}
					else {
						cout << index << "|" << line << "\n";
					}

				}
				index++;
				line = "";
				line += " " + vec[i];	// vec[i]는 다음 라인에 위치하게됨
			}
			else {	// line에 글자 더하기
				line += " " + vec[i];
			}
		}
	}
};

class StartPrint : public TextStrategy {	// 처음 editor에 넣을 클래스.
public:
	virtual void run(vector<string>& vec, string cmdInput) {
		int index = 1;	// 현재 라인 길이
		int len = 4;
		string line = "";

		// 벡터 출력해보기
		for (int i = 0; i < vec.size(); i++)
		{
			if (4 + line.size() + vec[i].size() > 75) {	// 다음줄 출력
				if (page * 20 < index && index <= (page + 1) * 20)
				{
					if (index < 10) {
						cout << " " << index << "|" << line << "\n";
					}
					else {
						cout << index << "|" << line << "\n";
					}

				}
				index++;
				line = "";
				line += " " + vec[i];	// vec[i]는 다음 라인에 위치하게됨
			}
			else {	// line에 글자 더하기
				line += " " + vec[i];
			}
		}

	}
};

class PrevPage : public TextStrategy {	// p 입력
	// 페이지 출력
	
public:

	virtual void run(vector<string>& vec, string cmdInput) {
		page--;
		if (page < 0) {
			page++;	// 페이지 다시 원상복구
			throw string("첫번째 페이지 입니다.");
		}
		printPage(vec);
	}
};

class NextPage : public TextStrategy {	// n 입력
	// 페이지 출력

public:

	virtual void run(vector<string>& vec, string cmdInput) {
		page++;

		printPage(vec);
	}
};


class InsertText : public TextStrategy {
	// i(1,10,hello)
	// 첫 번째 라인의 열 번째 단어 뒤에 hello 넣기
public:
	virtual void run(vector<string>& vec, string cmdInput) {

		// () 아니면
		if (cmdInput[1] != '(' || cmdInput[cmdInput.length() - 1]!= ')') {
			throw string("괄호가 존재하지 않습니다. 다시 입력해주세요.");
		}
		//i과 ()제거
		string substring = cmdInput.substr(2, cmdInput.length()-3); 
		istringstream ss(substring);
		string stringBuffer;
		vector<string> x;
		x.clear();
		while (getline(ss, stringBuffer, ',')) {	// , 에 도달하기 전까지의 값이 stringBuffer에 저장.
			
			for (int i = 0; i < stringBuffer.length(); i++) {
				if (stringBuffer[i] == ' ') {
					throw string("공백이 존재합니다. 다시 입력해주세요.");
				}
			}
			x.push_back(stringBuffer);
		}

		// 인자 3개인지 확인
		if (x.size() != 3) {
			throw string("인자의 개수가 잘못됐습니다. 다시 입력해주세요.");
		}

		// 숫자 숫자인지 확인
		if (!atoi(x[0].c_str()) || !atoi(x[1].c_str())) {
			throw string("숫자 숫자 문자여야합니다. 다시 입력해주세요.");
		}

		// 처음 숫자 부분 1~20인지 확인
		if (stoi(x[0]) < 1 && stoi(x[0]) > 20) {
			throw string("첫 번째 인자는 1~20 사이의 값만 입력할 수 있습니다.");
		}

		// 문자부분 75바이트 초과인지 확인
		if (x[2].length() > 75) {
			throw string("문자열 길이가 75바이트를 넘었습니다. 다시 입력해주세요.");
		}

		int line = stoi(x[0]);
		int prevIndex = stoi(x[1]);
		string target = x[2];


		int len = 4;
		int index = 1;
		
		for (int i = 0; i < vec.size(); i++) {
			if (index == line) {	// 해당 라인이면
				int first = i;
				int last=i;
				int lineLen = 4;
				for (int j = i; j < vec.size(); j++) {
					lineLen += 1 + vec[j].size();
					if (lineLen > 75) {
						break;
					}
					else {
						last++;
					}
				}
				// 두번째 숫자 부분 존재하는 단어인지 확인
				if (last - first < prevIndex) {
					throw string("존재하지 않는 위치입니다. 다시 입력해주세요.");
				}
				vec.insert(vec.begin() + i + prevIndex , target);
				printPage(vec);
				return;
			}
			len = len + 1 + vec[i].size();

			if (len > 75) {

				len = 4;
				index++;

				if (index > 21) {
					break;
				}

				i--;
			}
		}
	}
};

class DeleteText : public TextStrategy {
	// d(2,10)
	// 두 번째 라인의 열 번째 단어 삭제
public:
	virtual void run(vector<string>& vec, string cmdInput) {

		// () 아니면
		if (cmdInput[1] != '(' || cmdInput[cmdInput.length() - 1] != ')') {
			throw string("괄호가 존재하지 않습니다. 다시 입력해주세요.");
		}
		//d과 ()제거
		string substring = cmdInput.substr(2, cmdInput.length() - 3);
		istringstream ss(substring);
		string stringBuffer;
		vector<string> x;
		x.clear();
		while (getline(ss, stringBuffer, ',')) {	// , 에 도달하기 전까지의 값이 stringBuffer에 저장.
			x.push_back(stringBuffer);
		}

		// 인자 2개인지 확인
		if (x.size() != 2) {
			throw string("인자의 개수가 잘못됐습니다. 다시 입력해주세요.");
		}

		// 숫자 숫자인지 확인
		if (!atoi(x[0].c_str()) || !atoi(x[1].c_str())) {
			throw string("숫자 숫자 문자여야합니다. 다시 입력해주세요.");
		}

		// 처음 숫자 부분 1~20인지 확인
		if (stoi(x[0]) < 1 || stoi(x[0]) > 20) {
			throw string("첫 번째 인자는 1~20 사이의 값만 입력할 수 있습니다.");
		}


		int line = stoi(x[0]);
		int deleteIndex = stoi(x[1]);

		int len = 3;
		int index = 1;

		for (int i = 0; i < vec.size(); i++) {
			if (index == line) {	// 해당 라인이면
				int first = i;
				int last = i;
				int lineLen = 3;
				for (int j = i; j < vec.size(); j++) {
					lineLen += 1 + vec[j].size();
					if (lineLen > 75) {
						break;
					}
					else {
						last++;
					}
				}
				// 두번째 숫자 부분 존재하는 단어인지 확인
				if (last - first < deleteIndex) {
					throw string("존재하지 않는 위치입니다. 다시 입력해주세요.");
				}
				vec.erase(vec.begin() + i + deleteIndex - 1);
				printPage(vec);
				return;
			}
			len = len + 1 + vec[i].size();

			if (len > 75) {

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
	virtual void run(vector<string>& vec, string cmdInput) {

		// () 아니면
		if (cmdInput[1] != '(' || cmdInput[cmdInput.length() - 1] != ')') {
			throw string("괄호가 존재하지 않습니다. 다시 입력해주세요.");
		}
		//c와 ()제거
		string substring = cmdInput.substr(2, cmdInput.length() - 3);
		istringstream ss(substring);
		string stringBuffer;
		vector<string> x;
		x.clear();
		while (getline(ss, stringBuffer, ',')) {	// , 에 도달하기 전까지의 값이 stringBuffer에 저장.
			x.push_back(stringBuffer);
		}

		// 인자 2개인지 확인
		if (x.size() != 2) {
			throw string("인자의 개수가 잘못됐습니다. 다시 입력해주세요.");
		}

		// 2번째 인자 75바이트 넘는지 확인
		if (x[1].length() > 75) {
			throw string("문자열 길이가 75바이트를 넘었습니다. 다시 입력해주세요.");
		}

		string target = x[0];
		string changeData = x[1];

		bool check = false;
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[i] == target) {
				vec[i] = changeData;
				check = true;
			}
		}
		if (check == false) {
			throw string("변경하고싶은 단어가 현재 txt에 존재하지 않습니다.");
		}
		printPage(vec);
	}
};

class SearchText : public TextStrategy {
	// s(hello)
	// txt 파일의 처음부터 탐색해서 찾은 첫 번째 hello가 출력 창의 첫번째 라인에 위치하도록.

public:
	//벡터에서 target 찾기 전까지 계속 삭제.
	//target 찾으면 for문 끝내기.
	virtual void run(vector<string>& vec, string cmdInput) {

		// () 아니면
		if (cmdInput[1] != '(' || cmdInput[cmdInput.length() - 1] != ')') {
			throw string("괄호가 존재하지 않습니다. 다시 입력해주세요.");
		}
		//s와 ()제거
		string substring = cmdInput.substr(2, cmdInput.length() - 3);

		// 인자 75바이트 넘는지 확인
		if (substring.length() > 75) {
			throw string("문자열 길이가 75바이트를 넘었습니다. 다시 입력해주세요.");
		}

		string target = substring;
		bool check = false;

		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[i] == target) {
				check = true;
				break;
			}
		}

		if (check == false) {
			throw string("찾는 단어가 존재하지 않습니다.");
		}

		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[0] == target) {
				break;
			}
			else {
				vec.erase(vec.begin());
			}
		}

		printPage(vec);
	}

};

// t입력-> 저장(종료는 메인에서)
class StoreText : public TextStrategy {	
public:
	virtual void run(vector<string>& vec, string cmdInput) {
		out.open("test2.txt");

		string content = "";

		for (int i = 0; i < vec.size(); i++) {
			content += vec[i] + " ";
		}

		if (out.is_open()) {
			out << content;
			out.close();

		}
		else {
			throw string("Can't find the file");
		}
	}
private:
	fstream out;
};



class EditMachine {
public:
	EditMachine(TextStrategy* strategy) {
		textStrategy = strategy;
	}
	virtual void run(vector<string>&vec, string cmdInput) {
		textStrategy->run(vec, cmdInput);
	}
	void setTextStrategy(TextStrategy* strategy) {
		textStrategy = strategy;
	}
	
protected:
	TextStrategy* textStrategy;
};

int main() {
	static vector<string> vec;
	string input, output;	// input에 txt 내용 다 저장
	
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

	TextStrategy* printStrategy = new StartPrint;
	TextStrategy* nextStrategy = new NextPage;
	TextStrategy* prevStrategy = new PrevPage;
	TextStrategy* insertStrategy = new InsertText;
	TextStrategy* deleteStrategy = new DeleteText;
	TextStrategy* changeStrategy = new ChangeText;
	TextStrategy* searchStrategy = new SearchText;
	TextStrategy* storeStrategy = new StoreText;

	EditMachine* editor = new EditMachine(printStrategy);

	editor->run(vec, "helloWorld"); // cmd값은 아무거나 넣어주기
	
	cout << "---------------------------------------------------------------------------" << endl;
	cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료\n";
	cout << "---------------------------------------------------------------------------" << endl;
	cout << "(콘솔메시지) 201902736 이채림의 편집기입니다." << endl;


	
	while (true) {
		string message = "정상적으로 작동되었습니다.";
		string cmdInput = "";
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "입력: ";

		getline(cin, cmdInput);
		

		if (cmdInput[0] == 't') {
			try {
				editor->setTextStrategy(storeStrategy);
				editor->run(vec, cmdInput);
				cout << "---------------------------------------------------------------------------" << endl;
				cout << "(콘솔메시지)" << "저장되었습니다. 편집기를 종료합니다." << endl;
			}
			catch (string s) {
				message = s; 
				cout << "---------------------------------------------------------------------------" << endl;
				cout << "(콘솔메시지)" << s << endl;

			}
			break;
		}
		else if (cmdInput[0] == 'n') {
			try {
				editor->setTextStrategy(nextStrategy);
				editor->run(vec, cmdInput);
			}
			catch (string s) {
				message = s;
			}
		}
		else if (cmdInput[0] == 'p') {
			try {
				editor->setTextStrategy(prevStrategy);
				editor->run(vec, cmdInput);
			}
			catch (string s) {
				message = s;
			}
			
		}
		else if (cmdInput[0] == 'i') {
			try {
				editor->setTextStrategy(insertStrategy);
				editor->run(vec, cmdInput);
			}
			catch (string s) {
				message = s;
			}
		}
		else if (cmdInput[0] == 'd') {
			try {
				editor->setTextStrategy(deleteStrategy);
				editor->run(vec, cmdInput);
			}
			catch (string s) {
				message = s;
			}
		}
		else if (cmdInput[0] == 'c') {
			try {
				editor->setTextStrategy(changeStrategy);
				editor->run(vec, cmdInput);
			}
			catch (string s) {
				message = s;
			}
		}
		else if (cmdInput[0] == 's') {
			try {
				editor->setTextStrategy(searchStrategy);
				editor->run(vec, cmdInput);
			}
			catch (string s) {
				message = s;
			}
		}
		else { // 없는 명령어
			message = "존재하지 않는 명령어 입니다.";
		}

		cout << "---------------------------------------------------------------------------" << endl;
		cout << "(콘솔메시지)" << message << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료" << endl;
		



	}


	in.close();


	getchar();

	return 0;



}


