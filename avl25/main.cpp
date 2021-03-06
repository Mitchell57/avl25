// main.cpp - Testing and Time-checking of AVL and 2-5 tree implementations
// Mitchell Lewis, Sean Costello

#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <chrono>
#include <regex>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include "AVL.h"
#include "tree25.h"
#include "entry.h"

using namespace std;

// Read_directory - writes filenames inside a given directory to a string vector
void read_directory(const string& name, vector<string>* v){
  DIR* dirp = opendir(name.c_str());
  struct dirent * dp;
  while((dp = readdir(dirp)) != NULL){
    // adds name of entry to list as long as it does not start with a '.'
    if((dp->d_name)[0] != '.'){
      v->push_back(dp->d_name);
    }
  }
  closedir(dirp);
}

// Parse_text - Takes a pathname and vector address, and adds words to vector from file as long as they are
// alphabetical and do not match any of the stopwords
void parse_text(const string& name, vector<string>* v, unordered_set<string>* stopwords ){
  ifstream inFile(name);
  string str;

  while(inFile >> str){
        
    bool all_alpha  = std::regex_match(str, std::regex("^[A-Za-z']+$"));
    bool stopword = false;
    for(int i=0; str[i]; i++) str[i] = tolower(str[i]);

    if(stopwords->find(str) != stopwords->end()){
		stopword = true;
    }
    
    if(all_alpha && !stopword)
      v->push_back(str);
  }

  inFile.close();
}

