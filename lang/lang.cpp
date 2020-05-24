#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

using namespace std;

// EXP : { KEYWORD : VARIABLE : CONSTANT : OPERATOR : CONSTANT } 
//		     non		

enum token {
	TT_OP, //OPERATOR
	TT_SEP,  //SEPARATOR
	TT_KEY, //KEYWORD
	TT_CONST, //CONSTANT
	TT_VAR, //VAR
	TT_OUT, //OUTPUT
	TT_IGN, // TO BE IGNORED
};

int isKeyword(char buffer[]);

int main() {

	char ch, buffer[15];
	char operators[] = "+-*/%=", separators[] = ";,(){}";

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
			}
		}

		for (i = 0; i < size(separators); ++i) {
			if (ch == separators[i]) {
				cout << ch;
				t = TT_SEP;
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
			case TT_CONST: cout << "[CONSTANT]\n";   break;
			case TT_KEY: cout << "[KEYWORD]\n";   break;
			case TT_OP: cout << "[OPERATOR]\n";   break;
			case TT_OUT: cout << "[OUTPUT]\n";   break;
			case TT_SEP: cout << "[SEPARATOR]\n";   break;
			case TT_VAR: cout << "[VARIABLE]\n";   break;
			case TT_IGN: break;
		}
	}

	fin.close();

	return 0;
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
