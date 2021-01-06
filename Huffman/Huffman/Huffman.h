#pragma once
#include <string>
#include<queue>

class Huffman
{
	class HuffmanNode 
	{
		int frequency;
		char letter;
		bool isLeaf;
	};

	HuffmanNode* root;
	std::priority_queue<HuffmanNode> tree;
public:
	Huffman();
	~Huffman();
	void decode(std::string word);
	void encod();
};

