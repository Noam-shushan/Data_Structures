#include "Huffman.h"

Huffman::Huffman(std::string word)
{
	_word = word;
	std::string freqTable = countCharWithFreq(word);
	for (std::string::size_type i = 0; i < freqTable.size(); i++)
	{
		if (freqTable[i] != ' ' && i < freqTable.size() + 2)
		{
			if (isalnum(freqTable[i]) && freqTable[i + 1] == '-' && isalnum(freqTable[i + 2]))
			{
				char c = freqTable[i];
				int freq = static_cast<int>(freqTable[i + 2] - '0');
				HuffmanNode* node = new HuffmanNode(freq, c);
				tree.push(node);
			}
		}
	}
	for (int i = 0; i < tree.size() + 1; i++)
	{
		HuffmanNode* min1 = tree.top();
		tree.pop();
		HuffmanNode* min2 = tree.top();
		tree.pop();
		HuffmanNode* ptr = new HuffmanNode(min1->frequency + min2->frequency, 0, false);
		ptr->right = min2;
		ptr->left = min1;
		min1->father = min2->father = ptr;
		tree.push(ptr);
	}
	root = tree.top();
	tree.pop();
	setTreeStruct(root);
	setNodeCode(root, "");
	setCode(word);
}

Huffman::~Huffman()
{
	delMem(root);
}


std::string Huffman::encod()
{
	std::stringstream out;
	std::string freqTable = countCharWithFreq(_word);
	out << countDifferentChar(_word) << "\n"
		<< _letters << "\n"
		<< _treeStruct << "\n"
		<< _code << "\n";
	return out.str();
}

std::string Huffman::decode(int numOfDif, std::string difLetters,
	std::string wordStruct, std::string code)
{
	HuffmanNode* tempRoot = new HuffmanNode(0, 0, false);
	bulidTreeFromStruct(tempRoot, wordStruct, 0);
	setNodeCode(tempRoot, "");
	setLetters(tempRoot, difLetters, 0);

	std::stringstream out;
	for (int i = 1; i < numOfDif; i++)
	{
		for (int j = 0; j < code.size(); j++)
		{
			std::string sub = code.substr(j, i);
			char res = 0;
			if (getLetter(tempRoot, sub, &res))
				out << res;

		}
	}


	delMem(tempRoot);

	return out.str();
}

int _count = 0;
void Huffman::setLetters(HuffmanNode* node, std::string difLetters, int ind)
{
	if (ind == difLetters.size())
		return;

	if (node->isLeaf)
	{
		node->str = difLetters[ind];
		_count++;
		return;
	}
	setLetters(node->left, difLetters, _count);
	setLetters(node->right, difLetters, _count);
}

void Huffman::bulidTreeFromStruct(HuffmanNode* node, std::string wordStruct, int ind)
{
	if (ind >= wordStruct.size())
		return;
	if (wordStruct[ind] == '0')
	{
		node->left = new HuffmanNode(0, 0, false);
		node->right = new HuffmanNode(0, 0, false);
		bulidTreeFromStruct(node->left, wordStruct, ind + 1);
	}
	if (wordStruct[ind] == '1')
	{
		node->isLeaf = true;
		return;
	}
	bulidTreeFromStruct(node->right, wordStruct, ind + 2);
}

void Huffman::setNodeCode(HuffmanNode* node, std::string nodeCode)
{
	if (!node)
		return;

	if (node->isLeaf)
		node->code = nodeCode;

	setNodeCode(node->left, nodeCode + "0");
	setNodeCode(node->right, nodeCode + "1");
}

void Huffman::getCode(HuffmanNode* node, char letter, std::string* res)
{
	if (node->isLeaf)
	{
		if (node->str == letter)
		{
			*res = node->code;
			return;
		}
		return;
	}
	if (node->left)
		getCode(node->left, letter, res);

	if (node->right)
		getCode(node->right, letter, res);
}

bool Huffman::getLetter(HuffmanNode* node, std::string nodeCode, char* res)
{
	if (node->isLeaf)
	{
		if (node->code == nodeCode)
		{
			*res = node->str;
			return true;
		}
		return false;
	}
	return getLetter(node->left, nodeCode, res)
		|| getLetter(node->right, nodeCode, res);
}

void Huffman::setCode(std::string word)
{
	for (int i = 0; i < word.size(); i++)
	{
		std::string res = "";
		getCode(root, word[i], &res);
		_code += res;
	}
}

void Huffman::setTreeStruct(HuffmanNode* node)
{
	if (node->isLeaf)
	{
		_treeStruct += "1";
		_letters += node->str;
		return;
	}
	else
	{
		_treeStruct += "0";
		setTreeStruct(node->left);
	}
	setTreeStruct(node->right);
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
		if (freq[str[i] - 'a'] != 0)
		{

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
