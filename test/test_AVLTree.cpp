#include "AVLTree.h"
#include <gtest.h>

// Тест проверяет добавление и поиск элементов в AVL-дереве
TEST(AVLTreeTest, AddAndFind) {
    AVLTree<int, std::string> tree;

    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 2, "Value2" };
    tree.add(record1);
    tree.add(record2);

    EXPECT_EQ(*tree.find(1), "Value1");
    EXPECT_EQ(*tree.find(2), "Value2");
}

// Тест проверяет удаление элементов из AVL-дерева
TEST(AVLTreeTest, Remove) {
    AVLTree<int, std::string> tree;

    TRecord<int, std::string> record1 = { 1, "Value1" };
    tree.add(record1);
    tree.remove(1);

    EXPECT_EQ(tree.find(1), nullptr);
}

// Тест проверяет корректность обработки дублирующихся ключей
TEST(AVLTreeTest, AddDuplicate) {
    AVLTree<int, std::string> tree;

    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 1, "Value2" };
    tree.add(record1);
    tree.add(record2);

    EXPECT_EQ(*tree.find(1), "Value1");
}

// Тест проверяет поиск элемента, которого нет в AVL-дереве
TEST(AVLTreeTest, FindNonExistent) {
    AVLTree<int, std::string> tree;

    EXPECT_EQ(tree.find(1), nullptr);
}

// Тест проверяет отображение содержимого AVL-дерева
TEST(AVLTreeTest, Display) {
    AVLTree<int, std::string> tree;

    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 2, "Value2" };
    tree.add(record1);
    tree.add(record2);

    // Перенаправление вывода для проверки отображения
    std::stringstream output;
    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    // Отображение дерева
    tree.display();

    std::cout.rdbuf(coutBuffer); // Восстановление вывода

    // Проверка корректности вывода
    std::string expectedOutput = "Key: 1, Value: Value1\nKey: 2, Value: Value2\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

// Тест проверяет добавление и удаление нескольких элементов из AVL-дерева
TEST(AVLTreeTest, AddRemoveMultiple) {
    AVLTree<int, std::string> tree;

    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 2, "Value2" };
    TRecord<int, std::string> record3 = { 3, "Value3" };

    tree.add(record1);
    tree.add(record2);
    tree.add(record3);

    tree.remove(2);
    tree.remove(3);

    EXPECT_EQ(tree.find(2), nullptr);
    EXPECT_EQ(tree.find(3), nullptr);
}

// Тест проверяет удаление всех элементов из AVL-дерева
TEST(AVLTreeTest, AddRemoveAll) {
    AVLTree<int, std::string> tree;

    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 2, "Value2" };
    TRecord<int, std::string> record3 = { 3, "Value3" };

    tree.add(record1);
    tree.add(record2);
    tree.add(record3);

    tree.remove(1);
    tree.remove(2);
    tree.remove(3);

    EXPECT_EQ(tree.find(1), nullptr);
    EXPECT_EQ(tree.find(2), nullptr);
    EXPECT_EQ(tree.find(3), nullptr);
}

// Тест проверяет корректность обработки дублирующихся ключей при добавлении
TEST(AVLTreeTest, AddRemoveDuplicateKeys) {
    AVLTree<int, std::string> tree;

    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 1, "Value2" };

    tree.add(record1);
    tree.add(record2);

    EXPECT_EQ(*tree.find(1), "Value1");

    tree.remove(1);

    EXPECT_EQ(tree.find(1), nullptr);
}

// Тест проверяет добавление и поиск элементов с коллизиями ключей
TEST(AVLTreeTest, AddFindWithCollision) {
    AVLTree<int, std::string> tree;

    // Добавление элементов с коллизиями ключей
    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 6, "Value6" };
    TRecord<int, std::string> record3 = { 11, "Value11" };
    TRecord<int, std::string> record4 = { 16, "Value16" };

    tree.add(record1);
    tree.add(record2);
    tree.add(record3);
    tree.add(record4);

    // Проверка наличия добавленных элементов
    EXPECT_EQ(*tree.find(1), "Value1");
    EXPECT_EQ(*tree.find(6), "Value6");
    EXPECT_EQ(*tree.find(11), "Value11");
    EXPECT_EQ(*tree.find(16), "Value16");
}

// Тест проверяет работу метода удаления на пустом дереве
TEST(AVLTreeTest, RemoveFromEmptyTree) {
    AVLTree<int, std::string> tree;

    // Удаление элемента из пустого дерева
    tree.remove(1);

    // Ожидается, что ничего не изменится
    EXPECT_EQ(tree.find(1), nullptr);
}

// Тест проверяет добавление и поиск большого количества элементов
TEST(AVLTreeTest, AddAndFindLargeNumber) {
    AVLTree<int, std::string> tree;

    const int numElements = 1000;

    // Добавление большого количества элементов
    for (int i = 0; i < numElements; ++i) {
        TRecord<int, std::string> record = { i, "Value" + std::to_string(i) };
        tree.add(record);
    }

    // Проверка наличия добавленных элементов
    for (int i = 0; i < numElements; ++i) {
        EXPECT_EQ(*tree.find(i), "Value" + std::to_string(i));
    }
}

// Тест проверяет добавление, удаление и поиск случайных элементов
TEST(AVLTreeTest, AddRemoveFindRandom) {
    AVLTree<int, std::string> tree;

    // Добавление элементов с ключами от 0 до 99
    for (int i = 0; i < 100; ++i) {
        TRecord<int, std::string> record = { i, "Value" + std::to_string(i) };
        tree.add(record);
    }

    // Удаление четных элементов
    for (int i = 0; i < 100; ++i) {
        if (i % 2 == 0) {
            tree.remove(i);
        }
    }

    // Проверка наличия добавленных элементов
    for (int i = 0; i < 100; ++i) {
        if (i % 2 == 0) {
            EXPECT_EQ(tree.find(i), nullptr);
        }
        else {
            EXPECT_EQ(*tree.find(i), "Value" + std::to_string(i));
        }
    }
}