#include "trie.h"
/// <summary>
/// constructor
/// </summary>
Trie::Trie()
{
	root = new TrieNode();
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
/// <summary>
/// print auto suggestions of a given prefix
/// </summary>
/// <param name="prefix">the given prefix we wont to complte with all existing words in the Trie</param>
/// <returns>0 if no string exist with this prefix or the number of words that bigen with this prefix</returns>
int Trie::printAutoSuggestions(std::string prefix)
{
	TrieNode* end = getEndOfWord(prefix, true); // get the node of the last letter of the word in the Trie
	if(!end) // word dont exsist
		return 0;
	return printAutoSuggestions(end, prefix);
}

int Trie::printAutoSuggestions(TrieNode* node, std::string result)
{
	int count = 0;
	if (node->IsEndOfWord) // if this is the end print the result
	{
		std::cout << result << "\n";
		count += 1;
	}
	if (node->IsLeaf)
		return count;
	for (int i = 0; i < ALEPHBET_SIZE; i++)
	{
		if (node->Children[i])
		{
			result += intToAlphabet(i); // append the letter to the outpot
			count += printAutoSuggestions(node->Children[i], result); // call in recurtion to the next letter
			result = result.substr(0, result.size() - 1); // get rid of the leftovers from the last call
		}
	}
	return count;
}

int Trie::getIndexLetter(char letter)
{
	return static_cast<int>(tolower(letter) - 'a');
}

char Trie::intToAlphabet(int i)
{
	return static_cast<char>('a' + i);
}
/// <summary>
/// get the node of the last letter in the word
/// </summary>
/// <param name="word">the given word</param>
/// <param name="getPrefix">flag that detemant if we wont a word from the Trie of some prefix</param>
/// <returns>the node of the last letter</returns>
Trie::TrieNode* Trie::getEndOfWord(std::string word, bool getPrefix)
{
	TrieNode* ptr = root;
	for (std::string::size_type i = 0; i < word.length(); i++)
	{
		int index = getIndexLetter(word[i]);
		if (!ptr->Children[index])
			return NULL; // word dont exist in the Trie
		ptr = ptr->Children[index];
	}
	if (getPrefix && ptr)
		return ptr;
	if (ptr && ptr->IsEndOfWord)
		return ptr;
	
	return NULL;
}
// check if the node have children
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



