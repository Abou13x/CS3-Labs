// reads command line arguments and prints them one per line
// Mikhail Nesterenko
// 1/16/2014

#include <iostream>
#include <fstream>
#include<string>

using std::cout; 
using std::endl;  
using std::ifstream;
using std::string;

int main(int argc, char* argv[]) {
	//makes sure that two files have been provided to the command line
	if (argc != 3) {
		cout << "Not sufficient argument";
		return 1;
	}
	//creating file object
	ifstream file1(argv[1]);
	ifstream file2(argv[2]);
	//variables to contain the lines of the text files
	string text1;
	string text2;
	if (file1.is_open() && file2.is_open()) {
		//line number
		int n = 1;
		
		//runs the content of the loop until it reaches the end of both files
		while (!file1.eof() || !file2.eof()) {
			//reads each lines in the files
			getline(file1, text1);
			getline(file2, text2);

			//checking for the smallest text file
			int smallestTextLength = 0;
			if (text1.length() < text2.length()) {
				smallestTextLength = text1.length();
			}
			else if (text2.length() < text1.length()) {
				smallestTextLength = text2.length();
			}
			else {
				smallestTextLength = text1.length();
			}
			//Position of unequal lines
			bool foundPosition = false;
			//true if two unequal lines is found
			int unequalPosition = 0;
			
			for (int i = 0; i < smallestTextLength; i++) {
				//compares each characters of both files
				if (text1[i] != text2[i] && foundPosition != true) {
					//Position of unequal lines
					unequalPosition = i + 1;
					//true if two unequal lines is found
					foundPosition = true;
				}
			}
			//prints the unequal lines
			if (unequalPosition != 0) {
				//returns the size of the file name
				int file2Length = strlen(argv[2]);
				//number of spaces
				int space = file2Length + 5 + unequalPosition;
				//create the number of empty spaces
				string spaceString(space - 1, ' ');
				cout << argv[1] << ": " << n << ": " << text1 << "\n";
				cout << argv[2] << ": " << n << ": " << text2 << "\n";
				cout << spaceString;
				cout << "^\n";
			}
			//sets the text of the shortest file to empty when at the end of the file
			if (file1.eof() && !file2.eof()) {
				text1 = " ";
			}
			if (file2.eof() && !file1.eof()) {
				text2 = " ";
			}
			//increament line number by 1 
			n += 1;
			
		
		}
		//close the files
			file1.close();
			file2.close();
		}
	else {
		cout << "Couldn't opening file";
	}
			
	
	return 0;
}