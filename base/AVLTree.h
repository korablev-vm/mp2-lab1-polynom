#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

template <typename T>
class AVLTree {
    class Node {
    public:
        T data;
        Node* left; // ����� �������
        Node* right; // ������ �������
        int height; // ������ ����

        Node(T data, Node* left = nullptr, Node* right = nullptr, int height = 1);
    };

    Node* root; // ������ ������

    Node* rotateRight(Node* y); // ������ �������
    Node* rotateLeft(Node* x); // ����� �������
    int getHeight(Node* N); // ��������� ������ ����
    int getBalance(Node* N); // ��������� ������� ����
    Node* insert(Node* node, const T& key); // ������� ����
    Node* minValueNode(Node* node); // ����� ���� � ����������� ���������
    Node* deleteNode(Node* root, const T& key); // �������� ����
public:
    AVLTree();
    ~AVLTree();

    void add(const T& element);
    void remove(const T& element);
    bool find(const T& element) const;
    void display() const;
};

#endif