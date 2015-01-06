#include <iostream>
#include "correct.h"

using namespace std;

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(const char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */

void text_to_binary(const char* text,char* binary){

	char letter = text[0];
	char binLetter[9];

	if(letter == '\0'){
		*binary = '\0';
		return;
	}

	ascii_to_binary(letter,binLetter);
	int i = 0;
	while(binLetter[i] != '\0'){
		*binary = binLetter[i];
		binary++;
		i++;
	}
	return text_to_binary(++text,binary);
}

void binary_to_text(const char* binary, char* text){
	int length = strlen(binary);
	if(length%8 != 0){
		return;
	}
	if(length/8 == 0){
		*text = '\0';
		return;
	}
	char binaryChar[8];
	for(int i = 0; i < 8; i++){
		binaryChar[i] = *binary;
		binary++;
	}
	*text = binary_to_ascii(binaryChar);
	return binary_to_text(binary,++text);
}

void add_error_correction(const char* data, char* corrected){
	int length = strlen(data);
	if(length%4 != 0){
		return;
	}
	if(length/4 == 0){
		*corrected = '\0';
		return;
	}
	int intCorrected[7];
	intCorrected[2] = static_cast<int>(data[0] - '0');
	intCorrected[4] = static_cast<int>(data[1] - '0');
	intCorrected[5] = static_cast<int>(data[2] - '0');
	intCorrected[6] = static_cast<int>(data[3] - '0');

	intCorrected[0] = parity(intCorrected[2],intCorrected[4],intCorrected[6]);
	intCorrected[1] = parity(intCorrected[2],intCorrected[5],intCorrected[6]);
	intCorrected[3] = parity(intCorrected[4],intCorrected[5],intCorrected[6]);

	for(int i = 0; i < 7; i++){
		*corrected = static_cast<char>(intCorrected[i] + '0');
		corrected++;
	}
	data+=4;
	return add_error_correction(data,corrected);
}

int parity(int a,int b,int c,int d){
	return (a+b+c+d)%2;
}

int parity(int a,int b,int c){
	return (a+b+c)%2;
}

int decode(const char* received, char* decoded){
	int length = strlen(received);
	if(length%7 != 0){
		return 0;
	}
	if(length/7 == 0){
		*decoded = '\0';
		return 0;
	}

	char p[4];
	p[3] = '\0';

	p[0] = static_cast<int>(parity(received[3],received[4],received[5],received[6]) + '0');
	p[1] = static_cast<int>(parity(received[1],received[2],received[5],received[6]) + '0');
	p[2] = static_cast<int>(parity(received[0],received[2],received[4],received[6]) + '0');

	int par = binaryToDecimal(p);
	char tempDecoded[7];
	for(int i = 0; i < 7; i++){
		tempDecoded[i] = *received;
		received++;
	}
	bool result = par;
	if(result){

		if(tempDecoded[par-1] == '0')
			tempDecoded[par-1] = '1';
		else
			tempDecoded[par-1] = '0';
	}
	*decoded++ = tempDecoded[2];
	*decoded++ = tempDecoded[4];
	*decoded++ = tempDecoded[5];
	*decoded++ = tempDecoded[6];

	return (decode(received,decoded) + result);
}

int binaryToDecimal(const char* binary){
	int length = strlen(binary);
	char binChar[9];
	int i;
	for(i = 0; i < 8 - length; i++){
		binChar[i] = 0;
	}
	for(int j = 0; j < length; j++){
		binChar[i++] = binary[j];
	}
	binChar[i] = '\0';

	return static_cast<int>(binary_to_ascii(binChar));
}