#ifndef LINEARLISTTABLE_H
#define LINEARLISTTABLE_H

#include "TableInterface.h"
#include <list>
#include <iostream>

template<typename TKey, typename TValue>
class TLinearListTable : public TableInterface<TKey, TValue> {
	using T = TRecord<TKey, TValue>;
	std::list<T> data;

public:
	TLinearListTable() = default;

	void add(const TRecord<TKey, TValue>& record) override {
		data.push_back(record);
	}

	void remove(const TKey& key) override {
		auto it = data.begin();
		while (it != data.end()) {
			if (it->key == key) {
				it = data.erase(it);
			}
			else {
				++it;
			}
		}
	}

	TValue* find(const TKey& key) override {
		for (auto& record : data) {
			if (record.key == key) {
				return &(record.value);
			}
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

#endif // LINEARLISTTABLE_H
