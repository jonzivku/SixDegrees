// Jon Zivku, jzivku, jonzivku@me.com, Bacon.h, Degrees of Bacon, A07

// interface file for the Degrees of Bacon search
#ifndef BACON__H
#define BACON__H

#include <string>
#include <vector>
using std::vector;
using std::string;

struct WNode{
  WNode(string s=""){word = s; link = 0;}
  string word;
  WNode *link;
};

class Bacon{
 public:
  // Bacon takes a filename, and two words in its constructor
  Bacon(char* = 0, string = "", string = "");
  ~Bacon();

  void run();
  // public interface for Degrees of Bacon
 private:
  //member functions
  vector<WNode*> findAdjacentWords(vector<WNode*>);
  // pre-cond: a vector of WNode*
  // postcond: returns a vector of WNode* from allWords that are all adjacent
  // to the words in the argument. WNodes have been linked to their adjacent
  // words in the argument. Returned WNode*s in allWords have been made null

  WNode* pullWord(string);
  // pre-cond: a string
  // postcond: if the word is in allWords, returns a pointer to the word,
  // and sets the corresponding pointer in allWords to null. else, returns null
  string makeLower(string);
  // pre-cond: a string
  // postcond: the string is returned without capitalization
  bool isAdjacent(string, string);
  // pre-cond: two strings of the same length
  // postcond: returns true if the two strings differ by only one character. 
  // false if strings are different length, equal, or have more than one
  // character difference.
  void print(WNode*);
  // pre-cond: a WNode*
  // postcond: WNodes are traversed, starting at the argument, with each
  //                linked node being printed
  
  // member objects
  vector<vector<WNode*> > baconTree; 
  vector<WNode*> allWords;
  string startWord;
  string endWord;
};

#endif
