#include <iostream>
#include <string>
#include <fstream>


using std::cout; using std::endl; using std::string; using std::ifstream;

class WordOccurrence {
public:
    WordOccurrence(const string& word = " ", int num = 0) {
        word_ = word;
        num_ = num;
    }
   bool matchWord(const string& word) {// returns true if word matches stored
        if (word.compare(word_) == 0) {
            return true;
        }
        return false;
    }
   void increment() {// increments number of occurrences
       num_ = num_ + 1;
   }
   
   string getWord() const {
       return word_;
   }
   int getNum() const {
       return num_;
   }

private:
    string word_;
    int num_;
};



class WordList {
public:
    // add copy constructor, destructor, overloaded assignment

    WordList(int size = 0);
    ~WordList();
    WordList(const WordList& list);
    void operator = (const WordList& list);

    // implement comparison as friend
    friend bool equal(const WordList&, const WordList&);

    void addWord(const string&);
    void print();
    void sort();
private:
    WordOccurrence* wordArray_; // a dynamically allocated array of WordOccurrences
    // may or may not be sorted
    int size_;
};

//function definition

//constructor 
WordList::WordList(int size) {
    size_ = size;
    wordArray_ = new WordOccurrence[size];
}

//destructor
WordList::~WordList() {
    delete[] wordArray_;
}

////overloaded assigment
WordList::WordList(const WordList& list) {
    wordArray_ = new WordOccurrence[list.size_];
    for (int i = 0; i < list.size_; ++i){
    
        wordArray_[i] = list.wordArray_[i];
    }
    this->size_ = list.size_;
}

 bool equal(const WordList& list1, const WordList& list2) {
     if (list1.size_ != list2.size_) {
         return false;
     }
         
     for (int i = 0; i < list1.size_; ++i){
     
         for (int i = 0; i <list1.size_; ++i) {
             if (list1.wordArray_[i].getWord() != list2.wordArray_[i].getWord() ||
                 list1.wordArray_[i].getNum() != list2.wordArray_[i].getNum())
                 return false;
         }
     }
     return true;
}

 void WordList::operator = (const WordList& list){
 
     wordArray_ = new WordOccurrence[list.size_];
     for (int i = 0; i < list.size_; ++i){
     
         wordArray_[i] = list.wordArray_[i];
     }
     this->size_ = list.size_;
 }

 void WordList::addWord(const string& word) {
    
     for (int i = 0; i < size_; ++i) {
         if (wordArray_[i].matchWord(word)) {
             wordArray_[i].increment();
             return;
         }
     }
     //creating a new wordOccurence with increased size
     WordOccurrence* tempArray = new WordOccurrence[size_ + 1];
     for (int i = 0; i < size_; ++i) {
         tempArray[i] = wordArray_[i];
     }
     //delete old array
     delete[] wordArray_;
     wordArray_ = tempArray;

     //determining the index of the next insertion
     int insertIdx = 0;
     for (int i = 0; i < size_; ++i) {
         if (wordArray_[i].getWord().compare(word) > 0) {
             insertIdx = i;
             break;
         }
         else
             insertIdx = ++i;
     }

     for (int i = size_ - 1; insertIdx <= i; --i) {
         wordArray_[i + 1] = wordArray_[i];
     }

     wordArray_[insertIdx] = WordOccurrence(word, 1);
     ++size_;
 }

 void WordList::print() {
     for (int i = 0; i < size_; ++i){
     
         cout << "Word: " << wordArray_[i].getWord() << ", ";
         cout << "Count: " << wordArray_[i].getNum() << endl;
     }
 }
 //sorting the wordarray in acending order
 void WordList::sort(){
     
     for (int i = 0; i < size_ - 1; ++i){
     
         for (int j = i + 1; j < size_; ++j){
         
             if (wordArray_[i].getNum() > wordArray_[j].getNum()){
             
                 WordOccurrence temp = wordArray_[j];
                 wordArray_[j] = wordArray_[i];
                 wordArray_[i] = temp;
             }
         }
     }
  }


//Main function for the program
 int main(int argc, char** argv){
     ifstream file(argv[1]);
 
     if (argc < 1){
     
         cout << "Not enough arguments\n";
         return -1;
     }
     if (!file){
     
         cout << "Cannot open the file\n";
         return -1;
     }
     WordList list;
   
     std::string word;
     while (file >> word){
     
         std::string newWord;
         for (int i = 0; i < word.size(); ++i){
         
             char Char = word[i];
             if (0 <= Char && Char <= 127){
             
                 //checks for alphabet numeric
                 if (isalnum(Char)){
                 
                     //checks if the char is uppercase
                     if (isupper(Char)) {
                         Char = char(tolower(Char));
                     }
             
                     newWord.append(sizeof(Char), Char);
                 }
             }
         }
         list.addWord(newWord);
         //cout << newWord;
     }
     list.sort();
     list.print();
     return 0;
 }