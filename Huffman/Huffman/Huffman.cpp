#include "Huffman.h"

Huffman::Huffman(std::string word)
{
	std::string freqTable = countCharWithFreq(word);
	for (std::string::size_type i = 0; i < freqTable.size(); i++) 
	{
		if (freqTable[i] != ' ' && i < freqTable.size() + 2)
		{
			if (isalnum(freqTable[i]) && freqTable[i + 1] == '-' && isalnum(freqTable[i+2])) 
			{
				char c = freqTable[i];
				int freq = static_cast<int>(freqTable[i + 2] - '0');
				HuffmanNode* node = new HuffmanNode(freq, c);
				tree.push(node);
			}
		}
	}
	for(int i = 0; i < tree.size() + 1; i++)
	{
		HuffmanNode* min1 = tree.top();
		tree.pop();
		HuffmanNode* min2 = tree.top();
		tree.pop();
		HuffmanNode* ptr = new HuffmanNode(0, 0);
		ptr->frequency = min1->frequency + min2->frequency;
		ptr->isLeaf = false;
		ptr->right = min2;
		ptr->left = min1;
		tree.push(ptr);
	}
	root = tree.top();
	tree.pop();
}

Huffman::~Huffman()
{
	delMem(root);
}

void Huffman::decode()
{

}

void Huffman::encod(std::string word)
{
	std::stringstream out;
	std::string freqTable = countCharWithFreq(word);
	out << countDifferentChar(word) << "\n" << freqTable << "\n";
}


int Huffman::countDifferentChar(std::string str)
{

	std::unordered_map<char, int> map;

	for (std::string::size_type i = 0; i < str.length(); i++)
	{
		map[str[i]]++;
	}

	return map.size();
}
std::string Huffman::countCharWithFreq(std::string str)
{
	std::string finalone;
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

void Huffman::delMem(HuffmanNode* node)
{
	if (node == NULL)	
		return;

	if (node->left != NULL)
		delMem(node->left);
	
	if (node->right != NULL)
		delMem(node->right);
	
	delete node;
}
