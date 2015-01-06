#ifndef CORRECT_H
#define CORRECT_H

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(const char *binary);
//Predefined funcitons

void text_to_binary(const char* text,char* binary);
//Pre: input is text and the array the output will 
//bd put into
//Post: the value of binary has been set to the 
//binary value of the text

void binary_to_text(const char* binary, char* text);

void add_error_correction(const char* data, char* corrected);
//Pre: input is the datae in binary form
//Post: output is the data with the error correcting
//variables added

int parity(int a,int b,int c,int d);
//Pre: input is 4 integers
//Post: return 1 if sum is odd, 0 if even

int parity(int a,int b,int c);
//Pre: input is 3 integers
//Post: return 1 if sum is odd, 0 if even

int binaryToDecimal(const char* binary);
//Pre: input is a binary number in the form of a string
//Post: output is the number in decimal form

int decode(const char* received, char* decoded);
//Pre: input is the recieved data string
//Post: the value of decoded is set to the decoded value of received
//with error correction
//Function returns the number of errors corrected

#endif