int main(){

  //Text parsing
  vector<string> filenames, dirnames;
  string root = "hotels-small";

  // retrieves subdirectory names
  read_directory(root, &dirnames);

  // retrieves filenames inside each subdirectory, then builds the path up to the main dataset folder, then adds
  // to filename list
  for(unsigned int i=0; i<dirnames.size(); i++){
    vector<string> tempFileNames;
    string subdir = root + "/" + dirnames.at(i);
    read_directory(subdir, &tempFileNames);
    for(unsigned int j=0; j<tempFileNames.size(); j++){
      
      string path = subdir + "/" + tempFileNames.at(j);
      filenames.push_back(path);
    }
  }

  // builds map of stopwords for efficient checking
  ifstream inFile2("stopword.txt");
  string sw;
  std::unordered_set<string> stopwords;
  while(inFile2 >> sw){
    stopwords.insert(sw);
  }
  inFile2.close();
  cout << "Parsed stopwords\n";
  
  // parses the text from each filename found and adds eligible words to list
  vector<string> words;
  for(unsigned int i = 0; i<filenames.size(); i++){
    parse_text(filenames.at(i), &words, &stopwords);
  }
  cout << "Parsed text";

  //initializes trees and inserts all words from list
  //INIT HERE
  AVL* a = new AVL;
  tree25* t = new tree25();
  for(unsigned int i = 0; i<words.size(); i++){
    t->insert(words[i]);
    a->head = a->insert(words[i], a->head);
  }

  /* Timing template
	  auto start = std::chrono::high_resolution_clock::now();
          METHOD HERE
          auto stop = std::chrono::high_resolution_clock::now();

	  std::chrono::duration<double, std::milli> execTime = stop - start;
	  cout << "Hash/BST: " << execTime.count() << endl;
  */
  
  // Timing tests - sorts words, then grabs 100 words to test times
  t->sort("sorted.txt");
  ifstream inFile("sorted.txt");
  vector<string> testSet;
  string str;
  while(testSet.size() <= 100 && inFile >> str){
    testSet.push_back(str);
  }
  cout << "# of test words: " << testSet.size() << endl;

  // Search test
  auto start = std::chrono::high_resolution_clock::now();
  for(unsigned int i=0; i<testSet.size(); i++){
    t->search(testSet[i]);
  }
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> execTime = stop - start;
  cout << "2-5 search time: " << execTime.count() << endl;


  start = std::chrono::high_resolution_clock::now();
  for(unsigned int i=0; i<testSet.size(); i++){
    a->search(testSet[i], a->head);
  }
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "AVL search time: " << execTime.count() << endl;
  
  //Insert Test
  start = std::chrono::high_resolution_clock::now();
  for(unsigned int i=0; i<testSet.size(); i++){
    t->insert(testSet[i]);
  }
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "2-5 insert time: " << execTime.count() << endl;

  start = std::chrono::high_resolution_clock::now();
  for(unsigned int i=0; i<testSet.size(); i++){
    a->head = a->insert(testSet[i], a->head);
  }
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "AVL insert time: " << execTime.count() << endl;

  //Delete test
  start = std::chrono::high_resolution_clock::now();
  for(unsigned int i=0; i<testSet.size(); i++){
    // DELETE HERE
  }
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "2-5 delete time: " << execTime.count() << endl;

  start = std::chrono::high_resolution_clock::now();
  for(unsigned int i=0; i<testSet.size(); i++){
    // DELETE HERE
    a->head = a->remove(testSet[i], a->head);
  }
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "AVL delete time: " << execTime.count() << endl;

  //Sort Test
  start = std::chrono::high_resolution_clock::now();
  t->sort("sortTest.txt");
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "2-5 sort time: " << execTime.count() << endl;

  start = std::chrono::high_resolution_clock::now();
  a->sort("sorted.txt", a->head);                                              
  //a->print(a->head);
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "AVL sort time: " << execTime.count() << endl;
  
  //Range Search for 10, 100, and 1000 words
  // Used sorted output file to choose increments of 10, 100, and 1000 words
  start = std::chrono::high_resolution_clock::now();
  t->rangeSearch("annual", "answers", t->getRoot());
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "2-5 range search (n=10): " << execTime.count() << endl;

  start = std::chrono::high_resolution_clock::now();
  t->rangeSearch("annual", "applied", t->getRoot());
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "2-5 range search (n=100): " << execTime.count() << endl;

  start = std::chrono::high_resolution_clock::now();
  t->rangeSearch("annual", "breezy", t->getRoot());
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "2-5 range search (n=1000): " << execTime.count() << endl;

  start = std::chrono::high_resolution_clock::now();
  a->rangeSearch("annual", "answers", a->head);                                           
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "AVL range search (n=10): " << execTime.count() << endl;

  start = std::chrono::high_resolution_clock::now();
  a->rangeSearch("annual", "applied", a->head);                                         
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "AVL range search (n=100): " << execTime.count() << endl;

  start = std::chrono::high_resolution_clock::now();
  a->rangeSearch("annual", "breezy", a->head);      
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "AVL range search (n=1000): " << execTime.count() << endl;
  
  // Test interface - Prompts input for 1-5, performs search, insert, remove, sort, and range search respectively
  while(true){
    ostringstream out;
    int choice;
    string  w;
    cout << "enter 1-5"<< endl;
    cin >> choice;
    switch(choice){

      //search
      case 1:
	{
	  cin >> w;
		auto start = std::chrono::high_resolution_clock::now();
		bool avlSearch = a->search(w, a->head);
		auto stop = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> execTime = stop - start;
		if(avlSearch) cout << "AVL: True\n";
		else cout << "AVL: False\n";
		cout << "AVL: " << execTime.count() << endl;
		
		start = std::chrono::high_resolution_clock::now();
		bool treeSearch = t->search(w);                                           
		stop = std::chrono::high_resolution_clock::now();
		
		execTime = stop - start;
                if(treeSearch) cout << "2-5: True\n";
		else cout << "2-5: False\n";
                cout << "2-5: " << execTime.count() << " ms" << endl;
		break;
	}
	
      //insert
      case 2:
	{
	    cin >> w;
	    auto start = std::chrono::high_resolution_clock::now();
	    a->head = a->insert(w, a->head);
	    auto stop = std::chrono::high_resolution_clock::now();
	    std::chrono::duration<double, std::milli> execTime = stop - start;
	    cout << "AVL: " << execTime.count() << "s" << endl;
	    
	    start = std::chrono::high_resolution_clock::now();
	    t->insert(w);
	    stop = std::chrono::high_resolution_clock::now();
	    execTime = stop - start;
	    cout << "2-5: " << execTime.count() << " ms" << endl;
	    break;
	}

      //remove
      case 3:
	{
	    cin >> w;
	    auto start = std::chrono::high_resolution_clock::now();
	    a->head = a->remove(w, a->head);
	    auto stop = std::chrono::high_resolution_clock::now();
	    std::chrono::duration<double, std::milli> execTime = stop - start;
	    cout << "AVL: " << execTime.count() << "s" << endl;
	    
	    start = std::chrono::high_resolution_clock::now();
	    t->remove(w, t->getRoot());
	    stop = std::chrono::high_resolution_clock::now();
            execTime = stop - start;
            cout << "2-5: " << execTime.count() << "s" << endl;
	    break;
	}

      //sort
      case 4:
	{
		cin >> w;
		auto start = std::chrono::high_resolution_clock::now();
		a->sort(w, a->head);
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> execTime = stop - start;
		cout << "AVL: " << execTime.count() << "s" << endl;

		start = std::chrono::high_resolution_clock::now();
		t->sort(w);
		stop = std::chrono::high_resolution_clock::now();
		execTime = stop - start;
		cout << "2-5: " << execTime.count() << "s" << endl;
	    break;
	}

      //range search
    case 5:
      {
        string w2;
		cin >> w;
		cin >> w2;
		auto start = std::chrono::high_resolution_clock::now();
		a->rangeSearch(w, w2, a->head);
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> execTime = stop-start;
		cout << "AVL: " << execTime.count() << "s" << endl;
		
		start = std::chrono::high_resolution_clock::now();
		t->rangeSearch(w, w2, t->getRoot());
                stop = std::chrono::high_resolution_clock::now();
                execTime = stop - start;
                cout << "2-5: " << execTime.count() << "s" << endl;
		break;
      }
    default:
      {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid input" << endl;
      }
    }
  }
    
  
  return 0;
}


