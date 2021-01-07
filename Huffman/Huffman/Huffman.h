#pragma once
#include <string>
#include<queue>
#include<cstring>
#include <unordered_map>
#include <sstream>


class compareNode;
class Huffman
{
	class HuffmanNode
	{
	public:
		int frequency;
		char str;
		bool isLeaf;
		HuffmanNode* left;
		HuffmanNode* right;
		std::string code;
		HuffmanNode(int f, char s) : frequency(f), str(s), left(NULL), right(NULL), isLeaf(true) {}
		friend compareNode;
	};

	class compareNode {
	public:
		bool operator()(HuffmanNode* const& n1, HuffmanNode* const& n2)
		{
			return n1->frequency > n2->frequency;
		}
	};

	HuffmanNode* root;
	std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, compareNode> tree;
	
public:
	std::string letters = "";
	std::string treeStruct = "";
	std::string code = "";
	Huffman(std::string word);
	~Huffman();
	void decode();
	void encod(std::string word);
	void setNodeCode(HuffmanNode* node, std::string nodeCode);
	std::string getCode(HuffmanNode* node, char letter);
	void setCode(std::string word);
	void setTreeStruct(HuffmanNode* node);
	int countDifferentChar(std::string s);
	std::string countCharWithFreq(std::string str);
	void delMem(HuffmanNode* node);
};

