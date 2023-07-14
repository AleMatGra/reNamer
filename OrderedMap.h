#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

template<typename Key, typename Value>
class OrderedMap
{
    private:
        typedef typename std::map<Key, Value>::iterator iterator;
        typedef typename std::map<Key, Value>::const_iterator const_iterator;
        typedef typename std::vector<Key>::iterator order_iterator;

    private:
        std::map<Key, Value> map;
        std::vector<Key> insertionOrder;

    public:
        void insert(const Key& key, const Value& value)
        {
            map[key] = value;
            insertionOrder.push_back(key);
        }

        Value& operator[](const Key& key)
        {
            return map[key];
        }

        Value& at(const Key& key)
        {
            return map.at(key);
        }

        const std::vector<Key>& getOrder() const
        {
            return insertionOrder;
        }

        iterator begin()
        {
            return map.begin();
        }

        iterator end()
        {
            return map.end();
        }

        const_iterator begin() const
        {
            return map.begin();
        }

        const_iterator end() const
        {
            return map.end();
        }

        order_iterator beginOrder()
        {
            return insertionOrder.begin();
        }

        order_iterator endOrder()
        {
            return insertionOrder.end();
        }
};