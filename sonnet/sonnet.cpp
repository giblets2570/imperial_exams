#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>
#include <fstream>

using namespace std;

#include "sonnet.h"

/* PRE-SUPPLIED HELPER FUNCTIONS START HERE */

/* NOTE: It is much more important to understand the interface to and
   the "black-box" operation of these functions (in terms of inputs and
   outputs) than it is to understand the details of their inner working. */

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int word_number, char *output_word) {
  char *output_start = output_word;
  int words = 0;

  if (word_number < 1) {
    *output_word = '\0';
    return false;
  }
  
  do {
    while (*input_line && !isalnum(*input_line))
      input_line++;

    if (*input_line == '\0')
      break;

    output_word = output_start;
    while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
      *output_word = toupper(*input_line);
      output_word++;
      input_line++;
    }
    *output_word = '\0';

    if (++words == word_number)
      return true;

  } while (*input_line);

  *output_start = '\0';
  return false;
}

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending) {

  // the next rhyming letter to be issued (persists between calls)
  static char next = 'a';
  // the table which maps endings to letters (persists between calls)
  static map<string, char> lookup;

  // providing a way to reset the table between poems
  if (ending == RESET) {
    lookup.clear();
    next = 'a';
    return '\0';
  }

  string end(ending);

  // if the ending doesn't exist, add it, and issue a new letter
  if (lookup.count(end) == 0) {
    lookup[end]=next;
    assert(next <= 'z');
    return next++;
  }

  // otherwise return the letter corresponding to the existing ending
  return lookup[end];
}

/* START WRITING YOUR FUNCTION BODIES HERE */

int count_words(const char* line){ 
    int i = 0;
    int count = 0;
    while(line[i] != '\0'){
        if(line[i] == ' ' && line[i-1] != ' ')
            count++;
        i++;
    }
    if(i > 0)
        count++;
    return count;
}

bool find_phonetic_ending(const char* word, char* phonetic_ending){
    ifstream inStream;
    inStream.open("dictionary.txt");
    char line[512];
    inStream.getline(line,512);
    while(!inStream.eof()){
        char dictWord[512];
        strcpy(dictWord,strtok(line," "));
        if(!strcmp(word,dictWord)){
            char* phonics= strtok(NULL,"\0");
            get_phonetic_ending(phonics);
            strcpy(phonetic_ending,phonics);
            return true;
        }
        inStream.getline(line,512);
    }
    strcpy(phonetic_ending,"");
    return false;
}

void get_phonetic_ending(char* letters){
    int i = 0,j = 0;
    char newLetters[512];
    while(letters[i] != '\0'){
        if(letters[i] != ' '){
            newLetters[j++] = letters[i];
        }
        i++;
    }
    i = 0;
    newLetters[j] = '\0';
    int lastVowelIndex = 0;

    while(newLetters[i] != '\0'){
        if(is_vowel(newLetters[i]))
            lastVowelIndex = i;
        i++;
    }
    int index = 0;
    strcpy(letters,"");
    for(int k = lastVowelIndex; k < j; k++){
        letters[index++] = newLetters[k];
    }
    letters[index] = '\0';
    return;
}

bool is_vowel(char ch){
    switch(ch){
        case 'A':
            return true;
        case 'E':
            return true;
        case 'I':
            return true;
        case 'O':
            return true;
        case 'U':
            return true;
        default:
            return false;
    }
    return false;
}

bool find_rhyme_scheme(const char* filename, char* scheme){
    ifstream inStream;
    inStream.open(filename);
    char line[512];
    inStream.getline(line,512);
    rhyming_letter(RESET);
    while(!inStream.eof()){
        char word[80];
        int wordCount = count_words(line);
        get_word(line,wordCount,word);
        char ending[80];
        find_phonetic_ending(word,ending);
        *(scheme++) = rhyming_letter(ending);
        inStream.getline(line,512);
    }
    *scheme = '\0';
    return true;
}

const char* identify_sonnet(const char* filename){

    char scheme[80];
    find_rhyme_scheme(filename,scheme);

    if(!strcmp(scheme,"ababcdcdefefgg"))
        return "Shakespearean";
    else if(!strcmp(scheme,"abbaabbacdcdcd"))
        return "Petrarchan";
    else if(!strcmp(scheme,"ababbcbccdcdee"))
        return "Spenserian";
    return "Unknown";
}