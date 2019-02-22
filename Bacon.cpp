// Jon Zivku, jzivku, jonzivku@me.com, Bacon.cpp, Degrees of Bacon, A07
// Implementation for the class for Degrees of Bacon

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <vector>
using std::string;
using std::vector;
using std::cout;
using std::endl;
#include "Bacon.h"

// Uses <string>, <fstream>, <vector>, WNode
Bacon::Bacon(char* filename, string word1, string word2){
  std::ifstream inStream;
  // maybe this should go in main? and pass the instream to this constructor
  inStream.open(filename);
  if(inStream.fail()){
    std::cout << "Word list \""  << filename << "\" not found." << std::endl;
    std::cout << "Exiting Program" << std::endl;
    exit(EXIT_FAILURE);
  }
  string buffer;
  WNode* temp;
  int wcount = 0;
  while(inStream >> buffer){
    // make a new node, push the pointer into allwords
    temp = new WNode(buffer);
    allWords.push_back(temp);
    wcount++;
  }
  inStream.close();
  startWord = makeLower(word1);
  endWord = makeLower(word2);
}

Bacon::~Bacon(){
  //wipe out baconTree
  for(int i = baconTree.size() - 1; i >= 0; i--){
    for(int j = baconTree[i].size() - 1; j >= 0; j--)
      if(baconTree[i][j]){
	delete baconTree[i][j]; baconTree[i][j] = NULL;
      }
    baconTree[i].clear();
  }
  baconTree.clear();
  //wipe out allWords 
  for(int i = allWords.size() - 1; i >=0; i--){
    //iterate through all words, checking for null
    // if not null, delete
    if(allWords[i]){
      delete allWords[i]; allWords[i] = NULL;
    }  
  }
}

// uses <vector>, <string>, <iostream>, WNode
void Bacon::run(){
  // push the startword into a vector, and push that into baconTree
  int level = 0; // the current level of the baconTree, starts at the trunk
  vector<WNode*> startLevel;
  
  WNode* startWNode = pullWord(startWord);
  if(startWNode == NULL){
    cout << "Your start word " << startWord << " was not found in our " 
	 << "dictionary.\nNo way to compare it to your end word: " << endWord 
	 << "\nPlease try again.\n";
    return;
  }      
  startLevel.push_back(startWNode); // make the first level of the baconTree
  baconTree.push_back(startLevel); // initialized baconTree with the first level
  while(!baconTree.back().empty()){ // check that the current level is not empty 
                                // if it is, exit loop, print nopath, and return
    baconTree.push_back(findAdjacentWords(baconTree[level]));
    level++;
    //    cout <<"level size is " <<  baconTree[level].size() << endl;
    // if bacon, print and return
    if(!baconTree[level].empty() && baconTree[level].back()->word == endWord){
      print(baconTree[level].back());
      return;
    }    
  }   
  cout << "no path from " << startWord << " to " << endWord << ".\n";
}

// uses <vector>, isAdjacent
vector<WNode*> Bacon::findAdjacentWords(vector<WNode*> lastLevel){
  vector<WNode*> nextLevel;

  // iterates through lastLevel, testing each node in the level for adjacency to
  // WNodes in allWords, uses isAdjacent
  // if the word is found, pushes the pointer into nextLevel, sets the allWords[i]
  // to the keyNode and sets the corresponding pointer in allWords to null.
  // if bacon is found, pushes bacon into the nextLevel, and returns to caller
  // with nextLevel
  int lLSize = lastLevel.size();
  int aWSize = allWords.size();
  for(int i = 0; i < lLSize; i++){
    for(int j = 0; j < aWSize; j++){
      if(allWords[j] && isAdjacent(lastLevel[i]->word, allWords[j]->word)){
	//test for null & check if words are adjacent words
	allWords[j]->link = lastLevel[i];
	if(allWords[j]->word == endWord){
	  nextLevel.push_back(allWords[j]);
	  allWords[j] = NULL; 
	  return nextLevel; //check for bacon, and return nextLevel
	}// end of if(endword found)
	nextLevel.push_back(allWords[j]);
	allWords[j] = NULL;
      }// end of if(isAdjacent)
    }// end of for(int j)
  }// end of for(int i)
  return nextLevel;
}

// Uses <string>
// returns pointer to the Node if the node is in allWords, sets pointer to null
// used for putting the first word in the first baconLevel.
WNode* Bacon::pullWord(string key){
  WNode* temp = NULL;
  for(int i = allWords.size() - 1; i >= 0; i--){
    if(allWords[i]->word == key){
      temp = allWords[i];
      allWords[i] = NULL;
      return temp;
    }
  }
  return temp; // return null if word was not found
}

// Uses <string> and <cctype>
string Bacon::makeLower(string word){
  for(unsigned int i = 0; i < word.length(); i++)
    word[i] = tolower(word[i]);  
  return word;
}

// uses <string>
bool Bacon::isAdjacent(string word1, string word2){
  // uses a for loop to check if a word is adjacent to another word
  unsigned int count = 0;
  unsigned int length = word1.length();
  if(length != word2.length())
    return false;
  for(unsigned int i = 0; i < length; i++)
    if(word1.at(i) == word2.at(i) )
      count++; 
  if(count == length - 1)
    return true;
  else
    return false;
}

// uses <iostream>, WNode
void Bacon::print(WNode* first){ // it would be cool to overload << with this
  WNode* temp = first;   //hops down the baconTree, sending words to stdout on the way
  while(temp){
    cout << temp->word << endl;
    temp = temp->link;
  }
}
