//read a series of words into a vector

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

void getw(string& t, ifstream& in)
{

}

int main()
{
	ifstream word_file("word.txt"); //oepn word.txt file to be read
	istream_iterator<string> start(word_file), end; //initialize start as iterator to the beginning of file
	vector<string> words(start, end); //initialize vector words from start to end of file
	//in reading from the file, the input operator for strings uses white space
	//so each  white space set of characters is read as one string

	cout << "\n \n words as read \n";
	for (auto str : words)
		cout << str << "\t";
	sort(words.begin(), words.end());

	cout << " \n\n words as sorted\n";
	for (auto str : words)
		cout << str << "\t";
	cout << endl;
}