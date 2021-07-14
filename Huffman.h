#pragma once
#include "LinkedList.h"
#include "BinaryTreeNode.h"
#include <fstream>
#include <sstream>
#include <iomanip> // levelofcompression function
#include <map> // countchar function
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::map;

class Huffman {
private:
	LinkedList list;
	map<char, string> m;
	BinaryTreeNode* root;
	string inputString;
	
	void makeAlphabet(BinaryTreeNode* root, int arr[], int index);

public:
	void runHuffman();
	void doCompress();
	void doDecompress();
	void createTree();

	void runMakeAlphabet();
	void countChar();
	string constructCompressed();
	void getStringFromFile(string fileName, string& input);
	void writeToFile(string fileName, string& output);

	void levelOfCompression(string compressed);
	void runDebugMode(string compressed);
	int debugMode(string compressed);
	
	string decompress(string compressed);
};
