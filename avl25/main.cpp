// main.cpp - Testing and Time-checking of BST and Hash Table implementations
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
#include "HashTable.h"

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
void parse_text(const string& name, vector<string>* v){
  ifstream inFile(name);
  string str;

  while(inFile >> str){
     vector<string> stopwords = {"a", "about", "above", "above", "across", "after", "afterwards", "again", "against", "all", "almost", "alone", "along", "already", "also","although","always","am","among", "amongst", "amoungst", "amount",  "an", "and", "another", "any","anyhow","anyone","anything","anyway", "anywhere", "are", "around", "as",  "at", "back","be","became", "because","become","becomes", "becoming", "been", "before", "beforehand", "behind", "being", "below", "beside", "besides", "between", "beyond", "bill", "both", "bottom","but", "by", "call", "can", "cannot", "cant", "co", "con", "could", "couldnt", "cry", "de", "describe", "detail", "do", "done", "down", "due", "during", "each", "eg", "eight", "either", "eleven","else", "elsewhere", "empty", "enough", "etc", "even", "ever", "every", "everyone", "everything", "everywhere", "except", "few", "fifteen", "fify", "fill", "find", "fire", "first", "five", "for", "former", "formerly", "forty", "found", "four", "from", "front", "full", "further", "get", "give", "go", "had", "has", "hasnt", "have", "he", "hence", "her", "here", "hereafter", "hereby", "herein", "hereupon", "hers", "herself", "him", "himself", "his", "how", "however", "hundred", "ie", "if", "in", "inc", "indeed", "interest", "into", "is", "it", "its", "itself", "keep", "last", "latter", "latterly", "least", "less", "ltd", "made", "many", "may", "me", "meanwhile", "might", "mill", "mine", "more", "moreover", "most", "mostly", "move", "much", "must", "my", "myself", "name", "namely", "neither", "never", "nevertheless", "next", "nine", "no", "nobody", "none", "noone", "nor", "not", "nothing", "now", "nowhere", "of", "off", "often", "on", "once", "one", "only", "onto", "or", "other", "others", "otherwise", "our", "ours", "ourselves", "out", "over", "own","part", "per", "perhaps", "please", "put", "rather", "re", "same", "see", "seem", "seemed", "seeming", "seems", "serious", "several", "she", "should", "show", "side", "since", "sincere", "six", "sixty", "so", "some", "somehow", "someone", "something", "sometime", "sometimes", "somewhere", "still", "such", "system", "take", "ten", "than", "that", "the", "their", "them", "themselves", "then", "thence", "there", "thereafter", "thereby", "therefore", "therein", "thereupon", "these", "they", "thickv", "thin", "third", "this", "those", "though", "three", "through", "throughout", "thru", "thus", "to", "together", "too", "top", "toward", "towards", "twelve", "twenty", "two", "un", "under", "until", "up", "upon", "us", "very", "via", "was", "we", "well", "were", "what", "whatever", "when", "whence", "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "whereupon", "wherever", "whether", "which", "while", "whither", "who", "whoever", "whole", "whom", "whose", "why", "will", "with", "within", "without", "would", "yet", "you", "your", "yours", "yourself", "yourselves", "the"};
    
    bool all_alpha  = std::regex_match(str, std::regex("^[A-Za-z']+$"));
    bool not_stopword = true;
    for(int i=0; str[i]; i++) str[i] = tolower(str[i]);

    for(unsigned int i=0; i<stopwords.size(); i++){
      if(str.compare(stopwords.at(i)) == 0){
	not_stopword = false;
	break;
      }
    }
    if(all_alpha && not_stopword)
      v->push_back(str);
  }

  inFile.close();
}

int main(){

  //Text parsing
  vector<string> filenames, dirnames;
  string root = "hotels";

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

  // parses the text from each filename found and adds eligible words to list
  vector<string> words;
  for(unsigned int i = 0; i<filenames.size(); i++){
    parse_text(filenames.at(i), &words);
  }

  //initializes HashTable and inserts all words from list
  HashTable* ht = new HashTable(words.size());
  for(unsigned int i = 0; i<words.size(); i++){
    ht->insert(words.at(i));
  }

  /* Timing template
	  auto start = std::chrono::high_resolution_clock::now();
          METHOD HERE
          auto stop = std::chrono::high_resolution_clock::now();

	  std::chrono::duration<double, std::milli> execTime = stop - start;
	  cout << "Hash/BST: " << execTime.count() << endl;
  */

  // Timing tests - sorts words, then grabs 100 words to test times
  ht->sort("sorted.txt");
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
    ht->search(testSet.at(i));
  }
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> execTime = stop - start;
  cout << "Hash search time: " << execTime.count() << endl;

  //Insert Test
  start = std::chrono::high_resolution_clock::now();
  for(unsigned int i=0; i<testSet.size(); i++){
    ht->insert(testSet.at(i));
  }
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "Hash insert time: " << execTime.count() << endl;

  //Delete test
  start = std::chrono::high_resolution_clock::now();
  for(unsigned int i=0; i<testSet.size(); i++){
    ht->remove(testSet.at(i));
  }
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "Hash delete time: " << execTime.count() << endl;

  //Sort Test
  start = std::chrono::high_resolution_clock::now();
  ht->sort("sorted.txt");
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "Hash sort time: " << execTime.count() << endl;

  //Range Search for 10, 100, and 1000 words
  // Used sorted output file to choose increments of 10, 100, and 1000 words
  start = std::chrono::high_resolution_clock::now();
  ht->rangeSearch("annual", "answers");
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "Hash range search (n=10): " << execTime.count() << endl;

  start = std::chrono::high_resolution_clock::now();
  ht->rangeSearch("annual", "applied");
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "Hash range search (n=100): " << execTime.count() << endl;

  start = std::chrono::high_resolution_clock::now();
  ht->rangeSearch("annual", "breezy");
  stop = std::chrono::high_resolution_clock::now();
  execTime = stop - start;
  cout << "Hash range search (n=1000): " << execTime.count() << endl;
  
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
          int result = ht->search(w);
          auto stop = std::chrono::high_resolution_clock::now();

	  std::chrono::duration<double, std::milli> execTime = stop - start;
	  if(result == -1)
	    cout << "false" << endl;
	  else
	    cout << "true" << endl;
	  cout << "Hash: " << execTime.count() << endl;
	  break;
	}
	
      //insert
      case 2:
	{
	  cin >> w;
          auto start = std::chrono::high_resolution_clock::now();
          ht->insert(w);
          auto stop = std::chrono::high_resolution_clock::now();

          std::chrono::duration<double, std::milli> execTime = stop - start;
	  cout << "Hash: " << execTime.count() << endl;
	  break;
	}

      //remove
      case 3:
	{
	  cin >> w;
	  auto start = std::chrono::high_resolution_clock::now();
	  ht->remove(w);
	  auto stop = std::chrono::high_resolution_clock::now();

	  std::chrono::duration<double, std::milli> execTime = stop - start;
	  cout << "Hash: " << execTime.count() << endl;
	  break;
	}

      //sort
      case 4:
	{
	  cin >> w;
	  auto start = std::chrono::high_resolution_clock::now();
	  ht->sort(w);
	  auto stop = std::chrono::high_resolution_clock::now();

	  std::chrono::duration<double, std::milli> execTime = stop - start;
	  cout << "Hash: " << execTime.count() << endl;
	  break;
	}

      //range search
    case 5:
      {
        string w2;
	cin >> w;
	cin >> w2;
	auto start = std::chrono::high_resolution_clock::now();
	ht->rangeSearch(w, w2);
	auto stop = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> execTime = stop-start;
	cout << "Hash: " << execTime.count() << endl;
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


