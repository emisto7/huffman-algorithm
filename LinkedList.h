#pragma once
#include "BinaryTreeNode.h"
#include <iostream>

class LinkedList {
private:
	struct Node {
		BinaryTreeNode* data;
		Node* next;

		Node(BinaryTreeNode* data) : data(data), next(nullptr) {}
	};

public:
	LinkedList() : head(nullptr), sz(0) {}

	bool isEmpty() const;
	int size() const;
	void addElement(BinaryTreeNode* node); 
	void addElementAtPosition(int position, BinaryTreeNode* node);
	void removeElementAtPosition(int position);
	int getPosition(BinaryTreeNode* node);
	Node* getSmallestFreqData();
	void print() const;

private:
	Node* head;
	int sz;
};


