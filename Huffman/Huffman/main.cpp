#include <iostream>
#include "Huffman.h"
using namespace std;

int main()
{
	int choice;
	//Huffman

	Huffman *t = new Huffman;
	
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
			t->setWord(word);
			t->encod();
			break;
		case 2:
			cout << "enter n" << endl;
			cin >> number;
			cout << "enter the letters" << endl;
			cin >> letters;
			cout << "enter the encoded structure" << endl;
			cin >> encodedStruct;
			cout << "enter the encoded text" << endl;
			cin >> encodedtext;
			t->decode(number, letters, encodedStruct, encodedtext);
		}

	} while (choice != 3);
	return 0;
}