#include "Huffman.h"

Huffman::Huffman()
{

}

Huffman::~Huffman()
{
	delMem(root);
}

void Huffman::build(std::string word)
{
	_word = word;
	std::string freqTable = countCharWithFreq(word);
	buildQueue(freqTable);
	buildTree();
	setTreeStruct(root);
	setNodeCode(root, "");
	setCode(word);
}

std::string Huffman::encode()
{
	std::stringstream out;
	std::string freqTable = countCharWithFreq(_word);
	out << _letters.size() << "\n"
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
	int i = 0, codeSizeOfLetter = 1;
	while (i < code.size())
	{
		std::string sub = code.substr(i, codeSizeOfLetter);
		char res = 0;
		if (codeSizeOfLetter >= numOfDif)
		{
			return "Erorr";
		}
		if (getLetter(tempRoot, sub, &res))
		{
			out << res;
			i += codeSizeOfLetter;
			codeSizeOfLetter = 1;
		}
		else
		{
			codeSizeOfLetter++;
		}
	}
	delMem(tempRoot);

	return out.str();
}

void Huffman::buildTree()
{
	for (int i = 0; i < tree.size() + 1; i++)
	{
		HuffmanNode* min1 = tree.top();
		tree.pop();
		HuffmanNode* min2 = tree.top();
		tree.pop();
		HuffmanNode* ptr = new HuffmanNode(min1->frequency + min2->frequency, 0, false);
		ptr->right = min2;
		ptr->left = min1;
		tree.push(ptr);
	}
	root = tree.top();
	tree.pop();
}

void Huffman::buildQueue(std::string freqTable)
{
	for (std::string::size_type i = 0; i < freqTable.size(); i++)
	{
		if (freqTable[i] != ' ' && i < freqTable.size() + 2)
		{
			if (isalnum(freqTable[i]) && freqTable[i + 1] == '-' && isalnum(freqTable[i + 2]))
			{
				char c = freqTable[i];
				int freq = static_cast<int>(freqTable[i + 2] - '0');
				if (isalnum(freqTable[i + 3]))
				{
					freq *= 10;
					freq += static_cast<int>(freqTable[i + 3] - '0');
				}
				if (isalnum(freqTable[i + 4]))
				{
					freq *= 10;
					freq += static_cast<int>(freqTable[i + 4] - '0');
				}
				HuffmanNode* node = new HuffmanNode(freq, c);
				tree.push(node);
			}
		}
	}
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

std::string Huffman::countCharWithFreq(std::string str)
{
	std::string finalone;
	// size of the string 'str'
	int n = str.size();

	// 'freq[]' implemented as hash table
	int freq[26] = { 0 };

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
