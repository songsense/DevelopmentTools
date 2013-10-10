//
//  Tools.cpp
//  CrackingCodingInterview
//
//  Created by 宋思明 on 6/29/13.
//  Copyright (c) 2013 宋思明. All rights reserved.
//

#include "Tools.h"
TrieNode::~TrieNode() {
  for(TrieNode *p : next) {
    if (p != nullptr)
      delete p;
  }
}
TrieNode *TrieNode::GetNextNode (const char &character) {
  return next[character - 97];
}

// Build Trie accoding to word list
void Trie::BuildTrie(const vector<string> &wordList) {
  for (string word : wordList) {
    AddWord(word);
    curNode = &root;
  }
}
// Add a word to the Trie
void Trie::AddWord(const string &word, const size_t &pos) {
  if (word.empty())
    return;
  char c(tolower(word[pos]));
  TrieNode *nextNode = curNode->GetNextNode(c);
  if (nextNode == nullptr) {
    nextNode = curNode->SetNextNode(c, new TrieNode(c, "", false, false));
    curNode->SetNodeHasChild();
  }
  if (pos == word.size() - 1) {
    nextNode->SetNodeIsWord(word);
  }
  else {
    curNode = nextNode;
    AddWord(word, pos + 1);
  }
}
void Trie::AddWord(const string &word) {
  curNode = &root;
  AddWord(word, 0);
}
// return true if a word is found
bool Trie::ReadNextChar(const char &c, bool &longerWord, bool &isExist) {
  TrieNode *node = curNode->GetNextNode(c);
  longerWord = false;
  if (node == nullptr) {
    isExist = false;
    return false;
  }
  isExist = true;
  curNode = node;  
  if (node->GetNodeHasChild())
    longerWord = true;
  if (node->GetNodeIsWord()) {
    return true;
  }
  else {
    return false;
  }
}
bool Trie::Search(const string &str) {
  bool moreWord(false), isWord(false), isExist(false);
  Reset2Root();
  for (size_t pos = 0; pos < str.length(); ++pos){
    char c(tolower(str[pos]));
    if (!isalpha(c)) {
      return false;
    }
    isWord = ReadNextChar(c, moreWord,isExist);
    if (pos == str.length() - 1)
      return isWord;
  }
  return false;
}

// start over
void Trie::Reset2Root() {
  curNode = &root;
}