#ifndef PIGLATIN_H
#define PIGLATIN_H
#define NUMVOWELS 12
#include <iostream>

const char vowels[] = "aeiouyAEIOUY";

bool isVowel(char ch, int position, int length);

int findFirstVowel(const char* word);

void translateWord(const char* english, char* piglatin);

void translateStream(std::istream& inputStream, std::ostream& outputStream);

#endif