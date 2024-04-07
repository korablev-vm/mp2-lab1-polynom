#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <vector>
#include <memory>
#include <stdexcept>
#include "TableInterface.h"

template<typename TKey, typename TValue>
class TableManager {
private:
    std::vector<std::shared_ptr<TableInterface<TKey, TValue>>> tables;
    int activeTableIndex = -1; // Изначально нет активной таблицы

public:
    void addTable(std::shared_ptr<TableInterface<TKey, TValue>> table) {
        tables.push_back(table);
        if (tables.size() == 1) {
            setActiveTable(0);
        }
    }

    void setActiveTable(int index) {
        if (index < 0 || index >= tables.size()) {
            throw std::out_of_range("Индекс активной таблицы вне допустимого диапазона");
        }
        activeTableIndex = index;
    }

    void add(const TRecord<TKey, TValue>& record) {
        if (tables.empty()) {
            throw std::runtime_error("Нет добавленных таблиц для операции добавления");
        }
        tables[activeTableIndex]->add(record);
    }

    void remove(const TKey& key) {
        if (tables.empty()) {
            throw std::runtime_error("Нет добавленных таблиц для операции удаления");
        }
        tables[activeTableIndex]->remove(key);
    }

    void addAll(const TRecord<TKey, TValue>& record) {
        for (auto& table : tables) {
            table->add(record);
        }
    }

    void removeAll(const TKey& key) {
        for (auto& table : tables) {
            table->remove(key);
        }
    }

    TValue* find(const TKey& key) const {
        if (tables.empty()) {
            throw std::runtime_error("Нет добавленных таблиц для операции поиска");
        }
        return tables[activeTableIndex]->find(key);
    }

    void display(HDC hdc, int PosY) const {
        if (tables.empty()) {
            throw std::runtime_error("Нет добавленных таблиц для операции отображения");
        }
        if (activeTableIndex >= 0) {
            tables[activeTableIndex]->display(hdc, PosY);
        }
    }
};

#endif // TABLEMANAGER_H