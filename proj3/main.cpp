//-------------------------------------------------------------------------------------
//                CS 215-401  Project 3   Binary Search Tree
//-------------------------------------------------------------------------------------
//
//
//
//-------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "BST.h"
using namespace std;

//-------------------------------------------------------------------------------------
//                                loadFile()
//-------------------------------------------------------------------------------------
void loadFile(BST & b) {
	string fname, data;
	ifstream f;
	int numNodes, key;

	// open input file
	cout << "Enter load file name: ";
	cin >> fname;
	f.open(fname);
	if (f.fail()) {
		cout << "Unable to open " << fname << endl;
		return;
	}

	// read data from file
	f >> numNodes;
	for (int i = 1; i <= numNodes; i++) {
		f >> key;
		getline(f, data);
		b.insert(key, data);
	}
	f.close();
} // loadFile()

//-------------------------------------------------------------------------------------
//                                getSelection()
//-------------------------------------------------------------------------------------
char getSelection() {
	char sel;
	cout << "\nBST Test Menu:\n";
	cout << "I - Insert new node\n";
	cout << "S - Search\n";
	cout << "D - Dimensions (stats)\n";
	cout << "P - Print Key Tree\n";
	cout << "L - Print Sorted List\n";
	cout << "R - Read From File\n";
	cout << "X - Exit\n";
	cout << "Enter selection: ";
	cin >> sel;
	sel = toupper(sel);
	return sel;
}

//-------------------------------------------------------------------------------------
//                                testInsert()
//-------------------------------------------------------------------------------------
void testInsert(BST & b) {
	int akey;
	string data;
	cout << "Enter key and data: ";
	cin >> akey;
	getline(cin, data);
	b.insert(akey, data);
}

//-------------------------------------------------------------------------------------
//                                testSearch()
//-------------------------------------------------------------------------------------
void testSearch(BST & b) {
	int akey;
	string data;
	cout << "Enter search key: ";
	cin >> akey;
	data = b.search(akey);
	if (data == "")
		cout << "Item not found\n";
	else
		cout << "Item found, data = " << data << endl;
}

//-------------------------------------------------------------------------------------
//                                testStats()
//-------------------------------------------------------------------------------------
void testStats(BST & b) {
	cout << "Tree depth      = " << b.depth() << endl;
	cout << "Number of Nodes = " << b.numNodes() << endl;
	cout << "Minimum Key     = " << b.minKey() << endl;
}

//-------------------------------------------------------------------------------------
//                                main()
//-------------------------------------------------------------------------------------
int main() {
	BST b;				// a binary search tree
	char sel = ' ';

	do {
		sel = getSelection();
		switch (sel) {
		case 'I': testInsert(b);    break;
		case 'S': testSearch(b);    break;
		case 'D': testStats(b);     break;
		case 'P': b.printKeyTree(); break;
		case 'L': b.printSorted();  break;
		case 'R': loadFile(b);		break;
		case 'X': cout << "Bye!\n"; break;
		default: cout << "Invalid entry\n";
		}
	} while (sel != 'X');
	system("pause");
	return 0;
}
