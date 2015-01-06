#include <iostream>
#include <cstring>
#include <cctype>

#include "words.h"

using namespace std;

void reverse(const char* word, char* reversed_word){
  int index = 0;
  for(int i = strlen(word) - 1; i >=0; i--){
    reversed_word[index++] = word[i];
  }
  reversed_word[index] = '\0';
  return;
}

bool compare(const char* one, const char* two){
  //Check if at the end of the first sentence
  if(*one == '\0'){
    //if at the end of second sentence, return true
    if(*two == '\0')
      return true;
    //if there are more letters/numbers after first sentence
    //finished, the sentences arent equal
    else if(isalnum(*two)){
      return false;
    }
    //if punctuation, check next letter/number in sentence
    else
      return compare(one, ++two);
  }
  if(*two == '\0'){
    if(isalnum(*one)){
      return false;
    }
    else
      return compare(++one, two);
  }

  if(!isalnum(*one))
    return compare(++one, two);
  if(!isalnum(*two))
    return compare(one, ++two);    
  if(tolower(*one) != tolower(*two))
    return false;

  return compare(++one,++two);
}


bool palindrome(const char* sentence){
  //get the reversed sentence
  char reversed_sentence[512];
  reverse(sentence, reversed_sentence);
  return compare(sentence, reversed_sentence);
}

bool anagram(const char* str1,const char* str2){
  char sorted_str1[512], sorted_str2[512];
  
  lower_sorted_letters(str1,sorted_str1);
  lower_sorted_letters(str2,sorted_str2);

  int length1 = strlen(sorted_str1);
  int length2 = strlen(sorted_str2);

  if(length1 != length2)
    return false;

  int i = 0;

  while(sorted_str1[i] != '\0'){
    if(sorted_str1[i] != sorted_str2[i])
      return false;
    i++;
  }

  return true;

}

void lower_sorted_letters(const char* sentence, char* sorted_letters){
  int i = 0, j = 0;
  while(sentence[i] != '\0'){
    if(isalpha(sentence[i]))
      sorted_letters[j++] = tolower(sentence[i]);
    i++;
  }

  int length = j;

  for(i = 0; i < length - 1; i++){
    int lowest = i;
    for(j = i + 1; j < length; j++){
      if(sorted_letters[j] < sorted_letters[lowest])
        lowest = j;
    }
    swap(sorted_letters[i],sorted_letters[lowest]);
  }

  sorted_letters[length] = '\0';

  return;
}

void swap(char& ch1, char& ch2){
  char temp = ch1;
  ch1 = ch2;
  ch2 = temp;
}
