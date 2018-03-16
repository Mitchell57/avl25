#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct Node{
    string data;
    Node* left;
    Node* right;
    int count;
};


class AVL
{
 public:
  AVL();
  AVL(string data);
  ~AVL();
  void delB(Node* head);
  Node* insert(string s, Node* head);
  Node* remove(string s, Node* head);
  bool search(string s, Node* head);
  void sort(string path, Node* head);
  void sortHelper(string arr [], Node* head);
  void rangeSearch(string s1, string s2, Node* head);
  void print(Node* head);
  int height(Node* height);
  Node* rotateRight(Node* head);
  Node* rotateLeft(Node* head);
  Node* doubleRight(Node* head);
  Node* doubleLeft(Node* head);
  Node* minValue(Node* head);
  Node* maxValue(Node* head);
  Node* head;
  int size;
  int count;
};

#endif
