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

void tree25::remove(string w, tree25::treeNode* x){
  int i = 0;
  while (i <= x->n && w.compare(x->entries[i].getWord()) > 0){
    i++;
  }
  if (i <= x->n && w.compare(x->entries[i].getWord()) == 0){
    if (x->entries[i].getCount() > 1){
      x->entries[i].countDown();
    }
    if (x->leaf && x->n > 1){
      x->entries[i] = Entry();
      x->n--;
    }
    else if (x->children[i]->n > 1){
      Entry temp = x->entries[i];
      x->entries[i] =  x->children[i]->entries[0];
      x->children[i]->entries[0] = temp;
      remove(w, x->children[i]);
    }
    else if (x->children[i+1]->n > 1){
      Entry temp = x->entries[i];
      x->entries[i] =  x->children[i+1]->entries[x->children[i+1]->n-1];
      x->children[i+1]->entries[x->children[i+1]->n-1] = temp;
      remove(w, x->children[i]);
    }
    else{
      x->children[i]->entries[1] = x->entries[i];
      x->children[i]->entries[2] = x->children[i+1]->entries[0];
      x->children[i+1] = NULL;
      x->children[i]->n = 3;
      x->n--;
      remove(w, x->children[i]);
    }
  }
  else{
    if (x->children[i]->n > 1){
      remove(w, x->children[i]);
    }
    else{
      int ls = 1;
      int lS = 0;
      for (int j = 0; j < 5; j++){
	if (x->children[j]->n > ls){
	  ls = x->children[j]->n;
	  lS = j;
	}
      }
      if (ls > 1){
	x->children[i]->entries[1] = x->entries[i];
	x->entries[i] = x->children[lS]->entries[x->children[lS]->n-1];
	x->children[i]->children[2] = x->children[lS]->children[x->children[lS]->n];
	x->children[i]->n++;
	x->children[lS]->n--;
	remove(w, x->children[i]);
      }
      else{
	x->children[i]->entries[1] = x->entries[i];
	x->children[i]->entries[2] = x->children[lS]->entries[x->children[lS]->n-1];
	x->children[lS] = NULL;
	x->children[i]->n = 3;
	x->n--;
	remove(w, x->children[i]);
      }
    }
  }
}

tree25::treeNode* tree25::getParent(tree25::treeNode* c, tree25::treeNode* x){
  for (int i = 0; i < 5; i++){
    if (x->children[i] == c){
      return x;
    }
  }
  int i	= 0;
  while	(i <= x->n && (c->entries[0].getWord()).compare(x->entries[i].getWord()) == 1){
    i++;
  }
  if (x->leaf){
    return NULL;
  }
  else{
    return getParent(c, x->children[i]);
  }
}


Entry* tree25::searchForInsert(string w, tree25::treeNode* x){
  int i=0;
  while(i<x->n && w.compare(x->entries[i].getWord()) > 0){
    i++;
  }
  if(i < x->n && w.compare(x->entries[i].getWord()) == 0){
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
  while(i<x->n && w.compare(x->entries[i].getWord()) > 0){
    i++;
  }
  if(i < x->n && w.compare(x->entries[i].getWord()) == 0){
    return true;
  }
  if(x->leaf){
    return false;
  }
  else{
    return search(w, x->children[i]);
  }
}

//void sort(string path);

//void rangeSearch(string w1, string w2);

void tree25::insertNonFull(Entry* e, tree25::treeNode* node){
  int i = node->n;
  if(node->leaf){ 
    while(i >= 1 &&
	  (e->getWord().compare(node->entries[i].getWord()) < 0 || node->entries[i].getWord().length()<1)
	 ){
      if( !(e->getWord().compare(node->entries[i-1].getWord()) < 0) ) break;
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
	  e->getWord().compare(node->entries[i-1].getWord()) < 0)
    {
      i--;
    }
    if(node->children[i]->n == 4){
      splitChild(node, i, node->children[i]);
      if(e->getWord().compare(node->entries[i].getWord()) > 0){
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

tree25::treeNode* tree25::getRoot(){
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
    cout << endl << endl;
  }
  else{
  }
}

  int main() {
    tree25* testTree = new tree25();
    testTree->insert("apple");
    testTree->insert("boy");
    testTree->insert("dog");
    testTree->insert("cat");
    testTree->insert("airplane");

    //testTree->traversal(tree25::root);
    
    testTree->insert("fish");
    testTree->insert("captain");
    testTree->insert("weed");
    testTree->insert("long");
    testTree->insert("words");

    testTree->traversal(testTree->getRoot());

  }

  
