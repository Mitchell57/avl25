// tree25Node.cpp - implementation the 2-5 tree node methods
// Mitchell Lewis, 3-10-18

#include <string>

using namespace std;

// Constructor & Destructor
tree25Node::tree25Node(Entry eArr[], int n, tree25Node* parent1){
  Entry nullEntry = new Entry("", 0);
  parent = parent1;
  
}
 
tree25Node::~tree25Node(){

}

void tree25Node::add(Entry e){

}

void tree25Node::remove(Entry e){

}

void tree25Node::addChild(Entry e, tree25Node& child){

}

tree25Node* tree25Node::getParent(){
  return parent;
}
