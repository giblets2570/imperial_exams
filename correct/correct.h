#ifndef CORRECT_H
#define CORRECT_H

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(const char *binary);
void text_to_binary(const char* text,char* binary);
void binary_to_text(const char* binary, char* text);
void add_error_correction(const char* data, char* corrected);
int parity(int a,int b,int c,int d);
int parity(int a,int b,int c);

int binaryToDecimal(const char* binary);

int decode(const char* received, char* decoded);

#endif