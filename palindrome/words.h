#ifndef WORDS_H
#define WORDS_H

void reverse(const char* word, char* reversed_word);
//Pre: input is the word to reverse and the 
//array that the reverse word will be put into
//Post: reversed_word has been occupied with the
//letters of word reversed

bool compare(const char* one, const char* two);
//Pre: input is two strings
//Post: returns true if the strings are the same

bool palindrome(const char* sentence);
//Pre: input is a string
//Post: returns true if input is a palindrome
//i.e. if it is the same reversed

bool anagram(const char* str1, const char* str2);
//Pre: input are two strings
//Post: returns true if str1 is an anagram of str2
//i.e. if they contain the same letters

void lower_sorted_letters(const char* sentence, char* sorted_letters);
//Pre: input is the sentence and the array that the sorted
//letter will occupy
//Post: the array sorted_letters has been filled 
//with the sorted letters of sentence all in lower case

void swap(char& ch1, char& ch2);
//Pre: input are two chars
//Post: the values of the inputs have been swapped

#endif
