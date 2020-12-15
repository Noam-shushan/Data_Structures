#include "trie.h"

Trie::Trie()
{
	root = new TrieNode();
}

Trie::~Trie()
{
	delete root;
}

void Trie::insert(std::string newWord)
{
	TrieNode* ptr = root;
	TrieNode* father = NULL;
	for (std::string::size_type i = 0; i < newWord.length(); i++)
	{
		int index = getIndexLetter(newWord[i]);
		if (!ptr->Children[index]) 
		{
			ptr->Children[index] = new TrieNode();
			father = ptr->Children[index];
		}
		
		ptr = ptr->Children[index];
		ptr->Father = father;
	}

	ptr->IsEndOfWord = true;
}

bool Trie::del(std::string wordToDel)
{
	//if (!search(wordToDel))
	//	return false;
	//TrieNode* end = getEndOfWord(wordToDel);
	//if (!end)
	//	return false;
	//TrieNode* iter = end;
	//while(isLeaf(iter))
	//{

	//}
	//TrieNode* iter = end->Father;
	//end = NULL;
	//while(!iter->IsEndOfWord)
	//{
	//    iter = NULL;
	//	iter = iter->Father;
	//}
	return true;
}

bool Trie::search(std::string word)
{
	TrieNode* ptr = root;
	for (std::string::size_type i = 0; i < word.length(); i++)
	{
		int index = getIndexLetter(word[i]);
		if (!ptr->Children[index])
			return false;
		ptr = ptr->Children[index];
	}
	return (ptr != NULL && ptr->IsEndOfWord);
}

int Trie::printAutoSuggestions(std::string word)
{
	return 0;
}

int Trie::getIndexLetter(char letter)
{
	return toupper(letter) % ALEPHBET_SIZE;
}

Trie::TrieNode* Trie::getEndOfWord(std::string word)
{
	TrieNode* ptr = root;
	for (std::string::size_type i = 0; i < word.length(); i++)
	{
		int index = getIndexLetter(word[i]);
		if (!ptr->Children[index])
			return NULL;
		ptr = ptr->Children[index];
	}
	if (ptr != NULL && ptr->IsEndOfWord)
		return ptr;
	return NULL;
}

bool Trie::isLeaf(TrieNode* node)
{
	for (int i = 0; i < ALEPHBET_SIZE; i++) 
	{
		if(node->Children[i] != NULL)
			return false;
	}
	return true;

}
