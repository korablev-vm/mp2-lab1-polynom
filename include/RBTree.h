#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "TableInterface.h"
#include <iostream>
#include <algorithm>

template<typename TKey, typename TValue>
class RedBlackTree : public TableInterface<TKey, TValue> {
private:
    enum Color { RED, BLACK };

    class Node {
    public:
        TRecord<TKey, TValue> data;
        Node* left;
        Node* right;
        Node* parent;
        Color color;

        Node(const TRecord<TKey, TValue>& val) : data(val), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
    };

    Node* root;

    void rotateLeft(Node*& ptr) {
        Node* rightChild = ptr->right;
        ptr->right = rightChild->left;

        if (ptr->right != nullptr)
            ptr->right->parent = ptr;

        rightChild->parent = ptr->parent;

        if (ptr->parent == nullptr)
            root = rightChild;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = rightChild;
        else
            ptr->parent->right = rightChild;

        rightChild->left = ptr;
        ptr->parent = rightChild;
    }

    void rotateRight(Node*& ptr) {
        Node* leftChild = ptr->left;
        ptr->left = leftChild->right;

        if (ptr->left != nullptr)
            ptr->left->parent = ptr;

        leftChild->parent = ptr->parent;

        if (ptr->parent == nullptr)
            root = leftChild;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = leftChild;
        else
            ptr->parent->right = leftChild;

        leftChild->right = ptr;
        ptr->parent = leftChild;
    }

    Node* _findNode(Node* root, const TKey& key) {
        Node* current = root;
        while (current != nullptr) {
            if (key < current->data.key) {
                current = current->left;
            }
            else if (current->data.key < key) {
                current = current->right;
            }
            else {
                return current;
            }
        }
        return nullptr;
    }

    Node* _replaceNode(Node* node) {
        if (node->left != nullptr && node->right != nullptr)
            return _minValueNode(node->right);
        if (node->left == nullptr && node->right == nullptr)
            return nullptr;
        if (node->left != nullptr)
            return node->left;
        else
            return node->right;
    }

    Node* _minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void _transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void _fixDelete(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->right->color == BLACK) {
                        w->left->color = RED;
                        w->color = BLACK;
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }
            }
            else {
                Node* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->left->color == BLACK) {
                        w->right->color = RED;
                        w->color = BLACK;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr) x->color = BLACK;
    }

    // Восстанавливает свойства красно-чёрного дерева после вставки
    void fixInsert(Node*& ptr) {
        Node* parent = nullptr;
        Node* grandparent = nullptr;

        while ((ptr != root) && (ptr->color != BLACK) && (ptr->parent->color == RED)) {
            parent = ptr->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    ptr = grandparent;
                }
                else {
                    if (ptr == parent->right) {
                        rotateLeft(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }
                    rotateRight(grandparent);
                    std::swap(parent->color, grandparent->color);
                    ptr = parent;
                }
            }
            else {
                Node* uncle = grandparent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    ptr = grandparent;
                }
                else {
                    if (ptr == parent->left) {
                        rotateRight(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }
                    rotateLeft(grandparent);
                    std::swap(parent->color, grandparent->color);
                    ptr = parent;
                }
            }
        }
        root->color = BLACK;
    }

    Node* insert(Node* root, Node* ptr) {
        if (root == nullptr)
            return ptr;

        if (ptr->data < root->data) {
            root->left = insert(root->left, ptr);
            root->left->parent = root;
        }
        else if (ptr->data > root->data) {
            root->right = insert(root->right, ptr);
            root->right->parent = root;
        }

        return root;
    }

    void _deleteTree(Node* node) {
        if (node == nullptr) return;
        _deleteTree(node->left);
        _deleteTree(node->right);
        delete node;
    }

    void _display(Node* node, HDC hdc, int& y, int xOffset = 10) const {
        if (node != nullptr) {
            _display(node->left, hdc, y, xOffset + 15); // Увеличиваем смещение для левых дочерних узлов

            std::ostringstream oss;
            oss << "Key: " << node->data.key << ",\tValue: " << node->data.value << ",\tColor: " << (node->color == RED ? "Red" : "Black");
            std::string itemText = oss.str();
            TabbedTextOut(hdc, 5, y, itemText.c_str(), __max(itemText.size(), 33), 2, NULL, 0);
            y += 20; // Смещаем y на 20 для следующего узла

            _display(node->right, hdc, y, xOffset); // Смещение для правых дочерних узлов
        }
    }

public:
    bool isRed(Node* node) const;
    void checkProperties(Node* node, int& blackCount, int pathBlackCount, bool& isValid) const;
    bool RedBlackTree<TKey, TValue>::checkRBTreeProperties() const;
    RedBlackTree() : root(nullptr) {}

    ~RedBlackTree() {
        _deleteTree(root);
    }

    void add(const TRecord<TKey, TValue>& record) override {
        Node* newNode = new Node(record);
        root = insert(root, newNode);
        fixInsert(newNode);
    }

    void remove(const TKey& key) override {
        Node* z = _findNode(root, key);
        if (!z) return;

        Node* y = z;
        Node* x = nullptr;
        Color y_original_color = y->color;
        if (z->left == nullptr) {
            x = z->right;
            _transplant(z, z->right);
        }
        else if (z->right == nullptr) {
            x = z->left;
            _transplant(z, z->left);
        }
        else {
            y = _minValueNode(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent != z) {
                _transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            _transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (y_original_color == BLACK && x != nullptr) {
            _fixDelete(x);
        }
    }

    TValue* find(const TKey& key) override {
        Node* current = root;
        while (current != nullptr) {
            if (key < current->data.key) {
                current = current->left;
            }
            else if (current->data.key < key) {
                current = current->right;
            }
            else {
                return &current->data.value; // Найден узел с ключом
            }
        }
        return nullptr; // Ключ не найден
    }

    void display(HDC hdc, int PosY) const override {
        int y = -PosY;
        _display(root, hdc, y);
    }
};

#endif
