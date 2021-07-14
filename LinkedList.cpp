#include "LinkedList.h"
#include "BinaryTreeNode.h"

bool LinkedList::isEmpty() const {
	return sz == 0;
}

int LinkedList::size() const {
	return sz;
}

void LinkedList::addElement(BinaryTreeNode* node) {
	Node* newElement = new Node(node);

	if (this->head == nullptr) {
		this->head = newElement;
	}
	else {
		Node* iter = this->head;
		while (iter->next != nullptr) {
			iter = iter->next;
		}
		iter->next = newElement;
	}
	++sz;
}

void LinkedList::addElementAtPosition(int position, BinaryTreeNode* node) {
	Node* newElement = new Node(node);

	if (position == 1) {
		newElement->next = head;
		head = newElement;
	}
	else {
		Node* iter = this->head;
		for (int i = 1; i < position - 1; i++) {
			iter = iter->next;
		}
		newElement->next = iter->next;
		iter->next = newElement;
	}
	++sz;
}

void LinkedList::removeElementAtPosition(int position) {
	if (isEmpty() || position > sz || position < 1)
	{
		std::cout << "variable not found" << std::endl;
		throw std::invalid_argument("Index out of bounds\n");
	}

	Node* detach = this->head;

	if (position == 1) {
		head = head->next;
	}
	else {
		Node* iter = this->head;
		for (int i = 1; i < position - 1; i++) {
			iter = iter->next;
		}
		detach = iter->next;
		iter->next = detach->next;
	}
	--sz;
	delete detach;
}

int LinkedList::getPosition(BinaryTreeNode* node) {
	Node* iter = this->head;
	int position = 1;

	while (iter != nullptr) {
		if (iter->data->freq == node->freq) {
			return position;
		}
		++position;
		iter = iter->next;
	}
	return -1;
}

LinkedList::Node* LinkedList::getSmallestFreqData() {
	Node* iter = this->head;
	Node* temp = this->head;

	while (iter != nullptr) {
		if (temp->data->freq > iter->data->freq) {
			temp = iter;
		}
		iter = iter->next;
	}
	return temp;
}

void LinkedList::print() const {
	Node* iter = this->head;

	while (iter != nullptr) {
		std::cout << iter->data->symb << " " << iter->data->freq << std::endl;
		iter = iter->next;
	}
}
