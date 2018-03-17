// tree25.cpp - implementation of 2-5 Tree
// Mitchell Lewis, 3-10-18

#include <string>
#include <iostream>
#include "entry.h"
#include "tree25.h"

using namespace std;

tree25::treeNode* tree25::nodeInit(){
    tree25::treeNode* newNode = new tree25::treeNode;
    newNode->n = 0;
    newNode->children = new tree25::treeNode*[5];
    newNode->entries = new Entry[4];
    newNode->entries[0] = Entry();
    newNode->leaf = true;
    return newNode;
  }

tree25::treeNode *root, *x, *np; 


tree25::tree25(){
    root = nodeInit();
    
  }

//~tree25();

void tree25::insert(string w){
  Entry* result = searchForInsert(w, root);
  if(result != NULL){
    result->countUp();
    return;
  }
  Entry* e = new Entry(w, 1);
  traversal(root);
  tree25::treeNode* r = root;
  if(root->n >= 4){
    tree25::treeNode* newRoot = nodeInit();
    root = newRoot;
    newRoot->leaf = false;
    newRoot->n = 0;
    newRoot->children[0] = r;
    splitChild(root, 0, r);
    insertNonFull(e, root);
  }
  else{
    insertNonFull(e, root);
  }
}

Entry* tree25::searchForInsert(string w, tree25::treeNode* x){
  int i=0;
  while(i<=x->n && w.compare(x->entries[i].getWord()) == 1){
    i++;
  }
  if(i <= x->n && w.compare(x->entries[i].getWord()) == 0){
    return &(x->entries[i]);
  }
  if(x->leaf){
    return NULL;
  }
  else{
    return searchForInsert(w, x->children[i]);
  }
}

bool tree25::search(string w, tree25::treeNode* x){
  int i=0;
  while(i<=x->n && w.compare(x->entries[i].getWord()) == 1){
    i++;
  }
  if(i <= x->n && w.compare(x->entries[i].getWord()) == 0){
    return true;
  }
  if(x->leaf){
    return false;
  }
  else{
    return search(w, x->children[i]);
  }
}

//void remove(string word);

//void sort(string path);

//void rangeSearch(string w1, string w2);

void tree25::insertNonFull(Entry* e, tree25::treeNode* node){
  int i = node->n;
  if(node->leaf){ 
    while(i >= 1 &&
	  (e->getWord().compare(node->entries[i].getWord()) == -1 || node->entries[i].getWord().length()<1)
	 ){
      if( !(e->getWord().compare(node->entries[i-1].getWord()) == -1) ) break;
      node->entries[i] = node->entries[i-1];
      node->children[i] = node->children[i-1];
      i--;
     
    }
    Entry e1 = Entry(e->getWord(), e->getCount());
    node->entries[i] = e1;
    node->n++;
  }
  else{
    while(i >= 1 &&
	  (e->getWord().compare(node->entries[i].getWord()) == -1 || node->entries[i].getWord().length()<1)
	   ){
      i --;
    }
    if(node->children[i]->n == 4){
      splitChild(node, i, node->children[i]);
      if(e->getWord().compare(node->entries[i].getWord()) == 1){
	i++;
      }
    }
    insertNonFull(e, node->children[i]);
    
  }
  
}

void tree25::splitChild(tree25::treeNode* node, int index, tree25::treeNode* child ){
  tree25::treeNode* child2 = nodeInit();
  child2->parent = node;
  child2->leaf = child->leaf;
  child2->n = 2;
  for(int j=2; j<4; j++){
    child2->entries[j-2] = child->entries[j];
    child->entries[j] = Entry();
  }
  if(!child->leaf){
    for(int j=2; j<5; j++){
      child2->children[j-2] = child->children[j];
      child->children[j] = NULL;
    }
  }
  child->n = 1;
  for(int j=node->n+1; j>=index+1; j--){
    node->children[j+1] = node->children[j];
  }
  node->children[index+1] = child2;
  for(int j=node->n-1; j>=index; j--){
    node->entries[j+1] = node->entries[j];
  }
  node->entries[index] = child->entries[1];
  child->entries[1] = Entry();
  node->n += 1;
}

tree25::treeNode* getRoot(){
  return root;
}

void tree25::traversal(tree25::treeNode* node){
  int i;
  if(node != NULL) {
    for(i=0; i<node->n; i++){
      traversal(node->children[i]);
      cout << node->entries[i].getWord() << " ";
    }
    traversal(node->children[i]);
    cout << endl;
  }
}

  int main() {
    tree25* testTree = new tree25();
    testTree->insert("apple");
    testTree->insert("boy");
    testTree->insert("dog");
    testTree->insert("cat");
    testTree->insert("airplane");

    testTree->traversal(root);
    
    testTree->insert("fish");
    testTree->insert("captain");
    testTree->insert("weed");
    testTree->insert("long");
    testTree->insert("words");

    testTree->traversal(getRoot());

  }

  
