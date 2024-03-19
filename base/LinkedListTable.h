#ifndef LINEARLISTTABLE_H
#define LINEARLISTTABLE_H

#include "TableInterface.h"
#include "List.h"
#include <iostream>
using namespace std;

template<typename TKey, typename TValue>
class TLinearListTable {
	using T = TRecord<TKey, TValue>;
	List<T> data;

public:
	TLinearListTable() = default;

	void add(const T& element) {
		data.insertInOrder(element);
	}

	void remove(const TKey& key) {
		for (int i = 0; i < data.size(); ++i) {
			if (data[i].key == key) {
				data.erase(i);
				return;
			}
		}
	}

	T* find(const TKey& key) {
		for (int i = 0; i < data.size(); ++i) {
			if (data[i].key == key) {
				return &data[i];
			}
		}
		return nullptr;
	}

	void display() const {
		for (int i = 0; i < data.size(); ++i) {
			cout << "Key: " << data[i].key << ", Value: " << data[i].value << endl;
		}
	}
};

#endif // LINEARLISTTABLE_H
