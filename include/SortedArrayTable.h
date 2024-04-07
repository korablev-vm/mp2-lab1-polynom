#ifndef SORTEDARRAYTABLE_H
#define SORTEDARRAYTABLE_H

#include "TableInterface.h"
#include <algorithm>
#include <vector>
#include <iostream>

template<typename TKey, typename TValue>
class TSortedTable : public TableInterface<TKey, TValue> {
	using T = TRecord<TKey, TValue>;
	std::vector<T> data;

public:
	TSortedTable() = default;

	void add(const TRecord<TKey, TValue>& record) override {
		auto it = std::lower_bound(data.begin(), data.end(), record);
		if (it == data.end() || it->key != record.key) {
			data.insert(it, record);
		}
	}

	void remove(const TKey& key) override {
		T element{ key, TValue() };
		auto it = std::lower_bound(data.begin(), data.end(), element);
		if (it != data.end() && it->key == key) {
			data.erase(it);
		}
	}

	TValue* find(const TKey& key) override {
		T element{ key, TValue() };
		auto it = std::lower_bound(data.begin(), data.end(), element);
		if (it != data.end() && it->key == key) {
			return const_cast<TValue*>(&it->value);
		}
		return nullptr;
	}

	void display(HDC hdc, int PosY) const override {
		int y = -PosY;
		for (const auto& item : data) {
			std::ostringstream oss;
			oss << "Key: " << item.key << ",\tValue: " << item.value;
			std::string text = oss.str();
			TabbedTextOut(hdc, 5, y, text.c_str(), __max(text.size(), 20), 1, NULL, 0);
			y += 20;
		}
	}
};

#endif // SORTEDARRAYTABLE_H