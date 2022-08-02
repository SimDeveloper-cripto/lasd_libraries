
namespace lasd {

/* ************************************************************************** */

// A hash table of a given size
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong dim) : HashTable<Data>() {
    tab_size = dim;
    vec = Vector<BST<Data>>(tab_size);
}

// A hash table obtained from a LinearContainer
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const LinearContainer<Data>& lc) : HashTable<Data>() {
    vec = Vector<BST<Data>>(tab_size);
    DictionaryContainer<Data>::Insert(lc);
}

// A hash table of a given size obtained from a LinearContainer
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong dim, const LinearContainer<Data>& lc) : HashTable<Data>() {
    tab_size = dim;
    vec = Vector<BST<Data>>(tab_size);
    DictionaryContainer<Data>::Insert(lc);
}

// COPY CONSTRUCTOR
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr& hash) : HashTable<Data>(hash) {    
    vec = hash.vec;
}

// MOVE CONSTRUCTOR
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr&& hash) noexcept : HashTable<Data>(std::move(hash)) {
    std::swap(vec, hash.vec);
}

// COPY ASSIGNMENT
template<typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& hasht) {
    a = hasht.a;
    b = hasht.b;
    size = hasht.size;
    tab_size = hasht.tab_size;
    vec = hasht.vec;
    
    return *this;
}

// MOVE ASSIGNMENT
template<typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& hasht) noexcept {
    std::swap(a, hasht.a);
    std::swap(b, hasht.b);
    std::swap(size, hasht.size);
    std::swap(tab_size, hasht.tab_size);
    std::swap(vec, hasht.vec);
    
    return *this;
}

template <typename Data>
void helperFoldExists(const Data& element, const void* other_hash, void* presente) noexcept {
    if ((*(HashTableClsAdr<Data>*) other_hash).Exists(element)) { // Membership test dell'elemento nella struttura confrontata.
        *((bool*) presente) = true;
    }
}

template<typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& hasht) const noexcept {
    if (size == hasht.size) {
        bool presente = false;
        Fold(&helperFoldExists<Data>, &hasht, &presente); 
        return presente;
    } else {
        return false;
    }
}

template<typename Data>
inline bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data>& hasht) const noexcept {
    return !(*this == hasht);
}

template<typename Data>
void helperMapResize(Data& data, void* other_struct) {
    (*(HashTableClsAdr<Data>*)other_struct).Insert(data);
}

template<typename Data>
void HashTableClsAdr<Data>::Resize(ulong dim){
    if (tab_size != dim) {
        HashTableClsAdr<Data> newstruct = HashTableClsAdr<Data>(dim); 
        Map(&helperMapResize<Data>, &newstruct);

        a = newstruct.a;
        b = newstruct.b;
        size = newstruct.size;
        tab_size = newstruct.tab_size;
        std::swap(vec, newstruct.vec);
    }
}

template<typename Data>
bool HashTableClsAdr<Data>::Insert(const Data& data) {
    if (((vec)[HashKey(data)]).Insert(data)) {
        size++; 
        return true;
    }
    return false;
}

template<typename Data>
bool HashTableClsAdr<Data>::Insert(Data&& data) {
    if (((vec)[HashKey(data)]).Insert(std::move(data))) {
        size++; 
        return true;
    }
    return false;
}

template<typename Data>
bool HashTableClsAdr<Data>::Remove(const Data& data) {
    if (((vec)[HashKey(data)]).Remove(data)) {
        size--; 
        return true;
    }
    return false;
}

template<typename Data>
bool HashTableClsAdr<Data>::Exists(const Data& data) const noexcept {
    return ((vec)[HashKey(data)]).Exists(data);
}

template<typename Data>
void HashTableClsAdr<Data>::Map(MapFunctor funct, void* other_par) {
    for(ulong i = 0; i < tab_size; ++i) {
        vec[i].Map(funct, other_par);
    }
}

template<typename Data>
void HashTableClsAdr<Data>::Fold(FoldFunctor funct, const void* par, void* accum) const {
    for(ulong i = 0; i < tab_size; ++i) {
        vec[i].Fold(funct, par, accum);
    }
}

template<typename Data>
void HashTableClsAdr<Data>::Clear() {
    size = 0;  
    tab_size = 128;
    vec.Clear();
    vec.Resize(tab_size);
}

/* ************************************************************************** */

}