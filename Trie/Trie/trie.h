#pragma once
#include <string>
#include <iostream>
#include <list>

class Trie{
	
	static const int ALEPHBET_SIZE = 26;

protected:
	class TrieNode {
	public:
		TrieNode* Children[ALEPHBET_SIZE] = { 0 };
		TrieNode* Father;
		bool IsEndOfWord = false;
		int Index = 0;
		bool IsLeaf = true;
		TrieNode() {};
	};

private:
	TrieNode* root;
	int getIndexLetter(char letter);
	char intToAlphabet(int i);
	TrieNode* getEndOfWord(std::string word);
	bool isLeaf(TrieNode* node);
	void delMem(TrieNode* node);
public:	
	Trie();
	~Trie();
	void insert(std::string newWord);
	bool del(std::string wordToDel);
	bool search(std::string word);
	int printAutoSuggestions(std::string word);
};