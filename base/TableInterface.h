#ifndef TABLEINTERFACE_H
#define TABLEINTERFACE_H

template<typename TKey, typename TValue>
class TableInterface {
public:
	virtual ~TableInterface() = default;
	virtual void add(const TKey& key, const TValue& value) = 0;
	virtual void remove(const TKey& key) = 0;
	virtual TValue* find(const TKey& key) const = 0;
	virtual void display() const = 0;
};

template<typename TKey, typename TValue>
struct TRecord {
	TKey key;
	TValue value;

	bool operator<(const TRecord& other) const {
		return key < other.key;
	}

	bool operator==(const TRecord& other) const {
		return key == other.key;
	}
};

#endif // TABLEINTERFACE_H