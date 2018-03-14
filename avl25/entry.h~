
// HashEntry.h - defines hash table node structure
// Mitchell Lewis, 2-8-18

#ifndef HASHENTRY_H
#define HASHENTRY_H

#include <string>

using namespace std;

class HashEntry {
 public:

  
  // constructor
  HashEntry(string w, int c) {
    this->word = w;
    this->count = c;
  }

  //get funcs
  string getWord(){
    return word;
  }

  int getCount(){
    return count;
  }

  // functions to increment and decrement count
  void countUp(){ count += 1; }
  void countDown(){ count -= 1; }
  
 private:
  string word;
  int count;
  

};

#endif
