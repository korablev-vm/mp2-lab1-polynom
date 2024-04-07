#ifndef AVLTREE_H
#define AVLTREE_H

#include "TableInterface.h"
#include <iostream>
#include <algorithm>

template<typename TKey, typename TValue>
class AVLTree : public TableInterface<TKey, TValue> {
private:
	class Node {
	public:
		TRecord<TKey, TValue> data;
		Node* left;
		Node* right;
		int height;

		Node(const TRecord<TKey, TValue>& val) : data(val), left(nullptr), right(nullptr), height(1) {}
	};

	Node* root;

	Node* rotateRight(Node* y) {
		Node* x = y->left;
		Node* T2 = x->right;

		x->right = y;
		y->left = T2;

		y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
		x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

		return x;
	}

	Node* rotateLeft(Node* x) {
		Node* y = x->right;
		Node* T2 = y->left;

		y->left = x;
		x->right = T2;

		x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
		y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

		return y;
	}

	int getBalance(Node* N) {
		if (N == nullptr) return 0;
		return getHeight(N->left) - getHeight(N->right);
	}

	int getHeight(Node* N) {
		if (N == nullptr) return 0;
		return N->height;
	}

	Node* insert(Node* node, const TRecord<TKey, TValue>& record) {
		if (node == nullptr) return new Node(record);

		if (record < node->data) {
			node->left = insert(node->left, record);
		}
		else if (node->data < record) {
			node->right = insert(node->right, record);
		}
		else {
			return node; // Дубликаты не добавляем
		}

		// Обновление высоты предка текущего узла
		node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

		// Проверка баланса узла
		int balance = getBalance(node);

		// Левое-левое
		if (balance > 1 && record < node->left->data) {
			return rotateRight(node);
		}

		// Правое-правое
		if (balance < -1 && node->right->data < record) {
			return rotateLeft(node);
		}

		// Левое-правое
		if (balance > 1 && node->left->data < record) {
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}

		// Правое-левое
		if (balance < -1 && record < node->right->data) {
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}

		return node;
	}

	Node* minValueNode(Node* node) {
		Node* current = node;
		while (current->left != nullptr) current = current->left;
		return current;
	}

	Node* deleteNode(Node* root, const TKey& key) {
		if (root == nullptr) return root;

		TRecord<TKey, TValue> record{ key, TValue() };

		if (record < root->data) {
			root->left = deleteNode(root->left, key);
		}
		else if (root->data < record) {
			root->right = deleteNode(root->right, key);
		}
		else {
			if ((root->left == nullptr) || (root->right == nullptr)) {
				Node* temp = root->left ? root->left : root->right;

				if (temp == nullptr) {
					temp = root;
					root = nullptr;
				}
				else {
					*root = *temp; // Копирование содержимого ненулевого дочернего узла
				}
				delete temp;
			}
			else {
				Node* temp = minValueNode(root->right);

				root->data = temp->data;

				root->right = deleteNode(root->right, temp->data.key);
			}
		}

		if (root == nullptr) return root;

		// Обновление высоты текущего узла

		root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

		// Повторно проверяем баланс узла после удаления, чтобы убедиться, что он остается сбалансированным
		int balance = getBalance(root);

		// Левое-левое
		if (balance > 1 && getBalance(root->left) >= 0) {
			return rotateRight(root);
		}

		// Левое-правое
		if (balance > 1 && getBalance(root->left) < 0) {
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}

		// Правое-правое
		if (balance < -1 && getBalance(root->right) <= 0) {
			return rotateLeft(root);
		}

		// Правое-левое
		if (balance < -1 && getBalance(root->right) > 0) {
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}

		return root;
	}

	Node* _find(Node* root, const TKey& key) const {
		if (root == nullptr) {
			return nullptr;
		}

		TRecord<TKey, TValue> record{ key, TValue() };

		if (record < root->data) {
			return _find(root->left, key);
		}
		else if (root->data < record) {
			return _find(root->right, key);
		}
		else {
			return root;
		}
	}

	void _display(Node* root, HDC hdc, int& y, int xOffset = 10) const {
		if (root != nullptr) {
			_display(root->left, hdc, y, xOffset + 15); // Увеличиваем смещение для дочерних узлов

			std::ostringstream oss;
			oss << "Key: " << root->data.key << ", Value: " << root->data.value;
			std::string itemText = oss.str();  // Формируем строку с помощью ostringstream
			TabbedTextOut(hdc, 5, y, itemText.c_str(), __max(itemText.size(), 20), 1, NULL, 0);
			y += 20;  // Смещаемся вниз для следующего узла

			_display(root->right, hdc, y, xOffset + 15);
		}
	}

	void _deleteTree(Node* node) {
		if (node == nullptr) return;
		_deleteTree(node->left);
		_deleteTree(node->right);
		delete node;
	}

public:
	AVLTree() : root(nullptr) {}

	~AVLTree() {
		_deleteTree(root);
	}

	void add(const TRecord<TKey, TValue>& record) override {
		root = insert(root, record);
	}

	void remove(const TKey& key) override {
		root = deleteNode(root, key);
	}

	TValue* find(const TKey& key) override {
		Node* result = _find(root, key);
		if (result == nullptr) return nullptr;
		return &result->data.value;
	}

	void display(HDC hdc, int PosY) const override {
		int y = -PosY; // Начальное положение для отображения первого узла
		_display(root, hdc, y);
	}
};

#endif // AVLTREE_H
