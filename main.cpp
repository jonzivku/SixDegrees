// Jon Zivku, jzivku, jonzivku@me.com, main.cpp, Degrees of Bacon, A07
/* This application finds out if two words can be linked by adjacent words,
   where an adjacent word is a word that differs by 1 letter.
   
   Code Status: tested, compiling, up to spec

   When I first made the program, I used a Dictionary class and a Bacon class
   in separate files, but when I started writing functions, I had a lot of
   trouble figuring out which class should do which function, in this case it
   wasn't nearly as clear as cinco, probably owing to the dynamic allWords
   vector. I was defintely most interested in the command line arguments aspect
   - they're something I use a lot in my day-to-day, but wasn't sure how to
   implement them. I've hardcoded for the -r, and was working on implementing the
   -d and -s, but ran out of time. I've left my work commented out here.  My
   findAdjacentWords function is one of the more complex that I've written, taking
   a vector of pointers and returning a vector of pointers, but it never felt
   unintuitive to use. When finishing up my program, I used valgrind for the first
   time, and it helped me resolve a huge memory leak. 
*/

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
using std::cout;
using std::string;
using std::endl;
#include "Bacon.h"

void parameters(char*);

int main(int argc, char *argv[]){
  bool reverseFlag = false;
  bool destFlag = false;
  bool startFlag = false;
  char *dict;
  char *sWord = argv[0];
  char *dWord = argv[0];
 
  if(argc == 1)
    parameters(argv[0]);
  
  if(argc == 2) {
    dict = argv[1];
  }

  if(argc == 3){
    if(!strcmp(argv[1],"-r")){
      dict = argv[2];
      reverseFlag = true;
    }else if(!strcmp(argv[2],"-r")){
      dict = argv[1];
      reverseFlag = true;
    }else
      parameters(argv[0]);
  }

  if(argc == 4){
    if(!strcmp(argv[1], "-d")){
      dWord = argv[2]; destFlag = true;
      dict = argv[3];
    }else if(!strcmp(argv[1], "-s")){
      sWord = argv[2]; startFlag = true;
      dict = argv[3];
    }
    if(!strcmp(argv[2], "-d")){
      dWord = argv[3]; destFlag = true;
      dict = argv[1];
    }else if(!strcmp(argv[2], "-s")){
      sWord = argv[3]; startFlag = true;
      dict = argv[1];
    }	
  }

  cout << "Six Degrees of Bacon\n";
  cout << "Jon Zivku, jonzivku@me.com\n";
  
  string startWord(sWord);  
  string endWord(dWord);
  if(!destFlag)
    endWord = "bacon";
  cout << "Your word?";

  if(!startFlag)
    std::cin >> startWord;
  else if(startFlag)
    cout << startWord << endl;

  if(reverseFlag){
    string temp = startWord;
    startWord = endWord;
    endWord = temp;
  }

  Bacon theTree(dict, startWord, endWord);
  theTree.run();
  return 0;
}

void parameters(char *programName){
    cout << "Usage: " << programName << " [dictionary filename]" << endl;
    cout << "Initialization options (use only 1 option at a time):" << endl;
    cout << "-r      \t\t swap the order of the start word and the end word" 
	 << endl;
    cout << "-s WORD \t\t set the start word WORD" << endl;
    cout << "-d WORD \t\t set the destination word WORD" << endl;
    exit(0);
}
