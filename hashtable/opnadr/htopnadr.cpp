
namespace lasd {

/* ************************************************************************** */

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr() : HashTable<Data>() {
    vec = Vector<Data>(tab_size);
    initializeVecFlag(tab_size);
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong dim) : HashTable<Data>() {
    tab_size = dim;
    vec = Vector<Data>(tab_size);
    initializeVecFlag(tab_size);
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const LinearContainer<Data>& lc) : HashTable<Data>() {
    vec = Vector<Data>(tab_size);
    initializeVecFlag(tab_size);
    DictionaryContainer<Data>::Insert(lc);
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong dim, const LinearContainer<Data>& lc) : HashTable<Data>() {
    tab_size = dim;
    vec = Vector<Data>(tab_size);
    initializeVecFlag(tab_size);
    DictionaryContainer<Data>::Insert(lc);
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data>& hash) : HashTable<Data>(hash) {
    vec = hash.vec;
    vec_flag = hash.vec_flag;
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& hash) noexcept : HashTable<Data>(std::move(hash)) {
    std::swap(vec, hash.vec);
    std::swap(vec_flag, hash.vec_flag);
}

template<typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& hasht) {
    a = hasht.a;
    b = hasht.b;
    size = hasht.size;
    tab_size = hasht.tab_size;
    vec = hasht.vec;
    vec_flag = hasht.vec_flag;

    return *this;
}

template<typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& hasht) noexcept {
    std::swap(a, hasht.a);
    std::swap(b, hasht.b);
    std::swap(size, hasht.size);
    std::swap(tab_size, hasht.tab_size);
    std::swap(vec, hasht.vec);
    std::swap(vec_flag, hasht.vec_flag);

    return *this;
}

template <typename Data>
void helperFExists(const Data& element, const void* other_hash, void* presente) noexcept {
    if ((*(HashTableOpnAdr<Data>*) other_hash).Exists(element)) { // Membership test dell'elemento nella struttura confrontata.
        *((bool*) presente) = true;
    }
}

template<typename Data>
inline bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& hasht) const noexcept {
    if (size == hasht.size) {
        bool presente = false;
        Fold(&helperFExists<Data>, &hasht, &presente); 
        return presente;
    } else {
        return false;
    }
}

template<typename Data>
inline bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data>& hasht) const noexcept {
    return !(*this == hasht);
}

template<typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& data) {
    Expand();

    ulong i = 0;
    ulong position = HashKey(data, i);

    while(vec_flag.operator[](position) == 2 && i < tab_size) {
        if (vec.operator[](position) == data)
            return false;
        
        i++;
        position = HashKey(data, i);
    }

    if (i < tab_size) {
        if (vec_flag.operator[](position) == 0) {
            vec_flag.operator[](position) = 2;
            vec.operator[](position) = data;
            size++;
            return true;
        } else {
            ulong index = position;
            while (vec_flag.operator[](position) != 0 && i < tab_size) {
                i++;
                position = HashKey(data, i);

                if (vec_flag.operator[](position) == 2 && vec.operator[](position) == data) {
                    return false;
                }
            }
            vec_flag.operator[](index) = 2;
            vec.operator[](index) = data;
            size++;
            return true;
        }
    } else {
        return false;
    }
}

template<typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& data) {
    Expand();

    ulong i = 0;
    ulong position = HashKey(data, i);

    while(vec_flag.operator[](position) == 2 && i < tab_size) {
        if (vec.operator[](position) == data)
            return false;
        
        i++;
        position = HashKey(data, i);
    }

    if (i < tab_size) {
        if (vec_flag.operator[](position) == 0) {
            vec_flag.operator[](position) = 2;
            vec.operator[](position) = std::move(data);
            size++;
            return true;
        } else {
            ulong index = position;
            while (vec_flag.operator[](position) != 0 && i < tab_size) {
                i++;
                position = HashKey(data, i);

                if (vec_flag.operator[](position) == 2 && vec.operator[](position) == data) {
                    return false;
                }
            }
            vec_flag.operator[](index) = 2;
            vec.operator[](index) = std::move(data);
            size++;
            return true;
        }
    } else {
        return false;
    }
}

template<typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& data) {
    ulong i = 0;
    ulong index = HashKey(data, i);

    while (vec_flag.operator[](index) != 0 && i < tab_size) {
        if (vec.operator[](index) == data && vec_flag.operator[](index) == 2) {
            vec_flag.operator[](index) = 1;
            size--;
            return true;
        }
        
        i++;
        index = HashKey(data, i);
    }

    return false;
}

template<typename Data>
inline bool HashTableOpnAdr<Data>::Exists(const Data& data) const noexcept {
    ulong i = 0;
    ulong index = HashKey(data, i);
     
    // Scorrere le celle non vuote o che comunque contenevano un dato.
    while(vec_flag.operator[](index) != 0 && i < tab_size) {
        // Memebership test del dato nella tabella.
        if (vec.operator[](index) == data && vec_flag.operator[](index) == 2)
            return true;
        
        i++;
        index = HashKey(data, i);
    }
    
    return false;
}

template<typename Data>
void helperMResize(Data& data, void* other_struct) {
    (*(HashTableOpnAdr<Data>*)other_struct).Insert(data);
}

template<typename Data>
void HashTableOpnAdr<Data>::Resize(ulong dim){
    if (dim == 0) {
        Clear();
    } else {
        if (tab_size != dim) {
            dim = findCorrectTableSize(dim);
            HashTableOpnAdr<Data> newstruct = HashTableOpnAdr<Data>(dim); 
            Map(&helperMResize<Data>, &newstruct);
            std::swap(*this, newstruct);
        }
    }
}

template<typename Data>
void HashTableOpnAdr<Data>::Map(MapFunctor funct, void* other_par) {
    for(ulong i = 0; i < tab_size; ++i) {
        if (vec_flag.operator[](i) == 2) {
            funct(vec.operator[](i), other_par);
        }
    }
}

template<typename Data>
void HashTableOpnAdr<Data>::Fold(FoldFunctor funct, const void* par, void* accum) const {
    for(ulong i = 0; i < tab_size; ++i) {
        if (vec_flag.operator[](i) == 2) {
            funct(vec.operator[](i), par, accum);
        }
    }
}

template<typename Data>
void HashTableOpnAdr<Data>::Clear() {
    size = 0;  
    tab_size = 128;

    vec.Clear();
    vec.Resize(tab_size);

    vec_flag.Clear();
    vec_flag.Resize(tab_size); 
    initializeVecFlag(tab_size);
}

template<typename Data>
const ulong HashTableOpnAdr<Data>::HashKey(const Data& data, const ulong index) const {
    return (HashKey(data) + (c * index)) % tab_size;
}

template<typename Data>
void HashTableOpnAdr<Data>::initializeVecFlag(const ulong dim) {
    vec_flag = Vector<ushort>(dim);
    for (ulong i = 0; i < dim; ++i) {
        vec_flag.operator[](i) = 0;
    }
}

template<typename Data>
void HashTableOpnAdr<Data>::Expand() {
    if (size >= (tab_size / 2)) {
        Resize(tab_size * 2); 
    }
}

template<typename Data>
const ulong HashTableOpnAdr<Data>::findCorrectTableSize(ulong number) const {
    // Potenza di 2 >= all'input.
    ulong result = log2(number);
    int exponent = static_cast<int>(ceil(result));
    return pow(2, exponent);
}

/* ************************************************************************** */

}