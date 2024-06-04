#include "a3.h"
#include <string>
#include <iostream>

// this function takes a string and returns a string 
int getIdx(char ch){
  return ch -'a';
}

// this constructor takes a an array of strings and the size of the array, and adds all the strings to the trie 
Trie::Trie(const std::string wordList[],int sz){
  root = new Node;
  for(int i = 0; i < sz; i++){
    addWord(wordList[i]);
  }
}

// this function takes a string and adds it to the trie 
void Trie::addWord(const std::string& newWord){
  Node* curr = root;
  for(int i = 0; i < newWord.length(); i++){
    int idx = getIdx(newWord[i]);
    if(curr->children[idx] == NULL){
      curr->children[idx] = new Node;
    }
    curr = curr->children[idx];
  }
  curr->isWord = true;
}

// this function takes a string and returns true if the string is in the trie
bool Trie::lookup(const std::string& word) const{
  Node* curr = root;
  for(int i = 0; i < word.length(); i++){
    int idx = getIdx(word[i]);
    if(curr->children[idx] == NULL){
      return false;
    }
    curr = curr->children[idx];
  }
  return curr->isWord;

}

// this function takes a string and an array of strings and if the string is in the trie, it adds all the words that start with the string to the array and returns the number of words added
int Trie::beginsWith(const std::string& prefix, std::string resultList[]) const{
  // find all words that begin with prefix and store them in resultList in alphabetical order and return the number of words found
  Node* curr = root;
  for(int i = 0; i < prefix.length(); i++){
    int idx = getIdx(prefix[i]);
    if(curr->children[idx] == NULL){
      return 0;
    }
    curr = curr->children[idx];
  }

      int count = 0;
  if(curr->isWord && prefix.length() > 1){
    resultList[count] = prefix;
    count++;
  }
  
  for(int i = 0; i < 26; i++){
    if(curr->children[i] != NULL){
      count += beginsWith(prefix + (char)(i + 'a'), resultList + count);
    }
  }
  return count;
}

// this destructor deletes all the nodes in the trie
Trie::~Trie(){
  delete root;
}
