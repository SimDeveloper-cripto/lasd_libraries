
namespace lasd {

template<typename Data>
StackLst<Data>::StackLst(const LinearContainer<Data>& lc) : List<Data>(lc) {}

template<typename Data>
StackLst<Data>::StackLst(const StackLst<Data>& stack) : List<Data>(stack) {
    size = stack.size;
}

template<typename Data>
StackLst<Data>::StackLst(StackLst<Data>&& stack) noexcept {
    std::swap(size, stack.size); 
    std::swap(head, stack.head);
}

template<typename Data>
StackLst<Data>::~StackLst() {
    for (ulong index = 0; index < size; ++index) {
        Pop();
    }
}

template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stack) {
    StackLst<Data>* tempstack = new StackLst<Data>(stack); 
    std::swap(*tempstack, *this); 
    delete tempstack;
    return *this;
}

template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stack) noexcept {
    std::swap(size, stack.size);
    std::swap(head, stack.head);
    return *this;
}

template<typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& stack) const noexcept {
    if(size == stack.size) {
        for(ulong i = 0; i < size; i++) {
            if( (*this)[i] != stack[i] ) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

template<typename Data>
inline bool StackLst<Data>::operator!=(const StackLst<Data>& stack) const noexcept { 
    return !(*this == stack); 
}

template<typename Data>
const Data& StackLst<Data>::Top() const {
    if(size == 0) {
        throw std::length_error("Attezione, struttura dati vuota!");
    } else {
        return List<Data>::Front();   
    }
}

template<typename Data>
Data& StackLst<Data>::Top() {
    if(size == 0) {
        throw std::length_error("Attezione, struttura dati vuota!");
    } else {
        return List<Data>::Front();
    }
}

template<typename Data>
void StackLst<Data>::Pop() {
    if(size == 0) {
        throw std::length_error("Attezione, struttura dati vuota!");
    } else {
        List<Data>::RemoveFromFront();
    }
}

template<typename Data>
Data StackLst<Data>::TopNPop() {
    if(size == 0) {
        throw std::length_error("Attezione, struttura dati vuota!");
    } else {
        Data value = List<Data>::FrontNRemove();
        return value;
    }
}

template<typename Data>
void StackLst<Data>::Push(const Data& data) { 
    List<Data>::InsertAtFront(data); 
}

template<typename Data>
void StackLst<Data>::Push(Data&& data) {
    List<Data>::InsertAtFront(std::move(data)); 
}

template<typename Data>
void StackLst<Data>::Clear() { 
    List<Data>::Clear(); 
}

}