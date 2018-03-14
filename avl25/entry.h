
// Entry.h - defines 2-5 tree entry structure
// Mitchell Lewis, 3-10-18

#ifndef ENTRY_H
#define ENTRY_H

#include <string>

using namespace std;

class Entry {
 public:

  
  // constructor
  Entry(string w, int c) {
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
