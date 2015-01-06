#include <cstring>
#include <cctype>
#include "piglatin.h"

bool isVowel(char ch, int position, int length){
	if(position >= length){
		return false;
	}
	for(int i = 0; i < NUMVOWELS; i++){
		if(ch == vowels[i]){
			return true;
		}
	}
	return false;
}

int findFirstVowel(const char* word){
	int length = strlen(word);
	for(int i = 0; i < length; i++){
		if(isVowel(word[i],i,length)){
			if((word[i] == 'y' || word[i] == 'Y') && (i == 0 || i == length - 1)){

			}
			else{
				return i;
			}
		}
	}
	return -1;
}

void translateWord(const char* english, char* piglatin){
	strcpy(piglatin,"");
	//case of number
	if(!isalpha(english[0])){
		strcpy(piglatin,english);
		return;
	}
	int length = strlen(english);
	int index;
	int firstVowel = findFirstVowel(english);
	if(firstVowel == -1){
		strcpy(piglatin,english);
		index = length;
	}
	else{
		index = 0;
		bool firstUpper = isupper(english[0]);
		for(int i = firstVowel; i < length; i++){
			piglatin[index] 
			= (index == 0 && firstUpper) ? toupper(english[i]) : english[i];
			index++;
		}
		for(int i = 0; i < firstVowel; i++){
			piglatin[index++]
			= (i == 0) ? tolower(english[i]) : english[i];
		}
		if(firstVowel == 0){
			piglatin[index++] = 'w';
		}
	}

	piglatin[index++] = 'a';
	piglatin[index++] = 'y';
	piglatin[index] = '\0';

	return;
}

void translateStream(std::istream& inputStream, std::ostream& outputStream){
	using namespace std;
	char ch;
	char word[100];
	char piglatin[100];
	strcpy(piglatin,"");
	int index = 0;

	inputStream.get(ch);

	while(isalpha(ch) > 0 && !inputStream.eof()){
		word[index++] = ch;
		inputStream.get(ch);
	}

	word[index] = '\0';

	translateWord(word,piglatin);
	
	int wordLength = strlen(piglatin);


	for(int i = 0; i < wordLength; i++){
		outputStream << piglatin[i];
	}

	if(!inputStream.eof()){
		outputStream << ch;
		translateStream(inputStream,outputStream);
	}
	return;
}