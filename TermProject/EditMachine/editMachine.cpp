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

		int index = 1;	// ���� ���� ����
		string line = "";

		// ���� ����غ���
		for (int i = 0; i < vec.size(); i++)
		{
			if (4 + line.size() + vec[i].size() > 75) {	// ������ ���
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
				line += " " + vec[i];	// vec[i]�� ���� ���ο� ��ġ�ϰԵ�
			}
			else {	// line�� ���� ���ϱ�
				line += " " + vec[i];
			}
		}
	}
};

class StartPrint : public TextStrategy {	// ó�� editor�� ���� Ŭ����.
public:
	virtual void run(vector<string>& vec, string cmdInput) {
		int index = 1;	// ���� ���� ����
		int len = 4;
		string line = "";

		// ���� ����غ���
		for (int i = 0; i < vec.size(); i++)
		{
			if (4 + line.size() + vec[i].size() > 75) {	// ������ ���
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
				line += " " + vec[i];	// vec[i]�� ���� ���ο� ��ġ�ϰԵ�
			}
			else {	// line�� ���� ���ϱ�
				line += " " + vec[i];
			}
		}

	}
};

class PrevPage : public TextStrategy {	// p �Է�
	// ������ ���
	
public:

	virtual void run(vector<string>& vec, string cmdInput) {
		page--;
		if (page < 0) {
			page++;	// ������ �ٽ� ���󺹱�
			throw string("ù��° ������ �Դϴ�.");
		}
		printPage(vec);
	}
};

class NextPage : public TextStrategy {	// n �Է�
	// ������ ���

public:

	virtual void run(vector<string>& vec, string cmdInput) {
		page++;

		printPage(vec);
	}
};


