// tree25.cpp - implementation of 2-5 Tree
// Mitchell Lewis, 3-10-18

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
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
    insertNonFull(w, root);
  }
  else{
    insertNonFull(w, root);
  }
}

void tree25::remove(string w, tree25::treeNode* x){
  int i = 0;
  while (i < x->n && w.compare(x->entries[i].getWord()) > 0){
    i++;
  }
  if (i <= x->n && w.compare(x->entries[i].getWord()) == 0){
    if (x->entries[i].getCount() > 1){
      x->entries[i].countDown();
    }
    if (x->leaf && x->n > 1){
      x->entries[i] = Entry();
      for (int j = i; j < x->n-1; j++){
	x->entries[j] = x->entries[j+1];
      }
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
      for (int j = i; j < x->n-1; j++){
	x->entries[i] = x->entries[i+1];
	x->children[i+1] = x->children[i+2];
      }
      x->n--;
      remove(w, x->children[i]);
    }
  }
  else{
    if (!x->leaf){
      if (x->children[i]->n > 1){
	remove(w, x->children[i]);
      }
      else{
	int ls = 0;
	for (int j = 0; j <= x->n; j++){
	  if (x->children[j]->n > 1 && (i-j == -1 || i-j == 1)){
	    ls = j-i;
	  }
	}
	if (ls != 0){
	  if (ls == -1){
	    x->children[i]->entries[1] = x->children[i]->entries[0];
	    x->children[i]->entries[0] = x->entries[i+ls];
	    x->entries[i+ls] = x->children[i+ls]->entries[x->children[i+ls]->n-1];
	    x->children[i+ls]->entries[x->children[i+ls]->n-1] = Entry();
	    for (int j = x->children[i]->n+1; j < 0; j--){
	      x->children[i]->children[j] = x->children[i]->children[j-1];
	    }
	    x->children[i]->children[0] = x->children[i+ls]->children[x->children[i+ls]->n];
	  }
	  else{
	    x->children[i]->entries[1] = x->entries[i];
	    x->entries[i] = x->children[i+ls]->entries[0];
	    x->children[i]->children[2] = x->children[i+ls]->children[0];
	    for (int j = 0; j < x->children[i+ls]->n-1; j++){
	      x->children[i+ls]->entries[j] = x->children[i+ls]->entries[j+1];
	      x->children[i+ls]->children[j] = x->children[i+ls]->children[j+1];
	    }
	    x->children[i+ls]->children[x->children[i+ls]->n] = x->children[i+ls]->children[x->children[i+ls]->n+1];
	  }
	  x->children[i]->n++;
	  x->children[i+ls]->n--;
	  remove(w, x->children[i]);
	}
	else{
	  if (i > 1){
	    x->children[i]->entries[2] = x->children[i]->entries[0];
	    x->children[i]->entries[1] = x->entries[i];
	    x->children[i]->entries[0] = x->children[i-1]->entries[x->children[i-1]->n-1];
	    x->children[i-1] = NULL; 
	    x->children[i]->n = 3;
	    for (int j = i; j < x->n-1; j++){
	      x->entries[i] = x->entries[i+1];
	      x->children[i+1] = x->children[i+2];
	    }
	    x->n--;
	    remove(w, x->children[i]);
	  }
	  else{
            x->children[i]->entries[1] = x->entries[i];
            x->children[i]->entries[2] = x->children[i+1]->entries[x->children[i+1]->n-1];
            x->children[i+1] = NULL;
            x->children[i]->n = 3;
	    for (int j = i; j < x->n-1; j++){
	      x->entries[i] = x->entries[i+1];
	      x->children[i+1] = x->children[i+2];
	    }
            x->n--;
            remove(w, x->children[i]);
	  }
	}
      }
    }
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

bool tree25::searchHelper(string w, tree25::treeNode* x){
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
    return searchHelper(w, x->children[i]);
  }
}

bool tree25::search(string w){
  return searchHelper(w, root);
}

void tree25::sort(string path){
  vector<string> sortedWords;
  traversal(root, &sortedWords);

  ofstream wordsFile;
  wordsFile.open(path);
    
  for(unsigned int i=0; i<sortedWords.size(); i++){
    wordsFile << sortedWords.at(i) << endl;
  }
  wordsFile << endl;
  wordsFile.close();
}
/*
void rangeSearch(string w1, string w2){
  Entry* start = search(w1);
  vector<string> rangeWords;
  if()

 
  traversal(root, &rangeWords);

  int start = 0;
  int stop = 0
  for(int i)
}
*/
void tree25::insertNonFull(string w, tree25::treeNode* node){
  int i = node->n;
  if(node->leaf){ 
    while(i >= 1 &&
	  (w.compare(node->entries[i].getWord()) < 0 || node->entries[i].getWord().length()<1)
	 ){
      if( !(w.compare(node->entries[i-1].getWord()) < 0) ) break;
      node->entries[i] = node->entries[i-1];
      node->children[i] = node->children[i-1];
      i--;
     
    }
    Entry e = Entry(w, 1);
    node->entries[i] = e;
    node->n++;
  }
  else{
    while(i >= 1 &&
	  w.compare(node->entries[i-1].getWord()) < 0)
    {
      i--;
    }
    if(node->children[i]->n == 4){
      splitChild(node, i, node->children[i]);
      if(w.compare(node->entries[i].getWord()) > 0){
	i++;
      }
    }
    insertNonFull(w, node->children[i]);
    
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

void tree25::rangeSearch(string w1, string w2,tree25::treeNode* node){
  int i;
  if(!node->leaf) {
    for(i=0; i<node->n; i++){
      rangeSearch(w1, w2,node->children[i]);
      if (w1.compare(node->entries[i].getWord()) <= 0 && w2.compare(node->entries[i].getWord()) >= 0){
	cout << node->entries[i].getWord() << endl;
      }
    }
    rangeSearch(w1, w2, node->children[i]);
  }
  else{
    for (i = 0; i<node->n; i++){
      if (w1.compare(node->entries[i].getWord()) <= 0 && w2.compare(node->entries[i].getWord()) >= 0){
	cout << node->entries[i].getWord() << endl;
      }
    }
  }
}


void tree25::traversal(tree25::treeNode* node, vector<string>* v){
  int i;
  if(!node->leaf) {
    for(i=0; i<node->n; i++){
      traversal(node->children[i], v);
      v->push_back(node->entries[i].getWord());
    }
    traversal(node->children[i], v);
  }
  else{
    for (i = 0; i<node->n; i++){
      v->push_back(node->entries[i].getWord());
    }
  }
}
