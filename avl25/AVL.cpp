#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include "AVL.h"

using namespace std;

AVL::AVL(){
  head = NULL;
  size = 0;
}

bool AVL::search(string s, Node* head){
  if (head == NULL){
    return false;
  }
  if (s.compare(head->data) == 0){
    return true;
  }
  if (s.compare(head->data) <= 0){
    return false || search(s, head->left);
  }
  else{
    return false || search(s, head->right);
  }
}

Node* AVL::insert(string s,Node* head){
  if (head == NULL){
    Node* n = new Node;
    n->data = s;
    n->right = NULL;
    n->left = NULL;
    n->count = 1;
    size++;
    return n;
  }
  else if (s.compare(head->data) == 0){
    head->count++;
  }
  else if (head->data.compare(s) < 0){
    head->right = insert(s,head->right);
    if (height(head->right) - height(head->left) == 2){
      if (head->right->data.compare(s) < 0){
	head  = rotateRight(head);
      }
      else{
	head = doubleRight(head);
      }
    }
  }
  else{
    head->left = insert(s,head->left);
    if (height(head->right) - height(head->left) == -2){
      if (head->left->data.compare(s) > 0){
	head = rotateLeft(head);
      }
      else{
	head = doubleLeft(head);
      }
    }
  }
  return head;
}

Node* AVL::remove(string s, Node* head){
  if (head == NULL){
    return NULL;
  }
  if (s.compare(head->data) < 0){
    head->left = remove(s, head->left);
  }
  else if (s.compare(head->data) > 0){
    head->right = remove(s, head->right);
  }
  else{
    if (head->count > 1){
      head->count--;
    }
    else{
      size--;
      if (head->left == NULL && head->right == NULL){
	return NULL;
      }
      else if (head->left != NULL && head->right == NULL){
	return head->left;
      }
      else if (head->left == NULL && head->right == NULL){
	return head->right;
      }
      else{
	Node* temp = head->left;
	while (temp->right != NULL){
	  temp = temp->right;
	}
	head->data = temp->data;
	head->left = remove(temp->data, head->left);
      }
    }
  }
  if (height(head->right) - height(head->left) == 2){
    if (head->right->data.compare(s) < 0){
      head  = rotateRight(head);
    }
    else{
      head = doubleRight(head);
    }
  }
  else if (height(head->right) - height(head->left) == -2){
    if (head->left->data.compare(s) > 0){
      head = rotateLeft(head);
    }
    else{
      head = doubleLeft(head);
    }
  }
  return head;
}

Node* AVL::rotateRight(Node* head){
  Node* newHead = head->right;
  head->right = newHead->left;
  newHead->left = head;
  return newHead;
}

Node* AVL::rotateLeft(Node* head){
  Node* newHead = head->left;
  head->left = newHead->right;
  newHead->right = head;
  return newHead;
}

Node* AVL::doubleRight(Node* head){
  head->right = rotateLeft(head->right);
  return rotateRight(head);
}

Node* AVL::doubleLeft(Node* head){
  head->left = rotateRight(head->left);
  return rotateLeft(head);
}

int AVL::height(Node* head){
  if (head == NULL){
    return 1;
  }
  else{
    return max(height(head->left), height(head->right))+1;
  }
}

void AVL::print(Node* head){
  if (head != NULL){
    print(head->left);
    cout << head->data << " ";
    print(head->right);
  }
}

AVL::~AVL(){
  delB(head);
}

void AVL::delB(Node* head){
  if (head != NULL){
    delB(head->left);
    delB(head->right);
    delete head;
  }
}

void AVL::rangeSearch(string s1, string s2, Node* head){
  if (head == NULL){
    return;
  }
  rangeSearch(s1,s2,head->left);
  if (head->data.compare(s1) >= 0 && head->data.compare(s2) <= 0){
    cout << head->data << endl;
  }
  rangeSearch(s1, s2, head->right);
}

void AVL::sort(string path, Node* head){
  ofstream wordsFile;
  wordsFile.open(path);
  string arr [size];
  count = 0;
  sortHelper(arr, head);
  /*
  while (!arr->empty()){
    cout << arr->pop() << endl;
  }
  */
  for (int i = 0; i < size; i++){
    wordsFile << arr[i] << endl;
  }
  wordsFile.close();
}

void AVL::sortHelper(string arr [], Node* head){
  if (head != NULL){
    sortHelper(arr, head->left);
    arr[count] = head->data;
    count++;
    sortHelper(arr, head->right);
  }
}

