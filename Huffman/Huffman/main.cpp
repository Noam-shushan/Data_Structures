#include <iostream>
#include "Huffman.h"

/// authors:
/// noam shushan 314717588
/// shmuel verse 1666859  

using namespace std;




int main()
{
	int choice;
	cout << "enter 1 to encode a text\n";
	cout << "enter 2 to decode a text\n";
	cout << "enter 3 to exit\n";

	do
	{
		string word;
		cin >> choice;
		Huffman tree;
		switch (choice)
		{
			case 1:
				cout << "enter the original text" << endl;
				cin >> word;
				tree.build(word);
				cout <<"The encoded string is: \n" << tree.encode() << endl;
				break;
			
			case 2:
				int n;
				string letters, treeStuct, code;
				cout << "enter n ";
				cin >> n;
				cout << "enter the letters ";
				cin >> letters;
				cout << "enter the encoded structure ";
				cin >> treeStuct;
				cout << "enter the encoded text ";
				cin >> code;
				cout << "The decoded string is: " << tree.decode(n, letters, treeStuct, code) << endl;
				break;
		}

	} while (choice != 3);
	return 0;
}