#pragma once
#include <string>
#include <iostream>
#include <list>
/// <summary>
/// Implementation of Trie
/// </summary>
class Trie{
	
	static const int ALEPHBET_SIZE = 26;

protected:
	/// <summary>
	/// Trie Node in the Trie
	/// </summary>
	class TrieNode {
	public:
		TrieNode* Children[ALEPHBET_SIZE]; // all the letter from the current alefbet
		TrieNode* Father; // the previs letter of prefix in the Trie
		bool IsEndOfWord; 
		int Index; // the index of the letter in the Children array
		bool IsLeaf; // flag to know if this node as no children
		TrieNode() 
		{
			for (int i = 0; i < ALEPHBET_SIZE; i++)
				Children[i] = NULL;
			Father = NULL;
			IsEndOfWord = false;
			Index = 0;
			IsLeaf = true;
		}
	};

private:
	TrieNode* root; // the root of the Trie
	int getIndexLetter(char letter);
	char intToAlphabet(int i);
	TrieNode* getEndOfWord(std::string prefix, bool getPrefix = false);
	bool isLeaf(TrieNode* node);
	void delMem(TrieNode* node);
	int printAutoSuggestions(TrieNode* node, std::string result);
public:	
	Trie();
	~Trie();
	void insert(std::string newWord);
	bool del(std::string wordToDel);
	bool search(std::string word);
	int printAutoSuggestions(std::string word);
};