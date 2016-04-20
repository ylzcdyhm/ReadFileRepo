#pragma once
#include <iostream>
#include <ctype.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

class fileException
{
public:
	fileException(string s = "Error with file") : message(s) {}
private:
	string message;
};

class ReadFile
{
	friend ostream& operator<<(ostream&, const ReadFile&);
public:
	ReadFile(string s = " ");
	void readWord();
	void removePunct();
	void checkDuplicate();
	void printFrequency() const;

private:
	vector<string> words;
	vector<int> count;
	ifstream input;
	size_t index;
};

ostream & operator<<(ostream& os, const ReadFile& obj)
{
	for (const auto& i : obj.words)
		os << i << " ";
	os << endl;
	return os;
}

//constructor which also reads through the file, reading a word, removing its punctuation, checking if that word is a duplicate, then incrementing the index
ReadFile::ReadFile(string s)
{
	input.open(s);
	index = 0;

	while (input)
	{
		readWord();
		removePunct();
		if (index > 0)
			checkDuplicate();
		index++;
		if (input.eof())
			break;
	}

	//makeUnique();
	printFrequency();
}

inline void ReadFile::readWord()
{
	string word = "";
	input >> word;
	words.push_back(word);
	count.push_back(1);
}

//function to strip punctuation from end of a word using substring function
inline void ReadFile::removePunct()
{
	string word = "";
	word = words.at(index);						//store current word in local string variable
	size_t i = word.length();

	if (ispunct(word[i - 1]))
	{
		word = word.substr(0, i - 1);			//cut off punctuation at end of word if present
		words.at(index) = word;
	}
}

//function to march through word vector looking for duplicates, if there are, increment the count vector by 1 and then erase the most recent duplicate index from both vectors
inline void ReadFile::checkDuplicate()
{
	for (size_t i = 0; i < words.size() - 1; i++)
	{
		if (words[index] == words[i])
		{
			count[i]++;
			words.erase(words.begin() + index);
			count.erase(count.begin() + index);
			index--;
		}
	}
}

//function to print the frequency table
inline void ReadFile::printFrequency() const
{
	cout << "Words" << "\t \t" << "Frequency" << endl;
	for (size_t i = 0; i < words.size(); i++)
	{
		cout << words[i] << "\t \t \t" << count[i];
		cout << endl;
	}
}
