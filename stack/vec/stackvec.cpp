
namespace lasd {

/* ************************************************************************** */

template<typename Data>
StackVec<Data>::StackVec(StackVec&& stack) noexcept : Vector<Data>(std::move(stack)){ 
    std::swap(index, stack.index); 
}

template<typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& stack) {
    Vector<Data>::operator=(stack);
    index = stack.index;
    return *this;
}

template<typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& stack) noexcept {
    Vector<Data>::operator=(std::move(stack));
    std::swap(index, stack.index);
    return *this;
}

template<typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& stack) const noexcept {
    if(index == stack.index) {
        for(ulong i = 0; i < index; ++i){
            if(Elements[i] != stack.Elements[i]) {
                return false;
            }
        }
        return true;
        
    } else {
        return false;
    }
}

template<typename Data>
inline bool StackVec<Data>::operator!=(const StackVec<Data>& stack) const noexcept { return !(*this == stack); }

template<typename Data>
const Data& StackVec<Data>::Top() const {
    if(size == 0 || index == 0) {
        throw std::length_error("Errore: accesso ad uno stack vuoto!");
    } else {
        const Data& value = Elements[index - 1]; // Testa dello stack all'indice (index - 1).
        return value;
    }
}

template<typename Data>
Data& StackVec<Data>::Top() {
    if(size == 0 || index == 0) {
        throw std::length_error("Errore: accesso ad uno stack vuoto!");
    } else {
        return Elements[index - 1];
    }
}

template<typename Data>
void StackVec<Data>::Pop() {
    if(Empty()) {
        throw std::length_error("Errore: Pop di uno stack vuoto!");
    } else {
        --index; 
        Reduce();
    }
}

template<typename Data>
Data StackVec<Data>::TopNPop(){
    if(size == 0 || index == 0){
        throw std::length_error("Errore: TopNPop di uno stack vuoto!");
    } else {
        Data value = Elements[index - 1]; // Salviamo il dato della head prima del Pop per poterlo ritornare.
        index--;
        Reduce(); 
        return value;
    }
}

template<typename Data>
void StackVec<Data>::Push(const Data& data) {
    Expand(); 
    index++;
    Elements[index - 1] = data;
}

template<typename Data>
void StackVec<Data>::Push(Data&& data) {
    Expand(); 
    index++; 
    Elements[index - 1] = std::move(data);
}

template<typename Data>
inline bool StackVec<Data>::Empty() const noexcept { 
    return (index == 0); 
}

template<typename Data>
inline ulong StackVec<Data>::Size() const noexcept { 
    return index; 
}

template<typename Data>
void StackVec<Data>::Clear() {
    Vector<Data>::Clear();
    Vector<Data>::Resize(1);
    index = 0;
}

template<typename Data>
void StackVec<Data>::Expand() {
    if(index == size){
        Vector<Data>::Resize(size * 2);
    }
}

template<typename Data>
void StackVec<Data>::Reduce() {
    if(index == (size / 4)){
        Vector<Data>::Resize(size / 2);
    }
}

/* ************************************************************************** */

}