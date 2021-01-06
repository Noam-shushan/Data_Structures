#pragma once
#include <string>
#include<queue>
#include<cstring>
#include <unordered_map>
#include <sstream>

class Huffman
{
	class HuffmanNode 
	{
	public:
		int frequency;
		std::string str;
		bool isLeaf;
		HuffmanNode* left;
		HuffmanNode* right;
		HuffmanNode(int f, std::string s) : frequency(f), str(s), left(NULL), right(NULL), isLeaf(true) {}
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
	Huffman();
	~Huffman();
	void decode(std::string word);
	void encod();
	int countDifferentChar(std::string s);
	std::string countCharWithFreq(std::string str);
};

