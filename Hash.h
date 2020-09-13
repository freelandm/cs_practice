#pragma once

#include <iomanip>
#include <limits>

namespace experiment
{
/*
 * 9/10/2020:
 *
 * initial implementation will just support integers
 *
 * We'll need to come up with a mechanism (maybe our own wrapper classes)
 * that will use a custom hash, implementing the std::hash
 *
 */

const size_t default_capacity = 25;

template <typename KeyT>
class Hash
{
public:
    Hash() : Hash(default_capacity)
    {

    }
    Hash(int capacity) : m_capacity(capacity)
    {
        initialize();
    }
    ~Hash() = default;

    class Entry {
    public:
        Entry(KeyT key) : m_key(key) { }
        Entry() = default;
        void SetKey(KeyT key)
        {
            m_key = key;
            m_empty = false;
            m_deleted = false;
        }
        void Delete()
        {
            m_deleted = true;
        }
        const auto& GetKey() const { return m_key; }
        auto IsDeleted() const { return m_deleted; }
        auto IsEmpty() const { return m_empty; }

    private:
        KeyT m_key;
        bool m_deleted{false};
        bool m_empty{true};
    };

    bool insert(KeyT key) {
        if (full()) {
            std::cout << "Cannot insert " << key << ", the hash is at capacity." << std::endl;
            return false;
        }
        std::size_t start = get_hash(key);
        std::size_t current = start;
        do {
            auto& entry = m_entries[current];
            if (entry.IsDeleted() || entry.IsEmpty()) {
                ++m_size;
                entry.SetKey(key);
                std::cout << "Inserted " << key << " at location " << current << std::endl;
                return true;
            }
            else if (entry.GetKey() == key) {// stop
                // found the value
                std::cout << "Key " << key << " already exists.\n";
                return false;
            }
            ++current%=m_capacity;
        } while (current != start);
        return false;
    }
    std::size_t find(KeyT key) {
        std:: cout << " searching for key " << key << std::endl;
        std::size_t start = get_hash(key);
        std::size_t current = start;
        do {
            auto& entry = m_entries[current];
            if (entry.IsEmpty()) {
                return std::numeric_limits<int>::max();
            }
            else if (entry.GetKey() == key) {
                return current;
            }
        } while (current != start);
        return std::numeric_limits<int>::max();
    }
    bool erase(KeyT key) {
        std::cout << std::quoted("erase") << key << std::endl;
        auto location = find(key);
        if (location != std::numeric_limits<int>::max()) {
            m_entries[location].Delete();
            --m_size;
            std::cout << "Deleted key " << key << " at location " << location << std::endl;
            return true;
        }
        else {
            std::cout << "Cannot delete " << key << ", it does not exist." << std::endl;
            return false;
        }
    }

    auto size() const { return m_size; }
    auto capacity() const { return m_capacity; }
    bool full() const { return m_size >= m_capacity; }

private:
    void initialize()
    {
        m_entries = new Entry[m_capacity];
    }
    // very simple hash. it's not going to give us anything remarkable in terms of quality here
    std::size_t get_hash(KeyT key)
    {
        return std::hash<KeyT>{}(key) % m_capacity;
    }
private:
    size_t m_capacity;
    size_t m_size{0};
    Entry* m_entries{nullptr};
};

};
