#include <iostream>

namespace lasd {

/* ************************************************************************** */

template <typename Data>
Vector<Data>::Vector(const ulong dim) {
    Elements = new Data[dim] {}; 
    size = dim;
}

template <typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& linear_container) {
    size = linear_container.Size();
    Elements = new Data[size];
    for (ulong index = 0; index < size; ++index) {
        Elements[index] = linear_container[index];
    }
}

template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vector) {
    Elements = new Data[vector.size];
    std::copy(vector.Elements, vector.Elements + vector.size, Elements);
    size = vector.size;
}

template <typename Data>
Vector<Data>::Vector(Vector<Data>&& vector) noexcept {
    std::swap(Elements, vector.Elements);
    std::swap(size, vector.size);
}

template <typename Data>
Vector<Data>::~Vector() {
    delete[] Elements;
}

template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vector) noexcept {
    Vector<Data>* temp_vector = new Vector<Data>(vector);
    std::swap(*temp_vector, *this); 
    delete temp_vector; 
    return *this;
}

template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vector) noexcept {
    std::swap(Elements, vector.Elements);
    std::swap(size, vector.size);
    return *this;
}

template <typename Data>
bool Vector<Data>::operator==(const Vector& vector) const noexcept {
    if(size == vector.size) {
        for (ulong index = 0; index < size; ++index){
            if(Elements[index] != vector.Elements[index]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

template <typename Data>
bool Vector<Data>::operator!=(const Vector& vector) const noexcept {
    return !(*this == vector);
}

template <typename Data>
void Vector<Data>::Clear(){
    delete[] Elements; 
    Elements = nullptr;
    size = 0;
}

template <typename Data>
void Vector<Data>::Resize(const ulong new_size){
    if(new_size == 0){
        Clear();
    } else if (size != new_size) {
        ulong dim = (size < new_size) ? size : new_size;
        Data* tempElements = new Data[new_size] {};

        for(ulong index = 0; index < dim; ++index) {
            std::swap(Elements[index], tempElements[index]);
        }

        std::swap(Elements, tempElements); 
        size = new_size;
        delete[] tempElements;
    } 
}

template <typename Data>
Data& Vector<Data>::Front() const {
    if(size != 0){
        return Elements[0];
    } else {
        throw std::length_error("Accesso effettuato ad un Vector vuoto!");
    }
}
 
template <typename Data>
Data& Vector<Data>::Back() const {
    if(size != 0){
        return Elements[size - 1];
    } else {
        throw std::length_error("Accesso effettuato ad un Vector vuoto!");
    }
}

template <typename Data>
Data& Vector<Data>::operator[](const ulong index) const {
    if(index < size) {
        return Elements[index];
    } else {
        throw std::out_of_range("Accesso negato all'indice: " + std::to_string(index) + "; dimensione del vettore: " + std::to_string(size) + ".");
    }
}

template <typename Data>
inline void Vector<Data>::Map(MapFunctor funct, void* par) {
    MapPreOrder(funct, par);
}

template <typename Data>
inline void Vector<Data>::MapPreOrder(MapFunctor funct, void* par) {
    for(ulong index = 0; index < size; ++index) {
       funct(Elements[index], par); 
    }
}

template <typename Data>
void Vector<Data>::MapPostOrder(MapFunctor funct, void* par) {
    ulong index = size; 
    while(index > 0) {
        funct(Elements[--index], par);
    }
}

template <typename Data>
void Vector<Data>::Fold(FoldFunctor funct, const void* par, void* accum) const {
    FoldPreOrder(funct, par, accum);
}

template <typename Data>
inline void Vector<Data>::FoldPreOrder(FoldFunctor funct, const void* par, void* accum) const {
    for(ulong index = 0; index < size; ++index) {
       funct(Elements[index], par, accum); 
    }
}

template <typename Data>
inline void Vector<Data>::FoldPostOrder(FoldFunctor funct, const void* par, void* accum) const {
    ulong index = size;
    while(index > 0) {
        funct(Elements[--index], par, accum);
    }
}

/* ************************************************************************** */
// SECTION DEDICATED TO SORTING ALGORITHMS

template <typename Data>
void Vector<Data>::InsertionSort() {
    for (int j = 1; j < size; j++) {
        Data key = Elements[j];
        int i = j - 1;
        while (i >= 0 && key < Elements[i]) {
            Elements[i + 1] = Elements[i];    
            i = i - 1;
        }
        Elements[i + 1] = key;
    }
}

template <typename Data>
int Vector<Data>::FindMax(const int limit) {
    int max = 0;
    for (int i = 1; i <= limit; i++) {
        if (Elements[i] > Elements[max]) max = i;
    }
    return max;
}

template <typename Data>
void Vector<Data>::SelectionSort() {
    for (int j = size; j >= 1; j--) {
        int max = FindMax(j);

        Data temp = Elements[j];
        Elements[j] = Elements[max];
        Elements[max] = temp;
    }
}

/* ************************************************************************** */

}