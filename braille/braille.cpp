#include <iostream>
#include <cctype>

#include "braille.h"

const char* dots[6] = 
{"abcdefghklmnopqruvxyz",
"bfghijlpqrstvw.,;!?()",
"klmnopqrstuvxyz;-!?()",
"cdfgijmnpqstwxy",
"deghjnoqrtwyz.!()",
"uvwxyz.-?()"};

const char* number = "..0000";
const char* capital = ".....0";

using namespace std;

int encode_character(char ch, char* braille){
	int i = 0;
	if(isdigit(ch)){
		strcpy(braille,number);
		if(ch == '0')
			ch = 'j';
		else
			ch = ('a')+(ch-'1') ;
		i = 6;
	} else if(isupper(ch)){
		strcpy(braille,capital);
		ch = tolower(ch);
		i = 6;
	}
	for (int j = 0; j < 6; j++){
		if(strchr(dots[j],ch) == NULL)
			braille[i] = '.';
		else
			braille[i] = '0';
		i++;
	}
	braille[i] = '\0';
	return strlen(braille);
}

void encode(const char* plaintext,char* braille){
	if(*plaintext == '\0'){
		*braille = '\0';
		return;
	}
	char temp[20];
	encode_character(*plaintext++,temp);
	int i = 0;
	while(temp[i] != '\0'){
		*braille++ = temp[i];
		i++;
	}
	encode(plaintext,braille);
	return;
}

void print_braille(const char* plaintext, ostream& output){
	int length = strlen(plaintext)*12;
	char* braille = new char[length];
	encode(plaintext,braille);
	int brailleLength = strlen(braille);
	for(int col = 0; col < 3; col++){
		for(int row = col; row < brailleLength; row+=6)
			output << braille[row] << braille[row+3] << " ";
		output << endl;
	}
	delete braille;
	while(*plaintext != '\0'){
		if(isdigit(*plaintext))
			output << "   ";
		else if(isupper(*plaintext))
			output << "   ";
		output << *plaintext++ << "  ";
	}
	output << endl;
	return;
}