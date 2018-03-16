// tree25.cpp - implementation of 2-5 Tree
// Mitchell Lewis, 3-10-18

#include <string>

using namespace std;

  struct treeNode{
    Entry* entries[4];
    treeNode** children[5];
    treeNode* parent;
    bool leaf;
    int n; // Current # of entries
  };

treeNode* nodeInit(Entry e, treeNode* child, treeNode* parent){
    treeNode* newNode = new treeNode;
    newNode->entries[0] = e;
    newNode->children[0] = child;
    newNode->leaf = child == NULL;
    newNode->n = 1;
    newNode->children = new treeNode*[5];
    return newNode;
  }

treeNode *root, *x, *np; 
  tree25(){
    root = nodeInit();
    
  }

~tree25();

void insert(String w, tree25Node* root){
  Entry* search = search(w, root);
  if(search != NULL){
    search->countUp();
    return;
  }
  Entry e = new Entry(w, 1);
  
  treeNode* r = root;
  if(root->n >= 4){
    treeNode* newRoot = new treeNode;
    root = newRoot;
    newRoot->leaf = false;
    newRoot->n = 0;
    newRoot->children[0] = r;
    splitChild(root, 1, r);
    insertNonfull(root, w)
  }
}

Entry* search(String w, treeNode* x){
  int i=0;
  while(i<=x->n && w.compare(x->entries[i].getWord()) == 1){
    i++;
  }
  if(i <= x->n && w.compare(x->entries[i].getWord()) == 0){
    return 1;
  }
  if(x->leaf){
    return 0;
  }
  else{
    return search(w, x->children[i]);
  }
}

void remove(string word);

void sort(string path);

void rangeSearch(string w1, string w2);

void insertNonFull(Entry e, treeNode* node){
  int i = node->n;
  if(node->leaf){ 
    while(i >= 1 && e.getWord().compare(node->entries[i].getWord()) == -1){
      node->entries[i+1] = node->entries[i];
      node->children[i+1] = node->children[i];
      i--;
    }
    node->entries[i+1] = e;
    node->n++;
  }
  else{
    while(i >= 1 && e.getWord().compare(node->entries[i].getWord() == -1)){
      i --;
    }
    i++;
    if(node->children[i]->n == 5){
      splitChild(node, i, node->children[i]);
      if(e.getWord().compare(node->entries[i].getWord()) == 1){
	i++;
      }
    }
    insertNonFull(e, node->children[i]);)
    
  }
  
}
void insertMax(Entry e);
void splitChild(tree25Node* node, int index, treeNode* child ){
  treeNode* child2 = nodeInit();
}

