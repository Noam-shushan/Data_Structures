#include <iostream>
#include "Huffman.h"
using namespace std;

int main()
{
	int choice;

	//Huffman
	Huffman t("aaabaaac");

	std::cout << t.encod();
	std::cout << t.decode(3, "bca", "00111", "1110011101");
	
	cout << "enter 1 to encode a text\n";
	cout << "enter 2 to decode a text\n";
	cout << "enter 3 to exit\n";

	do
	{
		int number = 0;
		string encodedStruct;
		string encodedtext;
		string letters;
		string word;
	
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "enter the original text" << endl;
			cin >> word;
		
			break;
		case 2:
			break;
		}

	} while (choice != 3);
	return 0;
}