#include <iostream>

namespace lasd {

/* ************************************************************************** */

template <typename Data>
inline bool LinearContainer<Data>::operator==(const LinearContainer<Data>& linear_container) const noexcept {
    if (size == linear_container.size){
        for(ulong index = 0; index < size; ++index){
            if(operator[](index) != linear_container[index]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

template <typename Data>
inline bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& lc) const noexcept {
    return !(*this == lc);
}

template <typename Data>
inline Data& LinearContainer<Data>::Front() const {
    if(size != 0){
        return operator[](0);
    } else {
        throw std::length_error("Accesso effettuato ad un LinearContainer vuoto!");
    }
}

template <typename Data>
inline Data& LinearContainer<Data>::Back() const {
    if(size != 0){
        return operator[](size - 1);
    } else {
        throw std::length_error("Accesso effettuato ad un LinearContainer vuoto!");
    }
}

/* ************************************************************************** */

template<typename Data>
void DictionaryContainer<Data>::Insert(const LinearContainer<Data>& lc) {
    for (ulong i = 0; i < lc.Size(); ++i){
        Insert( lc[i] );
    }
}

template<typename Data>
void DictionaryContainer<Data>::Insert(LinearContainer<Data>&& lc) {
    for (ulong i = 0; i < lc.Size(); ++i){
        Insert( std::move(lc[i]) );
    }
}

template<typename Data>
void DictionaryContainer<Data>::Remove(const LinearContainer<Data>& lc) {
    for (ulong i = 0; i < lc.Size(); ++i){
        Remove( lc[i] );
    }
}

/* ************************************************************************** */

template <typename Data>
void CheckFoldExists(const Data& dat, const void* value, void* exists) noexcept {
    if(dat == *((Data*) value)) {
        *((bool*) exists) = true;
    }
}

template <typename Data>
inline bool FoldableContainer<Data>::Exists(const Data& data) const noexcept {
    bool exists = false;
    // std::cout << "Exists() --> parametro ricevuto: " << data << std::endl;
    Fold(&CheckFoldExists<Data>, &data, &exists); 
    return exists;
}

/* ************************************************************************** */

template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFunctor functor, void* other_par) {
    MapPreOrder(functor, other_par);
}


template <typename Data>
inline void PreOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
    FoldPreOrder(fun, par, acc);
}

template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFunctor functor, void* other_par) {
    MapPostOrder(functor, other_par);
}

template <typename Data>
inline void PostOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
    FoldPostOrder(fun, par, acc);
}

/**********************************************************************************************************/

template<typename Data>
inline void InOrderMappableContainer<Data>::Map(MapFunctor functor, void* other_par) {
    MapInOrder(functor, other_par);
}

template <typename Data>
inline void InOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
    FoldInOrder(fun, par, acc);
}

template <typename Data>
inline void BreadthMappableContainer<Data>::Map(MapFunctor fun, void* other_par) {
    MapBreadth(fun, other_par);
}

template <typename Data>
inline void BreadthFoldableContainer<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
    FoldBreadth(fun, par, acc);
}

/* ************************************************************************** */

}