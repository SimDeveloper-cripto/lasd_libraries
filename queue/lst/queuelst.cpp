
namespace lasd {

/* ************************************************************************** */

template<typename Data>
QueueLst<Data>::QueueLst(const QueueLst<Data>& queue) : List<Data>(queue) {
    size = queue.size;
}

template<typename Data>
QueueLst<Data>::QueueLst(QueueLst<Data>&& queue) noexcept {
    std::swap(size, queue.size); 
    std::swap(head, queue.head); 
    std::swap(tail, queue.tail);  
}

template<typename Data>
QueueLst<Data>::~QueueLst() {
    for (ulong i = 0; i < size; ++i){ 
        Dequeue(); 
    } 
}

template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& queue) {
    QueueLst<Data>* tempqueue = new QueueLst<Data>(queue);
    std::swap(*tempqueue, *this); 
    delete tempqueue; 
    return *this; 
}

template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& queue) noexcept {
    std::swap(size, queue.size);
    std::swap(head, queue.head);
    std::swap(tail, queue.tail);
    return *this;
}

template<typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& queue) const noexcept { 
    if(size == queue.size) {
        for(ulong i = 0; i < size; i++) {
            if( (*this)[i] != queue[i] ) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

template<typename Data>
inline bool QueueLst<Data>::operator!=(const QueueLst<Data>& queue) const noexcept { 
    return !(*this == queue); 
}

/******************** SPECIFIC MEMBER FUNCTION ********************/
template<typename Data>
const Data& QueueLst<Data>::Head() const {
    if(size == 0) {
        throw std::length_error("Attenzione, struttura dati vuota!");
    } else {
        return List<Data>::Front();
    }
}

template<typename Data>
Data& QueueLst<Data>::Head() {
    if(size == 0) {
        throw std::length_error("Attenzione, struttura dati vuota!");
    } else {
        return List<Data>::Front(); 
    }    
}

template<typename Data>
void QueueLst<Data>::Dequeue() {
    if(size == 0) {
        throw std::length_error("Attezione, struttura dati vuota!");
    } else {
        List<Data>::RemoveFromFront();
    }
}

template<typename Data>
Data QueueLst<Data>::HeadNDequeue() {
    if(size == 0) {
        throw std::length_error("Attenzione, struttura dati vuota!");
    } else {
        Data value = List<Data>::FrontNRemove();
        return value;
    }
}

template<typename Data>
void QueueLst<Data>::Enqueue(const Data& data) { 
    List<Data>::InsertAtBack(data); 
}

template<typename Data>
void QueueLst<Data>::Enqueue(Data&& data) { 
    List<Data>::InsertAtBack(std::move(data)); 
}

template<typename Data>
void QueueLst<Data>::Clear() { 
    List<Data>::Clear(); 
}

/* ************************************************************************** */

}