class InsertText : public TextStrategy {
	// i(1,10,hello)
	// ù ��° ������ �� ��° �ܾ� �ڿ� hello �ֱ�
public:
	virtual void run(vector<string>& vec, string cmdInput) {

		// () �ƴϸ�
		if (cmdInput[1] != '(' || cmdInput[cmdInput.length() - 1]!= ')') {
			throw string("��ȣ�� �������� �ʽ��ϴ�. �ٽ� �Է����ּ���.");
		}
		//i�� ()����
		string substring = cmdInput.substr(2, cmdInput.length()-3); 
		istringstream ss(substring);
		string stringBuffer;
		vector<string> x;
		x.clear();
		while (getline(ss, stringBuffer, ',')) {	// , �� �����ϱ� �������� ���� stringBuffer�� ����.
			
			for (int i = 0; i < stringBuffer.length(); i++) {
				if (stringBuffer[i] == ' ') {
					throw string("������ �����մϴ�. �ٽ� �Է����ּ���.");
				}
			}
			x.push_back(stringBuffer);
		}

		// ���� 3������ Ȯ��
		if (x.size() != 3) {
			throw string("������ ������ �߸��ƽ��ϴ�. �ٽ� �Է����ּ���.");
		}

		// ���� �������� Ȯ��
		if (!atoi(x[0].c_str()) || !atoi(x[1].c_str())) {
			throw string("���� ���� ���ڿ����մϴ�. �ٽ� �Է����ּ���.");
		}

		// ó�� ���� �κ� 1~20���� Ȯ��
		if (stoi(x[0]) < 1 && stoi(x[0]) > 20) {
			throw string("ù ��° ���ڴ� 1~20 ������ ���� �Է��� �� �ֽ��ϴ�.");
		}

		// ���ںκ� 75����Ʈ �ʰ����� Ȯ��
		if (x[2].length() > 75) {
			throw string("���ڿ� ���̰� 75����Ʈ�� �Ѿ����ϴ�. �ٽ� �Է����ּ���.");
		}

		int line = stoi(x[0]);
		int prevIndex = stoi(x[1]);
		string target = x[2];


		int len = 4;
		int index = 1;
		
		for (int i = 0; i < vec.size(); i++) {
			if (index == line) {	// �ش� �����̸�
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
				// �ι�° ���� �κ� �����ϴ� �ܾ����� Ȯ��
				if (last - first < prevIndex) {
					throw string("�������� �ʴ� ��ġ�Դϴ�. �ٽ� �Է����ּ���.");
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
	// �� ��° ������ �� ��° �ܾ� ����
public:
	virtual void run(vector<string>& vec, string cmdInput) {

		// () �ƴϸ�
		if (cmdInput[1] != '(' || cmdInput[cmdInput.length() - 1] != ')') {
			throw string("��ȣ�� �������� �ʽ��ϴ�. �ٽ� �Է����ּ���.");
		}
		//d�� ()����
		string substring = cmdInput.substr(2, cmdInput.length() - 3);
		istringstream ss(substring);
		string stringBuffer;
		vector<string> x;
		x.clear();
		while (getline(ss, stringBuffer, ',')) {	// , �� �����ϱ� �������� ���� stringBuffer�� ����.
			x.push_back(stringBuffer);
		}

		// ���� 2������ Ȯ��
		if (x.size() != 2) {
			throw string("������ ������ �߸��ƽ��ϴ�. �ٽ� �Է����ּ���.");
		}

		// ���� �������� Ȯ��
		if (!atoi(x[0].c_str()) || !atoi(x[1].c_str())) {
			throw string("���� ���� ���ڿ����մϴ�. �ٽ� �Է����ּ���.");
		}

		// ó�� ���� �κ� 1~20���� Ȯ��
		if (stoi(x[0]) < 1 || stoi(x[0]) > 20) {
			throw string("ù ��° ���ڴ� 1~20 ������ ���� �Է��� �� �ֽ��ϴ�.");
		}


		int line = stoi(x[0]);
		int deleteIndex = stoi(x[1]);

		int len = 3;
		int index = 1;

		for (int i = 0; i < vec.size(); i++) {
			if (index == line) {	// �ش� �����̸�
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
				// �ι�° ���� �κ� �����ϴ� �ܾ����� Ȯ��
				if (last - first < deleteIndex) {
					throw string("�������� �ʴ� ��ġ�Դϴ�. �ٽ� �Է����ּ���.");
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
	// txt ���Ͽ��� ��� hello�� bye�� ����
	virtual void run(vector<string>& vec, string cmdInput) {

		// () �ƴϸ�
		if (cmdInput[1] != '(' || cmdInput[cmdInput.length() - 1] != ')') {
			throw string("��ȣ�� �������� �ʽ��ϴ�. �ٽ� �Է����ּ���.");
		}
		//c�� ()����
		string substring = cmdInput.substr(2, cmdInput.length() - 3);
		istringstream ss(substring);
		string stringBuffer;
		vector<string> x;
		x.clear();
		while (getline(ss, stringBuffer, ',')) {	// , �� �����ϱ� �������� ���� stringBuffer�� ����.
			x.push_back(stringBuffer);
		}

		// ���� 2������ Ȯ��
		if (x.size() != 2) {
			throw string("������ ������ �߸��ƽ��ϴ�. �ٽ� �Է����ּ���.");
		}

		// 2��° ���� 75����Ʈ �Ѵ��� Ȯ��
		if (x[1].length() > 75) {
			throw string("���ڿ� ���̰� 75����Ʈ�� �Ѿ����ϴ�. �ٽ� �Է����ּ���.");
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
			throw string("�����ϰ���� �ܾ ���� txt�� �������� �ʽ��ϴ�.");
		}
		printPage(vec);
	}
};

class SearchText : public TextStrategy {
	// s(hello)
	// txt ������ ó������ Ž���ؼ� ã�� ù ��° hello�� ��� â�� ù��° ���ο� ��ġ�ϵ���.

public:
	//���Ϳ��� target ã�� ������ ��� ����.
	//target ã���� for�� ������.
	virtual void run(vector<string>& vec, string cmdInput) {

		// () �ƴϸ�
		if (cmdInput[1] != '(' || cmdInput[cmdInput.length() - 1] != ')') {
			throw string("��ȣ�� �������� �ʽ��ϴ�. �ٽ� �Է����ּ���.");
		}
		//s�� ()����
		string substring = cmdInput.substr(2, cmdInput.length() - 3);

		// ���� 75����Ʈ �Ѵ��� Ȯ��
		if (substring.length() > 75) {
			throw string("���ڿ� ���̰� 75����Ʈ�� �Ѿ����ϴ�. �ٽ� �Է����ּ���.");
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
			throw string("ã�� �ܾ �������� �ʽ��ϴ�.");
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

// t�Է�-> ����(����� ���ο���)
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
	string input, output;	// input�� txt ���� �� ����
	
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

	editor->run(vec, "helloWorld"); // cmd���� �ƹ��ų� �־��ֱ�
	
	cout << "---------------------------------------------------------------------------" << endl;
	cout << "n:����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������\n";
	cout << "---------------------------------------------------------------------------" << endl;
	cout << "(�ָܼ޽���) 201902736 ��ä���� �������Դϴ�." << endl;


	
	while (true) {
		string message = "���������� �۵��Ǿ����ϴ�.";
		string cmdInput = "";
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "�Է�: ";

		getline(cin, cmdInput);
		

		if (cmdInput[0] == 't') {
			try {
				editor->setTextStrategy(storeStrategy);
				editor->run(vec, cmdInput);
				cout << "---------------------------------------------------------------------------" << endl;
				cout << "(�ָܼ޽���)" << "����Ǿ����ϴ�. �����⸦ �����մϴ�." << endl;
			}
			catch (string s) {
				message = s; 
				cout << "---------------------------------------------------------------------------" << endl;
				cout << "(�ָܼ޽���)" << s << endl;

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
		else { // ���� ��ɾ�
			message = "�������� �ʴ� ��ɾ� �Դϴ�.";
		}

		cout << "---------------------------------------------------------------------------" << endl;
		cout << "(�ָܼ޽���)" << message << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "n:����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������" << endl;
		



	}


	in.close();


	getchar();

	return 0;



}


