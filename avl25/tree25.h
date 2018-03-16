// tree25.h - defines 2-5 tree implementation
// Mitchell Lewis, 3-10-18

#ifndef TREE25_H
#define TREE25_H

#include <string>

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
  Entry* search(string w, treeNode* x);

  // helper funcs
  void insertNonFull(Entry* e, treeNode* node);
  void splitChild(treeNode* node, int i, treeNode* child);
  void traversal(treeNode* node);
  //delete
  //  void remove(string word);
  treeNode* getRoot();
  
  //sort
  //  void sort(string path);

  //range search
  // void rangeSearch(string w1, string w2);

 private:
  treeNode *root, *np, *x;
};

#endif
