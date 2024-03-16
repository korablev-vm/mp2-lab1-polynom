﻿#ifndef TABLEINTERFACE_H
#define TABLEINTERFACE_H

template<typename T>
class TableInterface {
public:
	virtual ~TableInterface() = default;
	virtual void add(const T& element) = 0;
	virtual void remove(const T& element) = 0;
	virtual T* find(const T& element) const = 0;
	virtual void display() const = 0;
};

template<typename TKey, typename TValue>
struct TRecord {
	TKey key;
	TValue value;
};

#endif // TABLEINTERFACE_H