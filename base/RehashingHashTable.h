#ifndef REHASHINGHASHTABLE_H
#define REHASHINGHASHTABLE_H

#include <vector>
#include <optional>
#include <functional>
#include "TableInterface.h"

// Класс хеш-таблицы с повторным перемешиванием
template<typename TKey, typename TValue>
class RehashingHashTable : public TableInterface<TRecord<TKey, TValue>> {
	using T = TRecord<TKey, TValue>;
	std::vector<std::optional<T>> data; // Используем optional для хранения возможно пустых элементов
	size_t capacity;

	// Хеширующая функция, возвращающая индекс для ключа
	size_t hashKey(const TKey& key) const {
		return std::hash<TKey>{}(key) % capacity;
	}

public:
	RehashingHashTable(size_t initCapacity = 101) : capacity(initCapacity) {
		data.resize(capacity);
	}

	void add(const T& element) override {
		size_t index = hashKey(element.key);
		while (data[index].has_value()) { // Поиск следующего пустого места при коллизии
			index = (index + 1) % capacity; // Линейное пробирование
		}
		data[index] = element;
	}

	void remove(const T& element) override {
		size_t index = hashKey(element.key);
		while (data[index].has_value() && data[index]->key != element.key) {
			index = (index + 1) % capacity; // Линейное пробирование при поиске
		}
		if (data[index].has_value()) {
			data[index].reset(); // Сброс значения, если элемент найден
		}
	}

	T* find(const T& element) const override {
		size_t index = hashKey(element.key);
		while (data[index].has_value() && data[index]->key != element.key) {
			index = (index + 1) % capacity;
		}
		if (data[index].has_value()) {
			return &data[index].value();
		}
		return nullptr;
	}

	void display() const override {
		for (const auto& item : data) {
			if (item.has_value()) {
				std::cout << "Key: " << item->key << ", Value: " << item->value << std::endl;
			}
		}
	}
};

#endif // REHASHINGHASHTABLE_H
