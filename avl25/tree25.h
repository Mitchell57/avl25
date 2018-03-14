// tree25.h - defines 2-5 tree implementation
// Mitchell Lewis, 3-10-18

#ifndef TREE25_H
#define TREE25_H

#include <string>

using namespace std;

class tree25 {

 public:

  //Contstructor and Destructor
  tree25();

  ~tree25();

  //insert
  void insert(string word);

  //delete
  void remove(string word);

  //sort
  void sort(string path);

  //range search
  void rangeSearch(string w1, string w2);

}
