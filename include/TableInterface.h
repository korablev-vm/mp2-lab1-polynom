#ifndef TABLEINTERFACE_H
#define TABLEINTERFACE_H

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

template<typename TKey, typename TValue>
class TableInterface {
public:
    virtual ~TableInterface() = default;
    virtual void add(const TRecord<TKey, TValue>& record) = 0;
    virtual void remove(const TKey& key) = 0;
    virtual TValue* find(const TKey& key) = 0;
    virtual void display() const = 0;
};

#endif // TABLEINTERFACE_H