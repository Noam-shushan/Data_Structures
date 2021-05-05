#pragma once
#include <string>
#include <iostream>
#include<queue>
#include <sstream>
#include "FrequencyTable.h"

class compareNode;
/// <summary>
/// Application of data compression (strings) 
/// by using the Hoffman tree and its algorithm
/// </summary>
class Huffman
{
	/// <summary>
	/// a node in the tree
	/// </summary>
	class HuffmanNode
	{
	public:
		int frequency; // the frequency of some character
		char character; // the character of the node
		bool isLeaf; // flag to know if its a leaf in the tree
		HuffmanNode* left; // left son
		HuffmanNode* right; // right son
		std::string code; // the huffman code for the character
		
		/// <summary>
		/// constructor for the HuffmanNode
		/// </summary>
		/// <param name="f">frequency</param>
		/// <param name="c">character</param>
		HuffmanNode(int f, char c) : frequency(f), character(c), left(NULL), right(NULL), isLeaf(true)  {}
		/// <summary>
		/// constructor for the HuffmanNode
		/// </summary>
		/// <param name="f">frequency</param>
		/// <param name="c">character</param>
		/// <param name="l">flag to know if its a leaf in the tree</param>
		HuffmanNode(int f, char c, bool l) : frequency(f), character(c), left(NULL), right(NULL), isLeaf(l) {}
		friend compareNode;
	};
	/// <summary>
	/// compare object in order to use priority queue
	/// </summary>
	class compareNode {
	public:
		bool operator()(HuffmanNode* const& n1, HuffmanNode* const& n2)
		{
			return n1->frequency > n2->frequency;
		}
	};

private:
	HuffmanNode* root; // root of the huffman tree
	std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, compareNode> tree;
	std::string _letters;
	std::string _treeStruct;
	std::string _code;
	std::string _word;
	FrequencyTable* _frequencyTable;
	/// <summary>
	/// 
	/// </summary>
	struct GlobalCountersForRecursion {
	private:
		int countForSetLetters;
		int countForbulidTree;
	public:
		int getCountForSetLetters() {
			return countForSetLetters;
		}

		int incCountForSetLetters() {
			return ++countForSetLetters;
		}

		void resetCountForSetLetters() {
			countForSetLetters = 0;
		}

		int incCountForbulidTree() {
			return ++countForbulidTree;
		}

		int getCountForbulidTree() {
			return countForbulidTree;
		}

		void resetCountForbulidTree() {
			countForbulidTree = 0;
		}
	} counters;
	
	void setLetters(HuffmanNode* node, std::string difLetters, int ind);
	void bulidTreeFromStruct(HuffmanNode* node, std::string wordStruct, int ind);
	void setNodeCode(HuffmanNode* node, std::string nodeCode);
	void getCode(HuffmanNode* node, char letter, std::string* res);
	bool getLetter(HuffmanNode* node, std::string nodeCode, char* res);
	void setCode(std::string word);
	void setTreeStruct(HuffmanNode* node);
	void delMem(HuffmanNode* node);
	void buildTree();
	void buildQueue();
	std::string getTheWordDecoded(HuffmanNode* node, int  numOfDif, std::string code);
public:
	
	Huffman();
	~Huffman();
	/// <summary>
	/// bulid the huffman tree
	/// </summary>
	/// <param name="word">the word to encode or decode</param>
	void build(std::string word);
	std::string decode(int numOfDif, std::string difLetters,
		std::string wordStruct, std::string code);
	std::string encode();
};

