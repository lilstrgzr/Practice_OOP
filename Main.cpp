#include <iostream>
#include <initializer_list>

template <typename key, typename value>
class Map {

private:
    struct Pair {
        key first;
        value second;

        Pair() : first(), second() {}
        Pair(const key& key, const value& value) : first(key), second(value) {}
    };

    Pair* pairs;
    size_t capacity;
    size_t CSize;

    void setDefaults() {
        pairs = nullptr;
        capacity = 0;
        CSize = 0;
    }

public:

    Map() { setDefaults(); }

    Map(const Map& other) : capacity(other.CSize), CSize(other.CSize) {
        pairs = new Pair[CSize];
        for (size_t i = 0; i < CSize; ++i) {
            pairs[i] = other.pairs[i];
        }
    }

    Map(const std::initializer_list<std::pair<key, value>>& initList) : capacity(initList.size()), CSize(0) {
        pairs = new Pair[capacity];
        for (auto& p : initList) {
            pairs[CSize++] = Pair(p.first, p.second);
        }
    }

    ~Map() {
        delete[] pairs;
    }

    void new_Size() {
        capacity = capacity == 0 ? 1 : capacity * 2;
        Pair* newPairs = new Pair[capacity];
        for (size_t i = 0; i < CSize; ++i) {
            newPairs[i] = pairs[i];
        }
        delete[] pairs;
        pairs = newPairs;
    }

    void setItem(const key& key, const value& value) {
        for (size_t i = 0; i < CSize; ++i) {
            if (pairs[i].first == key) {
                pairs[i].second = value;
                return;
            }
        }
        if (CSize >= capacity) {
            new_Size();
        }
        pairs[CSize++] = Pair(key, value);
    }

    value& operator[](const key& key) {
        for (size_t i = 0; i < CSize; ++i) {
            if (pairs[i].first == key) {
                return pairs[i].second;
            }
        }

        if (CSize >= capacity) {
            new_Size();
        }
        pairs[CSize] = Pair(key, value());
        return pairs[CSize++].second;
    }

    void clear() {
        delete[] pairs;
        setDefaults();
    }

    size_t size() const {
        return CSize;
    }
};

int main() {
    setlocale(LC_ALL, "russian");
    Map<int, std::string> map1;
    map1.setItem(98, "Travis Scott");
    map1.setItem(30, "Kendrick Lamar");
    map1.setItem(109, "Snoop Doog");

    std::cout << map1[109] << std::endl;
    std::cout << map1[1] << std::endl;
    std::cout << map1[98] << std::endl;
    std::cout << "Размер: " << map1.size() << std::endl;

    map1.clear();
    std::cout << "Размер после очищения: " << map1.size() << std::endl;

    return 0;
}