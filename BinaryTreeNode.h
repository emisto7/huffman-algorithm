#pragma once

struct BinaryTreeNode {
	char symb;
	int freq;
	BinaryTreeNode* left;
	BinaryTreeNode* right;

	BinaryTreeNode(char _data, int _freq) : symb(_data), freq(_freq), left(nullptr), right(nullptr)
	{}
};

