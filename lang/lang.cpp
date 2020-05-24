#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

using namespace std;

struct tokens {

};

struct token{
	int id;
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

		for (i = 0; i < size(operators); ++i) {
			if (ch == operators[i]) {
				cout << ch << " :\t\t[OPERATOR]\n";
			}
		}

		for (i = 0; i < size(separators); ++i) {
			if (ch == separators[i]) {
				cout << ch << " :\t\t[SEPARATOR]\n";
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
				cout << buffer << " :\t\t[OUTPUT]\n";
				toPrint = 0;
			} else if (isKeyword(buffer) == 1)
				cout << buffer << " :\t\t[KEYWORD]\n";
			else if (isdigit(buffer[0]))
				cout << buffer << " :\t\t[CONSTANT]\n";
			else
				cout << buffer << " :\t\t[VARIABLE]\n";
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
