#include <iostream>
#include "Huffman.h"


int main()
{
	int choice;
	//Huffman
	Huffman t("aaabaaac");
	std::cout << t.encod();
	std::cout << t.decode(3, "bca", "00111", "1110011101");
	//cout << "enter 1 to encode a text\n";
	//cout << "enter 2 to decode a text\n";
	//cout << "enter 3 to exit\n";

	//do
	//{
	//	string word;
	//	cout << "press 1 to encode or 2 to decode" << endl;
	//	cin >> choice;
	//	switch (choice)
	//	{
	//	case 1:
	//		cout << "enter the original text" << endl;
	//		cin >> word;

	//		//Build Huffman tree given the data inside "word".
	//		//Then find the code of each letter.
	//		//Then print the output - number of leaves, order of letters, tree structure and the encoded text - according to the explanation in the exercise.

	//		break;
	//	case 2:
	//		//input the number of leaves, the  order of letters, tree structure and the encoded text.
	//		//build the Huffman Tree according to the tree strcture. put the letters in the leaves according to the given order. 
	//		//Given the Huffman Tree and the encoded text, find the original text, and print it. 

	//	}

	//} while (choice != 3);
	return 0;
}