
namespace lasd {

/* ************************************************************************** */

template<typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& lc) {
    testa = 0;
    size = lc.Size() + 1;
    Elements = new Data[size];

    for(ulong index = 0; index < lc.Size(); index++) {
        Elements[index] = lc[index];
    }

    coda = lc.Size();
    Expand();
}

template<typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& queue) noexcept : Vector<Data>(std::move(queue)) {
    std::swap(testa, queue.testa);
    std::swap(coda, queue.coda);
}

template<typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& queue) {
    Vector<Data>::operator=(queue);
    testa = queue.testa; 
    coda = queue.coda;
    return *this;
}

template<typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& queue) noexcept {
    Vector<Data>::operator=(std::move(queue));
    std::swap(testa, queue.testa);
    std::swap(coda, queue.coda);
    return *this;
}

template<typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& queue) const noexcept {
    if(this->Size() == queue.Size()) {
        ulong i = this->testa;
        ulong j = queue.testa;

        while( i != this->coda ) {
            if( Elements[i] != queue.Elements[j] ) {
                return false;
            }
            i = (i + 1) % size;
            j = (j + 1) % queue.size;
        }

        return true;
    } else {
        return false;
    }
}

template<typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data>& queue) const noexcept { 
    return !(*this == queue); 
}

template<typename Data>
const Data& QueueVec<Data>::Head() const {
    if(testa == coda) {
        throw std::length_error("Attenzione, coda vuota!");
    } else {
        return Elements[testa];
    }
}

template<typename Data>
Data& QueueVec<Data>::Head() {
    if(testa == coda) {
        throw std::length_error("Attenzione, coda vuota!");
    } else {
        return Elements[testa];
    }
}

template<typename Data>
void QueueVec<Data>::Dequeue() {
    if(testa == coda){
        throw std::length_error("Attenzione, coda vuota!");
    } else {
        testa = (testa + 1) % size;
        Reduce();
    }
}

template<typename Data>
Data QueueVec<Data>::HeadNDequeue() {
    if(testa == coda){
        throw std::length_error("Attenzione, coda vuota!");
    } else {
        Data value = Elements[testa];
        testa = (testa + 1) % size;
        Reduce();
        return value;
    }
}

template<typename Data>
void QueueVec<Data>::Enqueue(const Data& data) {
    Expand();
    Elements[coda] = data; 
    coda = (coda + 1) % size;
}

template<typename Data>
void QueueVec<Data>::Enqueue(Data&& data) {
    Expand();
    Elements[coda] = std::move(data); 
    coda = (coda + 1) % size;
}

template<typename Data>
inline bool QueueVec<Data>::Empty() const noexcept { 
    return (testa == coda); 
}

template<typename Data>
inline ulong QueueVec<Data>::Size() const noexcept { 
    if(testa > coda) {
        return ((size - testa) + coda);
    } else {
        return (coda - testa);
    }
}

template<typename Data>
void QueueVec<Data>::Clear() {
    testa = 0; 
    coda = 0;
    Vector<Data>::Resize(1);
}

template<typename Data>
void QueueVec<Data>::Expand() {
    if(Size() == (size - 1)){
        SwapVectors((this->size) * 2);
    }
}

template<typename Data>
void QueueVec<Data>::Reduce() {
    if(Size() == (size / 4)){
        SwapVectors((this->size) / 2);
    }
}

template<typename Data>
void QueueVec<Data>::SwapVectors(ulong dim) {
    Data* tmp = new Data[dim] {};
    ulong i = testa; 
    ulong j = 0;
    while(i != coda) {
        std::swap(Elements[i], tmp[j]);
        i = (i + 1) % size;
        j++;
    }

    std::swap(Elements, tmp);
    size = dim;
    testa = 0; 
    coda = j;
    delete[] tmp;
}

/* ************************************************************************** */

}