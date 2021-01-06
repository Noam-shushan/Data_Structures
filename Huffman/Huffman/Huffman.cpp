#include "Huffman.h"
#include<cstring>
#include <unordered_map>
#include <sstream>
using namespace std;

Huffman::Huffman()
{

}

Huffman::~Huffman()
{
}

void Huffman::decode(std::string word)
{
}

void Huffman::encod()
{
}


int countdifCarac(string s)
{

	unordered_map<char, int> m;

	for (int i = 0; i < s.length(); i++) {
		m[s[i]]++;
	}

	return m.size();
}
string countCharWithFreq(string str)
{
	string finalone;
	// size of the string 'str'
	int n = str.size();

	// 'freq[]' implemented as hash table
	int freq[26];

	// initialize all elements of freq[] to 0
	memset(freq, 0, sizeof(freq));

	// accumulate freqeuncy of each character in 'str'
	for (int i = 0; i < n; i++)
		freq[str[i] - 'a']++;

	// traverse 'str' from left to right
	for (int i = 0; i < n; i++) {

		// if frequency of character str[i] is not
		// equal to 0
		if (freq[str[i] - 'a'] != 0) {

			// print the character along with its
			// frequency
			finalone = finalone + str[i];
			finalone = finalone + "-";

			std::string out_string;
			std::stringstream ss;
			ss << freq[str[i] - 'a'];
			out_string = ss.str();

			finalone = finalone + out_string;
			finalone = finalone + ' ';


			freq[str[i] - 'a'] = 0;
		}
	}
	return finalone;
}
