#ifndef AVLTREE_H
#define AVLTREE_H

#include "TableInterface.h"
#include <iostream>

template <typename T>
class AVLTree : public TableInterface<T> {
private:
	class Node {
	public:
		T data;
		Node* left;
		Node* right;
		int height;

		Node(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
	};

	Node* root;

	// Методы для балансировки дерева
	Node* rotateRight(Node* y);
	Node* rotateLeft(Node* x);
	int getBalance(Node* N);
	int getHeight(Node* N);
	Node* insert(Node* node, const T& val);
	Node* minValueNode(Node* node);
	Node* deleteNode(Node* root, const T& val);
	bool _find(Node* root, const T& val) const;
	void _display(Node* root) const;

public:
	AVLTree() : root(nullptr) {}
	~AVLTree();

	void add(const T& element) override;
	void remove(const T& element) override;
	bool find(const T& element) const override;
	void display() const override;
};

#endif // AVLTREE_H
