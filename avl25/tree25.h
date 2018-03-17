// tree25.h - defines 2-5 tree implementation
// Mitchell Lewis, 3-10-18

#ifndef TREE25_H
#define TREE25_H

#include <string>
#include "entry.h"

using namespace std;

class tree25 {

 public:
    struct treeNode{
      Entry* entries;
      treeNode** children;
      treeNode* parent;
      bool leaf;
      int n;
    };
  //Contstructor and Destructor
  tree25();

  ~tree25();

  //insert
  void insert(string w);
  
  treeNode* nodeInit();
  bool search(string w);
  bool searchHelper(string w, treeNode* x);
  Entry* searchForInsert(string w, treeNode* x);
  // helper funcs
  void insertNonFull(string w, treeNode* node);
  void splitChild(treeNode* node, int i, treeNode* child);
  void traversal(treeNode* node, vector<string>* v);
  //delete
  void remove(string word, treeNode* x);
  treeNode* getRoot();
  treeNode* getParent(treeNode* c, treeNode* x);
  void transfer(treeNode* x, int i);
  void fuse(treeNode* x, int i);
  //sort
  void sort(string path);

  //range search
  void rangeSearch(string w1, string w2, treeNode* node);

 private:
  treeNode *root, *np, *x;
};

#endif
