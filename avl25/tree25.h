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
  void insert(Entry e, tree25Node* root);

  // helper funcs
  void insertNonFull(Entry e);
  void insertMax(Entry e);
  void split(tree25Node* node);
   
  //delete
  void remove(string word);

  //sort
  void sort(string path);

  //range search
  void rangeSearch(string w1, string w2);

 private:
  
  // helper funcs
  void insertNonFull(Entry e);
  void insertMax(Entry e);
  void split(tree25Node* node);

}
