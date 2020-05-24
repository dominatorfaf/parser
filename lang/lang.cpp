#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<vector>

using namespace std;

enum token {
	TT_OP, //OPERATOR			//0
	TT_SEP,  //SEPARATOR		//1
	TT_KEY, //KEYWORD			//2
	TT_CONST, //CONSTANT		//3
	TT_VAR, //VAR				//4
	TT_OUT, //OUTPUT			//5
	TT_LEFTPARENT, // (			//6
	TT_RIGHTPARENT, // )		//7
	TT_EQUALS, // =				//8
	TT_IGN, //TBIGNORED
};

int isKeyword(char buffer[]);

bool parser(vector <token> vecOfElements);

int main() {
	vector <token> toEvaluate;
	char ch, buffer[15];
	char operators[] = "+-*/%", separators[] = ";,(){}";

	int i, j = 0, toPrint = 0;

	ifstream fin("code.txt");

	if (!fin.is_open()) {
		cout << "No file\n";
		return 0;
	}

	while (!fin.eof()) {
		ch = fin.get();

		token t = TT_IGN;

		for (i = 0; i < size(operators); ++i) {
			if (ch == operators[i]) {
				cout << ch;
				t = TT_OP;
				continue;
			}
			else if (ch == '='){
				cout << ch;
				t = TT_EQUALS;
				continue;
			}
		}

		for (i = 0; i < size(separators); ++i) {
			if (ch == separators[i]) {
				cout << ch;
				t = TT_SEP;
				continue;
			}
			else if (ch == ')') {
				t = TT_LEFTPARENT;
				continue;
			}
			else if (ch == '(') {
				t = TT_RIGHTPARENT;
				continue;
			}
		}

		if (isalnum(ch) || ch == '"') {
			buffer[j++] = ch;
			if (ch == '"')
				toPrint = 1;
		}
		else if ((ch == ' ' || ch == '\n') && (j != 0)) {
			buffer[j] = '\0';
			j = 0;

			if (toPrint == 1) {
				cout << buffer;
				t = TT_OUT;
				toPrint = 0;
			}
			else if (isKeyword(buffer) == 1) {
				cout << buffer;
				t = TT_KEY;
			}
			else if (isdigit(buffer[0])) {
				cout << buffer;
				t = TT_CONST;
			}
			else {
				cout << buffer;
				t = TT_VAR;
			}
		}
		
		switch (t) {
			case TT_CONST: cout << "\t:\t[CONSTANT]\n"; toEvaluate.push_back(t);  break;
			case TT_KEY: cout << "\t:\t[KEYWORD]\n"; toEvaluate.push_back(t);  break;
			case TT_OP: cout << "\t:\t[OPERATOR]\n"; toEvaluate.push_back(t);  break;
			case TT_OUT: cout << "\t:\t[OUTPUT]\n";  toEvaluate.push_back(t); break;
			case TT_SEP: cout << "\t:\t[SEPARATOR]\n"; toEvaluate.push_back(t); break;
			case TT_VAR: cout << "\t:\t[VARIABLE]\n"; toEvaluate.push_back(t);  break;
			case TT_LEFTPARENT: cout << "\t:\t[LEFT_PARANTHESE]\n"; toEvaluate.push_back(t);  break;
			case TT_RIGHTPARENT: cout << "\t:\t[RIGHT_PARANTHESE]\n"; toEvaluate.push_back(t);  break;
			case TT_EQUALS: cout << "\t:\t[EQUALS]\n"; toEvaluate.push_back(t); break;
			case TT_IGN: break;
		}

	}

	fin.close();

	for (std::vector<int>::size_type i = 0; i != toEvaluate.size(); i++) {
		cout << toEvaluate[i];
	}

	if (parser(toEvaluate)) {
		cout << "\nValid Syntax";
	}
	else {
		cout << "\nInvalid Syntax";
	}

	return 0;
}

bool parser(vector <token> vecOfElements) {
	bool fileError = false;
	int openParanthese = 0; 
	for (std::vector<int>::size_type i = 0; i != vecOfElements.size(); i++) {

		if (vecOfElements[vecOfElements.size() - 1] != TT_SEP) {
			cout << "Semicolon expected at the end";
			break;
		}

		switch (vecOfElements[i]) {
			case TT_CONST: 
				if ( vecOfElements[i + 1] == TT_CONST) {
					fileError = true;
					cout << "\nCONST error at " << i + 1;
				}
				break;
			case TT_OP: 
				if (i == 0 || vecOfElements[i + 1] == TT_OP || vecOfElements[i + 1] == TT_SEP || i == vecOfElements.size()) {
					fileError = true;
					cout << "\nOP error at " << i + 1;
				}
				break;
			case TT_SEP:
				if (i == 0) {
					fileError = true;
					cout << "\nSEP error" << i + 1;
				}
				break;
			case TT_LEFTPARENT:  
				openParanthese++;
				break;
			case TT_RIGHTPARENT: 
				if (openParanthese == 0) {
					fileError = true;
					cout << "\nPARANTHESE error" << i + 1;
				}
				else {
					openParanthese--;
				}
				break;
		}
		if (fileError == true) {
			return false;
		} 
	}
	if (openParanthese != 0) {
		cout << "\nopen PARANTHESE error";
		return false;
	}
	return true;
}

int isKeyword(char buffer[]) {
	char keywords[28][10] = { "print","break","case","char","const","continue","default",
							"do","double","else","enum","float","for","goto",
							"if","int","long","return","short","signed",
							"sizeof","static","struct","switch",
							"unsigned","void","while" };
	int i, flag = 0;

	for (i = 0; i < 32; ++i) {
		if (strcmp(keywords[i], buffer) == 0) {
			flag = 1;
			break;
		}
	}

	return flag;
}
