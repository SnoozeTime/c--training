#ifndef HASHMAP_HPP
#define HASHMAP_HPP

/*
    See here
    https://medium.com/@aozturk/simple-hash-map-hash-table-implementation-in-c-931965904250#.xu44t3gld
*/
unsigned long TABLE_SIZE = 100;

// The node of the hashmap
template<typename K, typename V>
class HashNode
{
public:
    HashNode(K key, V value):
        key_(key),
        value_(value),
        next_(nullptr)
    {
    }

    K key() const
    {
        return key_;
    }

    void set_key(K key)
    {
        key_ = key;
    }

    V value() const
    {
        return value_;
    }

    void set_value(V value)
    {
        value_ = value;
    }

    HashNode* next() const
    {
        return next_;
    }

    void set_next(HashNode<K,V>* node)
    {
        next_ = node;
    }

private:
    /*
        Key, which will be input into the hash function to get the index of the
        value
    */
    K key_;

    /*
        Data to retrieve
    */
    V value_;

    /*
        Next bucket with the same key
    */
    HashNode<K,V>* next_;
};


/*
    The hash function. Get index from K
*/
template <typename K>
struct KeyHash {
    unsigned long operator()(const K& key) const
    {
        return reinterpret_cast<unsigned long>(key) % TABLE_SIZE;
    }
};

#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
unsigned hash_str(const char* s)
{
   unsigned h = 31 /* also prime */;
   while (*s) {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   return h; // or return h % C;
}

/*
    Now the map
*/
template <typename K, typename V, typename F = KeyHash<K>>
class HashMap
{
public:
    HashMap()
    {
        // Initialize the table.
        table_ = new HashNode<K,V>* [TABLE_SIZE]();
    }

    ~HashMap()
    {
        // destroy all buckets one by one
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode<K,V> *entry = table_[i];
            while (entry != nullptr) {
                HashNode<K,V>* prev = entry;
                entry = entry->next();
                delete prev;
            }
            table_[i] = nullptr;
        }

        // destroy hash table
        delete[] table_;
    }

    bool get(const K& key, V& value)
    {
        unsigned long hashvalue = HashFunc(key);
        HashNode<K, V> *entry = table_[hashvalue];

        while (entry != nullptr) {
            if (key == entry->key()) {
                value = entry->value();
                return true;
            }
            entry = entry->next();
        }

        return false;
    }

    void put(const K& key, const V& value)
    {
        unsigned long hashvalue = HashFunc(key);
        HashNode<K, V> *entry = table_[hashvalue];
        HashNode<K, V> *prev = nullptr;

        while (entry != nullptr && entry->key() != key) {
            prev = entry;
            entry = entry->next();
        }

        /*
            Two cases. Either the entry is null so it means there are not entry
            with the given key in our bucket, or the entry is not null and we
            are overriding the value.
        */
        if (entry == nullptr) {
            entry = new HashNode<K,V>(key, value);
            if (prev == nullptr) {
                table_[hashvalue] = entry;
            } else {
                prev->set_next(entry);
            }
        } else {
            entry->set_value(value);
        }
    }

    bool remove(const K &key)
    {
        unsigned long hashvalue = HashFunc(key);
        HashNode<K, V> *entry = table_[hashvalue];
        HashNode<K, V> *prev = nullptr;

        while (entry != nullptr && entry.key() != key) {
            prev = entry;
            entry = entry->next();
        }

        if (entry == nullptr) {
            // No entry
            return false;
        } else {
            if (prev == nullptr) {
                table_[hashvalue] = entry->next();
            } else {
                prev->set_next(entry->next());
            }
            delete entry;
        }
    }

private:
    // our buckets. index is the hash value return by HashFunc
    HashNode<K,V> **table_;

    // Hash function
    F HashFunc;
};


#endif
