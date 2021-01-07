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
	Huffman(std::string word);
	~Huffman();
	void decode();
	void encod(std::string word);
	int countDifferentChar(std::string s);
	std::string countCharWithFreq(std::string str);
	void delMem(HuffmanNode* node);
};

