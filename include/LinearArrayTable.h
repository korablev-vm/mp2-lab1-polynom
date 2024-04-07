#ifndef LINEARARRAYTABLE_H
#define LINEARARRAYTABLE_H

#include <algorithm>
#include <iostream>
#include "TableInterface.h"

template<typename TKey, typename TValue>
class TUnorderedTable : public TableInterface<TKey, TValue> {
    using T = TRecord<TKey, TValue>;
    std::vector<T> data;

public:
    TUnorderedTable() = default;

    void add(const TRecord<TKey, TValue>& record) override {
        auto it = std::find_if(data.begin(), data.end(), [&record](const T& item) { return item.key == record.key; });
        if (it == data.end()) {
            data.push_back(record);
        }
    }

    void remove(const TKey& key) override {
        auto it = std::find_if(data.begin(), data.end(), [&key](const T& item) { return item.key == key; });
        if (it != data.end()) {
            data.erase(it);
        }
    }

    TValue* find(const TKey& key) override {
        auto it = std::find_if(data.begin(), data.end(), [&key](const T& item) { return item.key == key; });
        if (it != data.end()) {
            return &(it->value);
        }
        return nullptr;
    }

    void display(HDC hdc, int PosY) const override {
        int y = -PosY;
        for (const auto& record : data) {
            std::ostringstream oss;
            oss << "Key: " << record.key << ",\tValue: " << record.value;
            std::string text = oss.str();
            TabbedTextOut(hdc, 5, y, text.c_str(), __max(text.size(), 20), 1, NULL, 0);
            y += 20;
        }
    }
};

#endif // LINEARARRAYTABLE_H