#pragma once
#include <string>
#include <iostream>

class Trie{
	static const int ALEPHBET = 26;
protected:
	class TrieNode {
	public:
		TrieNode* Children[ALEPHBET] = { 0 };
		TrieNode* Father;
		bool IsEndWord = false;

		TrieNode() {};
	};

	TrieNode* root;
public:
	
	Trie();
	~Trie();

	void insert(std::string newWord);
	bool del(std::string wordToDel);
	bool search(std::string word);
	int printAutoSuggestions(std::string word);

};