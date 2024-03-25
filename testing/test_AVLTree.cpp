#include "AVLTree.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>


// Функция для проверки высоты дерева
template<typename TKey, typename TValue>
int getHeight(typename AVLTree<TKey, TValue>::Node* node) {
    if (node == nullptr) return 0;
    int leftHeight = getHeight<TKey, TValue>(node->left);
    int rightHeight = getHeight<TKey, TValue>(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Функция для проверки, является ли дерево АВЛ-сбалансированным
template<typename TKey, typename TValue>
bool isAVLBalanced(typename AVLTree<TKey, TValue>::Node* node) {
    if (node == nullptr) return true;

    int leftHeight = getHeight<TKey, TValue>(node->left);
    int rightHeight = getHeight<TKey, TValue>(node->right);

    if (abs(leftHeight - rightHeight) > 1) return false;

    return isAVLBalanced<TKey, TValue>(node->left) && isAVLBalanced<TKey, TValue>(node->right);
}

// Тест на проверку, что новосозданное дерево пусто
TEST(AVLTreeTest, IsEmptyOnCreation) {
    AVLTree<int, int> tree;
    EXPECT_EQ(tree.find(1), nullptr);
}

// Тест на добавление одного элемента и его поиск
TEST(AVLTreeTest, AddAndFindSingleElement) {
    AVLTree<int, int> tree;
    tree.add({ 1, 100 });
    int* value = tree.find(1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, 100);
}

// Тест на удаление элемента
TEST(AVLTreeTest, RemoveElement) {
    AVLTree<int, int> tree;
    tree.add({ 2, 200 });
    tree.remove(2);
    EXPECT_EQ(tree.find(2), nullptr);
}

// Тест на поиск несуществующего элемента
TEST(AVLTreeTest, FindNonExistentElement) {
    AVLTree<int, int> tree;
    tree.add({ 3, 300 });
    EXPECT_EQ(tree.find(4), nullptr);
}