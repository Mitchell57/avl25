// tree25.cpp - implementation of 2-5 Tree
// Mitchell Lewis, 3-10-18


tree25();

~tree25();

void insert(Entry e, tree25Node* root);

void insertNonFull(Entry e);
void insertMax(Entry e);
void split(tree25Node* node);
   
void remove(string word);

void sort(string path);

void rangeSearch(string w1, string w2);

void insertNonFull(Entry e);
void insertMax(Entry e);
void split(tree25Node* node);