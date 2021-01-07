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
		HuffmanNode* father;
		std::string code;
		HuffmanNode(int f, char s) : frequency(f), str(s), left(NULL), right(NULL), isLeaf(true), father(NULL)  {}
		HuffmanNode(int f, char c, bool l) : frequency(f), str(c), left(NULL), right(NULL), isLeaf(l), father(NULL) {}
		friend compareNode;
	};

	class compareNode {
	public:
		bool operator()(HuffmanNode* const& n1, HuffmanNode* const& n2)
		{
			return n1->frequency > n2->frequency;
		}
	};
private:
	HuffmanNode* root;
	std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, compareNode> tree;
	std::string _letters;
	std::string _treeStruct;
	std::string _code;
	std::string _word;

	void setLetters(HuffmanNode* node, std::string difLetters, int ind);
	void bulidTreeFromStruct(HuffmanNode* node, std::string wordStruct, int ind);
	void setNodeCode(HuffmanNode* node, std::string nodeCode);
	void getCode(HuffmanNode* node, char letter, std::string* res);
	bool getLetter(HuffmanNode* node, std::string nodeCode, char* res);
	void setCode(std::string word);
	void setTreeStruct(HuffmanNode* node);
	int countDifferentChar(std::string s);
	std::string countCharWithFreq(std::string str);
	void delMem(HuffmanNode* node);

public:
	
	Huffman(std::string word);
	~Huffman();
	std::string decode(int numOfDif, std::string difLetters,
		std::string wordStruct, std::string code);
	std::string encod();
};

