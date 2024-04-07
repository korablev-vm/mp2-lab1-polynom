#include "RBTree.h"
#include <gtest.h>

// Проверка, что новое дерево пустое
TEST(RedBlackTree, IsEmptyInitially) {
    RedBlackTree<int, int> tree;
    EXPECT_EQ(tree.find(10), nullptr);
}

// Проверка вставки одного элемента
TEST(RedBlackTree, CanInsertSingleElement) {
    RedBlackTree<int, int> tree;
    tree.add({ 10, 100 });
    ASSERT_NE(tree.find(10), nullptr);
    EXPECT_EQ(*tree.find(10), 100);
}

// Проверка удаления несуществующего элемента
TEST(RedBlackTree, DeleteNonExistentElement) {
    RedBlackTree<int, int> tree;
    tree.remove(10);  // Удаление несуществующего элемента
    EXPECT_EQ(tree.find(10), nullptr);
}

// Проверка множественной вставки и удаления
TEST(RedBlackTree, MultipleInsertionsAndDeletions) {
    RedBlackTree<int, int> tree;
    tree.add({ 10, 100 });
    tree.add({ 20, 200 });
    tree.add({ 30, 300 });
    tree.add({ 40, 400 });
    tree.add({ 50, 500 });

    tree.remove(30);
    tree.remove(10);
    ASSERT_EQ(tree.find(10), nullptr);
    ASSERT_NE(tree.find(20), nullptr);
    ASSERT_EQ(tree.find(30), nullptr);
    ASSERT_NE(tree.find(40), nullptr);
    ASSERT_NE(tree.find(50), nullptr);
}

// Проверка на сохранение свойств красно-чёрного дерева после вставки
TEST(RedBlackTree, PropertiesAfterInsertions) {
    RedBlackTree<int, int> tree;
    for (int i = 1; i <= 10; ++i) {
        tree.add({ i, i * 100 });
    }
    // Этот тест должен быть дополнен проверками на соответствие свойствам красно-чёрного дерева
}

// Проверка на сохранение свойств красно-чёрного дерева после удаления
TEST(RedBlackTree, PropertiesAfterDeletions) {
    RedBlackTree<int, int> tree;
    for (int i = 1; i <= 10; ++i) {
        tree.add({ i, i * 100 });
    }
    for (int i = 1; i <= 10; i += 2) {
        tree.remove(i);
    }
    // Этот тест должен быть дополнен проверками на соответствие свойствам красно-чёрного дерева
}

// Тест на проверку вставки и базового поиска
TEST(RedBlackTree, InsertAndFind) {
    RedBlackTree<int, int> tree;
    tree.add({ 10, 100 });
    tree.add({ 20, 200 });
    tree.add({ 5, 50 });

    EXPECT_EQ(*tree.find(10), 100);
    EXPECT_EQ(*tree.find(20), 200);
    EXPECT_EQ(*tree.find(5), 50);
    EXPECT_EQ(tree.find(15), nullptr);
}

//// Тест на проверку сохранения свойств красно-черного дерева после вставки
//TEST(RedBlackTree, PropertiesAfterInsert) {
//    RedBlackTree<int, int> tree;
//    for (int i = 1; i <= 100; i++) {
//        tree.add({ i, i * 10 });
//    }
//    // Здесь должна быть функция, проверяющая свойства КЧ дерева
//    EXPECT_TRUE(checkRBTreeProperties(tree));
//}
//
//// Тест на проверку удаления элементов
//TEST(RedBlackTree, Deletion) {
//    RedBlackTree<int, int> tree;
//    tree.add({ 10, 100 });
//    tree.add({ 20, 200 });
//    tree.add({ 5, 50 });
//    tree.add({ 1, 10 });
//    tree.add({ 30, 300 });
//
//    tree.remove(10);
//    EXPECT_EQ(tree.find(10), nullptr);
//    EXPECT_NE(tree.find(5), nullptr);
//    EXPECT_NE(tree.find(20), nullptr);
//    EXPECT_TRUE(checkRBTreeProperties(tree));
//}

template<typename TKey, typename TValue>
bool RedBlackTree<TKey, TValue>::isRed(Node* node) const {
    return node != nullptr && node->color == RED;
}

template<typename TKey, typename TValue>
void RedBlackTree<TKey, TValue>::checkProperties(Node* node, int& blackCount, int pathBlackCount, bool& isValid) const {
    if (node == nullptr) {
        // Проверка на черную высоту
        if (blackCount == -1) {
            blackCount = pathBlackCount;
        }
        else if (blackCount != pathBlackCount) {
            isValid = false;
        }
        return;
    }

    // Красные узлы не должны иметь красных детей
    if (isRed(node)) {
        if (isRed(node->left) || isRed(node->right)) {
            isValid = false;
        }
    }
    else {
        pathBlackCount++;  // Увеличиваем счетчик черных узлов, если узел черный
    }

    // Рекурсивная проверка детей
    checkProperties(node->left, blackCount, pathBlackCount, isValid);
    checkProperties(node->right, blackCount, pathBlackCount, isValid);
}

template<typename TKey, typename TValue>
bool RedBlackTree<TKey, TValue>::checkRBTreeProperties() const {
    int blackCount = -1;  // Счетчик черных узлов на пути
    int pathBlackCount = 0;  // Черные узлы на текущем пути
    bool isValid = true;  // Валидность дерева

    if (root != nullptr && root->color != BLACK) {
        return false;  // Корень должен быть черным
    }

    checkProperties(root, blackCount, pathBlackCount, isValid);
    return isValid;
}