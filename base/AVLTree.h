#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

template <typename T>
class AVLTree {
    class Node {
    public:
        T data;
        Node* left; // Левый потомок
        Node* right; // Правый потомок
        int height; // Высота узла

        Node(T data, Node* left = nullptr, Node* right = nullptr, int height = 1);
    };

    Node* root; // Корень дерева

    Node* rotateRight(Node* y); // Правый поворот
    Node* rotateLeft(Node* x); // Левый поворот
    int getHeight(Node* N); // Получение высоты узла
    int getBalance(Node* N); // Получение баланса узла
    Node* insert(Node* node, const T& key); // Вставка узла
    Node* minValueNode(Node* node); // Поиск узла с минимальным значением
    Node* deleteNode(Node* root, const T& key); // Удаление узла
public:
    AVLTree();
    ~AVLTree();

    void add(const T& element);
    void remove(const T& element);
    bool find(const T& element) const;
    void display() const;
};

#endif