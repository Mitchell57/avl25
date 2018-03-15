// tree25Node.h - defines the 2-5 tree node structure
// Mitchell Lewis, 3-10-18

#ifndef TREE25NODE_H
#define TREE25NODE_H

#include <string>

using namespace std;

class tree25Node {


  
 public:

  // Constructor & Destructor
  tree25Node();
  ~tree25Node();

  void add(Entry e);
  void remove(Entry e);
  void addChild(Entry e, tree25Node& child);
  
 private:

  int data[];
  tree25Node* children[];
  tree25Node* parent;
  int n; // Number of Entries
  boolean leaf;
  
};

#endif
