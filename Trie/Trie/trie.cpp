#include "trie.h"
/// <summary>
/// constructor
/// </summary>
Trie::Trie()
{
	root = new TrieNode();
	root->Father = NULL;
}
/// <summary>
/// disctrutor
/// </summary>
Trie::~Trie()
{
	delMem(root);
	delete root;
}
/// <summary>
/// insert a new word to the Trie
/// </summary>
/// <param name="newWord">the given word</param>
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
			ptr->Index = index;
			ptr->IsLeaf = false;
			father = ptr;
		}
		
		ptr = ptr->Children[index];
		ptr->Father = father;
	}

	ptr->IsEndOfWord = true; // mark the end of the word
}
/// <summary>
/// delete word from the Trie 
/// </summary>
/// <param name="wordToDel">the given word</param>
/// <returns>true if the deletion as made else false</returns>
bool Trie::del(std::string wordToDel)
{
	TrieNode* end = getEndOfWord(wordToDel); // get the node of the end of the word 
	if (!end) // check if it is exsist
		return false;
	
	end->IsEndOfWord = false; // for any case mark it as false
	if(!end->IsLeaf) // if the end of the word is prefix of anther word
		return true;
	
	TrieNode* iter = end;
	// we delete from the end to the beginig while the node is not prefix of anther word or it as children
	while(!iter->IsEndOfWord && iter->IsLeaf) 
	{
		int ind = iter->Index;
		iter = iter->Father;
		delete iter->Children[ind];
		iter->IsLeaf = isLeaf(iter);
	}
	return true;
}
/// <summary>
/// search word in the Trie 
/// </summary>
/// <param name="word">the given word</param>
/// <returns>true if the word is found else false</returns>
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
	//std::list<std::string> allSuggestion;
	//TrieNode* ptr = root;
	//for (int i = 0; i < ALEPHBET_SIZE; i++)
	//{

	//}
	return 0;
}

int Trie::getIndexLetter(char letter)
{
	return static_cast<int>(tolower(letter) - 'a');
}

char Trie::intToAlphabet(int i)
{
	return static_cast<char>('a' + i);
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

void Trie::delMem(TrieNode* node)
{
	if (node->IsLeaf)
		return;

	for (int i = 0; i < ALEPHBET_SIZE; i++)
	{
		if (node->Children[i])
		{
			delMem(node->Children[i]);
			delete node->Children[i];
		}
	}
}


