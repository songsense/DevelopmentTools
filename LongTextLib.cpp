//
//  LongTextLib.cpp
//  CrackingCodingInterview
//
//  Created by 宋思明 on 9/24/13.
//  Copyright (c) 2013 宋思明. All rights reserved.
//

#include "LongTextLib.h"

void LongTextLib::book2WordList(vector<string> &wordList) {
  string words(book);
  noPunct(words);
  split(words, ' ', wordList);
}
string &LongTextLib::noSpace(string &s) {
  for (auto c = s.begin(); c != s.end();) {
    if (!isalpha(*c))
      s.erase(c);
    else
      ++c;
  }
  return s;
}
string &LongTextLib::noPunct(string &s) {
  for (auto c = s.begin(); c != s.end();) {
    if (*c == '.' || *c == ',' || *c == '\'' || *c == '\"' ||
        *c == '?' || *c == '!' || *c == '-')
      s.erase(c);
    else
      ++c;
  }
  return s;
}

vector<string> &LongTextLib::split(const string &s, char delim, vector<string> &elems) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

vector<string> LongTextLib::split(const string &s, char delim) {
  vector<string> elems;
  split(s, delim, elems);
  return elems;
}
unordered_set<string> &LongTextLib::getDictFromWordList(unordered_set<string> &dict) {
  dict = dictionary;
  return dict;
}
unordered_set<string> &LongTextLib::setDictFromWordList(unordered_set<string> &dict) {
  maxWordLength = 0;
  for (string word : wordList) {
    dict.insert(word);
    if (word.length() > maxWordLength)
      maxWordLength = word.length();
  }
  return dict;
}