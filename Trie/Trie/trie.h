#pragma once
#include <string>
#include <iostream>

class Trie{
	
	static const int ALEPHBET_SIZE = 26;

protected:
	class TrieNode {
	public:
		TrieNode* Children[ALEPHBET_SIZE] = { 0 };
		TrieNode* Father;
		bool IsEndOfWord = false;

		TrieNode() {};
		~TrieNode()
		{
			for (int i = 0; i < ALEPHBET_SIZE; i++)
			{
				if (Children[i] != NULL)
					delete Children[i];
			}
		}
	};

private:
	TrieNode* root;
	int getIndexLetter(char letter);
	TrieNode* getEndOfWord(std::string word);
	bool isLeaf(TrieNode* node);
public:	
	Trie();
	~Trie();

	void insert(std::string newWord);
	bool del(std::string wordToDel);
	bool search(std::string word);
	int printAutoSuggestions(std::string word);

};