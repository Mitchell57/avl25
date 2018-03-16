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

  // parses the text from each filename found and adds eligible words to list
  vector<string> words;
  for(unsigned int i = 0; i<filenames.size(); i++){
    parse_text(filenames.at(i), &words, &stopwords);
  }
  cout << "Parsed text";
  for(std::string element : stopwords){
    cout << element << ": stopword \n";
  }
  //initializes trees and inserts all words from list
  //INIT HERE
  for(unsigned int i = 0; i<words.size(); i++){
    //INSERT HERE
  }

  /* Timing template
	  auto start = std::chrono::high_resolution_clock::now();
          METHOD HERE
          auto stop = std::chrono::high_resolution_clock::now();

	  std::chrono::duration<double, std::milli> execTime = stop - start;
	  cout << "Hash/BST: " << execTime.count() << endl;
  */

  // Timing tests - sorts words, then grabs 100 words to test times
  ifstream inFile("stopwords.txt");
  vector<string> testSet;
  string str;
  while(testSet.size() <= 100 && inFile >> str){
    testSet.push_back(str);
  }
  cout << "# of test words: " << testSet.size() << endl;

  // Search test
  auto start = std::chrono::high_resolution_clock::now();
  for(unsigned int i=0; i<testSet.size(); i++){
    //SEARCH HERE
  }
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> execTime = stop - start;
  cout << "2-5 search time: " << execTime.count() << endl;

  //Insert Test
  start = std::chrono::high_resolution_clock::now();
  for(unsigned int i=0; i<testSet.size(); i++){
    // INSERT HERE
  }
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "2-5 insert time: " << execTime.count() << endl;

  //Delete test
  start = std::chrono::high_resolution_clock::now();
  for(unsigned int i=0; i<testSet.size(); i++){
    // DELETE HERE
  }
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "2-5 delete time: " << execTime.count() << endl;

  //Sort Test
  start = std::chrono::high_resolution_clock::now();
  //ht->sort("sorted.txt");
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "2-5 sort time: " << execTime.count() << endl;

  //Range Search for 10, 100, and 1000 words
  // Used sorted output file to choose increments of 10, 100, and 1000 words
  start = std::chrono::high_resolution_clock::now();
  //ht->rangeSearch("annual", "answers");
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "2-5 range search (n=10): " << execTime.count() << endl;

  start = std::chrono::high_resolution_clock::now();
  //->rangeSearch("annual", "applied");
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "2-5 range search (n=100): " << execTime.count() << endl;

  start = std::chrono::high_resolution_clock::now();
  //ht->rangeSearch("annual", "breezy");
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "2-5 range search (n=1000): " << execTime.count() << endl;
  
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
		int result = 0; //ht->search(w);
	    auto stop = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> execTime = stop - start;
		if(result == 0)
		    cout << "false" << endl;
		else
		    cout << "true" << endl;
		cout << "2-5: " << execTime.count() << endl;
		break;
	}
	
      //insert
      case 2:
	{
	    cin >> w;
        auto start = std::chrono::high_resolution_clock::now();
        //ht->insert(w);
        auto stop = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> execTime = stop - start;
	    cout << "2-5: " << execTime.count() << endl;
	    break;
	}

      //remove
      case 3:
	{
	    cin >> w;
	    auto start = std::chrono::high_resolution_clock::now();
	    //ht->remove(w);
	    auto stop = std::chrono::high_resolution_clock::now();

	    std::chrono::duration<double, std::milli> execTime = stop - start;
	    cout << "2-5: " << execTime.count() << endl;
	    break;
	}

      //sort
      case 4:
	{
		cin >> w;
	    auto start = std::chrono::high_resolution_clock::now();
  	    //ht->sort(w);
		auto stop = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> execTime = stop - start;
		cout << "2-5: " << execTime.count() << endl;
	    break;
	}

      //range search
    case 5:
      {
        string w2;
		cin >> w;
		cin >> w2;
		auto start = std::chrono::high_resolution_clock::now();
		//ht->rangeSearch(w, w2);
		auto stop = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> execTime = stop-start;
		cout << "2-5: " << execTime.count() << endl;
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


