
namespace lasd {

/* ************************************************************************** */

#include <string>

/* ************************************************************************** */

template<>
class Hash<int> {

public: 
    ulong operator()(const int& data) const noexcept {
        return (data * data);
    }

};

template<>
class Hash<double> {

public: 
    ulong operator()(const double& data) const noexcept {
        long integer_part = floor(data);
        long fractional_part = pow(2, 24) * (data - integer_part);
        return (integer_part * fractional_part);
    }

};

template<>
class Hash<std::string> {

public: 
    ulong operator()(const std::string& data) const noexcept {
        ulong hash = 5381; 
        for (ulong i = 0; i < data.length(); ++i) {
            hash = (hash << 5) + data[i]; 
        }
        return hash;
    }
};

template<typename Data>
HashTable<Data>::HashTable() {
    size = 0;
    std::default_random_engine generator( std::random_device{}() );

    std::uniform_int_distribution<unsigned long long> uniform_dist_1(1, p - 1);
    a = uniform_dist_1(generator);

    std::uniform_int_distribution<unsigned long long> uniform_dist_2(0, p - 1);
    b = uniform_dist_2(generator);
}

template<typename Data>
HashTable<Data>::HashTable(const HashTable<Data>& hasht) {
    a = hasht.a;
    b = hasht.b;
    size = hasht.size;
    tab_size = hasht.tab_size;
}

template<typename Data>
HashTable<Data>::HashTable(HashTable<Data>&& hasht) noexcept {
    std::swap(a, hasht.a);
    std::swap(b, hasht.b);
    std::swap(size, hasht.size);
    std::swap(tab_size, hasht.tab_size);
}

template<typename Data>
const ulong HashTable<Data>::HashKey(const Data& data) const {
    ulong encoding = hash.operator()(data);
    return ((((a * encoding) + b) % p) % tab_size);
}

/* ************************************************************************** */

}