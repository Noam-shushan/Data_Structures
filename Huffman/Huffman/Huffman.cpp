#include "Huffman.h"

Huffman::Huffman()
{
	counters.resetCountForbulidTree();
	counters.resetCountForbulidTree();
}

Huffman::~Huffman()
{
	delMem(root);
	delete _frequencyTable;
}

void Huffman::build(std::string word)
{
	_word = word;;
	_frequencyTable = new FrequencyTable(word); // bulid frequency table with the tuples of (letter, frequency)
	buildQueue(); // bulid the priority queue with the nodes
	buildTree(); // bulid the tree from the queue
	setTreeStruct(root); // set the struct of the tree
	setNodeCode(root, ""); // set the node code to each node in the tree
	setCode(word); // set the code of the word 
}

std::string Huffman::encode()
{
	std::stringstream out;
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
	counters.resetCountForbulidTree();
	
	setNodeCode(tempRoot, "");
	setLetters(tempRoot, difLetters, 0);
	counters.resetCountForSetLetters();
	
	std::string out = getTheWordDecoded(tempRoot, numOfDif, code);
	delMem(tempRoot);
	return out;
}

void Huffman::buildTree()
{
	while (tree.size() > 1)
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

void Huffman::buildQueue()
{
	while (!tree.empty()) // clear the queue
		tree.pop();
	
	for (std::map<char, int>::iterator iter = _frequencyTable->begin(); 
		iter != _frequencyTable->end(); iter++) 
	{
		HuffmanNode* node = new HuffmanNode(iter->second, iter->first);
		tree.push(node);
	}
}

std::string Huffman::getTheWordDecoded(HuffmanNode* node, int  numOfDif,std::string code)
{
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
		if (getLetter(node, sub, &res))
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

	return out.str();
}

void Huffman::setLetters(HuffmanNode* node, std::string difLetters, int ind)
{
	if (ind == difLetters.size())
	{
		return;
	}
	
	if (node->isLeaf)
	{
		node->character = difLetters[ind];
		counters.incCountForSetLetters();
		return;
	}
	setLetters(node->left, difLetters, counters.getCountForSetLetters());
	setLetters(node->right, difLetters, counters.getCountForSetLetters());
}


void Huffman::bulidTreeFromStruct(HuffmanNode* node, std::string wordStruct, int ind)
{
	if (ind == wordStruct.size()) 
	{
		return;
	}
		
	if (wordStruct[ind] == '0')
	{
		node->left = new HuffmanNode(0, 0, false);
		node->right = new HuffmanNode(0, 0, false);
		counters.incCountForbulidTree();
		bulidTreeFromStruct(node->left, wordStruct, counters.getCountForbulidTree());
	}
	if (wordStruct[ind] == '1')
	{
		node->isLeaf = true;
		counters.incCountForbulidTree();
		return;
	}
	bulidTreeFromStruct(node->right, wordStruct, counters.getCountForbulidTree());
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
		if (node->character == letter)
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
			*res = node->character;
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
		_letters += node->character;
		return;
	}
	else
	{
		_treeStruct += "0";
		setTreeStruct(node->left);
	}
	setTreeStruct(node->right);
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
