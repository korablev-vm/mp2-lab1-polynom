#include <vector>
#include <memory>
#include <stdexcept>
#include "TableInterface.h"

template<typename T>
class TableManager {
private:
    std::vector<std::shared_ptr<TableInterface<T>>> tables;
    int activeTableIndex = 0;

public:
    void addTable(std::shared_ptr<TableInterface<T>> table) {
        tables.push_back(table);
        if (tables.size() == 1) {
            setActiveTable(0);
        }
    }

    // Установка активной таблицы для операций поиска и отображения
    void setActiveTable(int index) {
        if (index < 0 || index >= tables.size()) {
            throw std::out_of_range("Индекс активной таблицы вне допустимого диапазона");
        }
        activeTableIndex = index;
    }

    void add(const T& element) {
        if (tables.empty()) {
            throw std::runtime_error("Нет добавленных таблиц для операции добавления");
        }
        for (auto& table : tables) {
            table->add(element);
        }
    }

    void remove(const T& element) {
        if (tables.empty()) {
            throw std::runtime_error("Нет добавленных таблиц для операции удаления");
        }
        for (auto& table : tables) {
            table->remove(element);
        }
    }

    T* find(const T& element) const {
        if (tables.empty()) {
            throw std::runtime_error("Нет добавленных таблиц для операции поиска");
        }
        return tables[activeTableIndex]->find(element);
    }

    void display() const {
        if (tables.empty()) {
            throw std::runtime_error("Нет добавленных таблиц для операции отображения");
        }
        tables[activeTableIndex]->display();
    }
};
