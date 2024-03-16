#ifndef CHAININGHASHTABLE_H
#define CHAININGHASHTABLE_H

#include <vector>
#include <list>
#include <functional>
#include "TableInterface.h"

// Класс хеш-таблицы с разрешением коллизий методом цепочек
template<typename TKey, typename TValue>
class ChainingHashTable : public TableInterface<TRecord<TKey, TValue>> {
	using T = TRecord<TKey, TValue>;
	std::vector<std::list<T>> data; // Вектор списков для хранения элементов с одинаковыми хешами
	size_t capacity; // Максимальное количество "корзин" в таблице

	size_t hashKey(const TKey& key) const {
		return std::hash<TKey>{}(key) % capacity;
	}

public:
	ChainingHashTable(size_t initCapacity = 101) : capacity(initCapacity) {
		data.resize(capacity);
	}

	void add(const T& element) override {
		size_t index = hashKey(element.key);
		data[index].push_back(element);
	}

	void remove(const T& element) override {
		size_t index = hashKey(element.key);
		auto& chain = data[index];
		chain.remove_if([&element](const T& item) { return item.key == element.key; });
	}

	T* find(const T& element) const override {
		size_t index = hashKey(element.key);
		const auto& chain = data[index];
		for (const auto& item : chain) {
			if (item.key == element.key) {
				return &const_cast<T&>(item);
			}
		}
		return nullptr;
	}

	void display() const override {
		for (const auto& chain : data) {
			for (const auto& item : chain) {
				std::cout << "Key: " << item.key << ", Value: " << item.value << std::endl;
			}
		}
	}
};

#endif // CHAININGHASHTABLE_H
