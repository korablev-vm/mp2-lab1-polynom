#ifndef REHASHINGHASHTABLE_H
#define REHASHINGHASHTABLE_H

#include <vector>
#include <functional>
#include <iostream>
#include "TableInterface.h"

template<typename TKey, typename TValue>
class RehashingHashTable : public TableInterface<TKey, TValue> {
	using T = TRecord<TKey, TValue>;
	std::vector<std::pair<bool, T>> data; // пара для хранения возможно пустых элементов
	size_t capacity;

	size_t hashKey(const TKey& key) const {
		return std::hash<TKey>{}(key) % capacity;
	}

public:
	RehashingHashTable(size_t initCapacity = 101) : capacity(initCapacity) {
		data.resize(capacity, { false, T() });
	}

	void add(const TRecord<TKey, TValue>& record) override {
		size_t index = hashKey(record.key);
		while (data[index].first) {
			if (data[index].second.key == record.key) {
				data[index].second = record;
				return;
			}
			index = (index + 1) % capacity;
		}
		data[index] = { true, record };
	}

	void remove(const TKey& key) override {
		size_t index = hashKey(key);
		while (data[index].first && data[index].second.key != key) {
			index = (index + 1) % capacity;
		}
		if (data[index].first) {
			data[index].first = false;
		}
	}

	TValue* find(const TKey& key) override {
		size_t index = hashKey(key);
		while (data[index].first && data[index].second.key != key) {
			index = (index + 1) % capacity;
		}
		if (data[index].first) {
			return &(data[index].second.value);
		}
		return nullptr;
	}

	void display(HDC hdc, int PosY) const override {
		int y = -PosY;
		for (const auto& item : data) {
			if (item.first) {
				std::ostringstream oss;
				oss << "Key: " << item.second.key << ",\tValue: " << item.second.value;
				std::string text = oss.str();
				TabbedTextOut(hdc, 5, y, text.c_str(), __max(text.size(), 20), 1, NULL, 0);
				y += 20;
			}
		}
	}
};

#endif // REHASHINGHASHTABLE_H
