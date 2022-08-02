namespace lasd {

/* ************************************************************************** */

template<typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data& data, ulong index, Vector<NodeVec*> *vector) {
    element = data;
    node_index = index;
    vec_p = vector;
}

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(const BinaryTreeVec<Data>::NodeVec& node) {
    element = node.element;
    node_index = node.index;
    vec_p = node.vec_p;
    return *this;
} 

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(BinaryTreeVec<Data>::NodeVec&& node) noexcept {
    std::swap(element, node.element);
    std::swap(node_index, node.index);
    vec_p = std::move(node.vec_p);
    return *this;
} 

template<typename Data>
Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept { 
    return element; 
}

template<typename Data>
const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept { 
    return element; 
}

template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return ( (node_index*2 + 1) <= (vec_p->Size() - 1) ); // node_index*2 + 1 --> posizione del figlio sinistro.
}

template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    return ( (node_index*2 + 2) <= (vec_p->Size() - 1) ); // node_index*2 + 2 --> posizione del figlio destro.
}

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if(!HasLeftChild())
        throw std::out_of_range("Errore: figlio sinistro non presente!");

    return *vec_p->operator[](node_index*2 + 1);
}

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if(!HasRightChild())
        throw std::out_of_range("Errore: figlio destro non presente!");

    return *vec_p->operator[](node_index*2 + 2);
}

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& lc) {
    if(lc.Size() > 0) {
        size = lc.Size(); 
        vector_tree = new Vector<NodeVec*>(size);
        for(ulong i = 0; i < size; i++){
            BinaryTreeVec<Data>::NodeVec* node = new BinaryTreeVec<Data>::NodeVec(lc[i], i, vector_tree);
            vector_tree->operator[](i) = node;
        }
    }
}

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& btvec) {
    size = btvec.size; 
    vector_tree = new Vector<NodeVec*>(size); 
    for (ulong i = 0; i < size; i++){
        vector_tree->operator[](i) = new NodeVec(btvec.vector_tree->operator[](i)->Element(), i, vector_tree);
    }
}

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& btvec) noexcept {
    vector_tree = new Vector<NodeVec*>();
    std::swap(size, btvec.size); 
    std::swap(vector_tree, btvec.vector_tree);
}

template<typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
    this->Clear();
    delete vector_tree; 
    vector_tree = nullptr;
}

template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& btvec) {
    BinaryTreeVec<Data>* temp = new BinaryTreeVec<Data>(btvec);
    std::swap(*this, *temp);
    delete temp;
    return *this;
}

template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& btvec) noexcept{
    std::swap(size, btvec.size); 
    std::swap(vector_tree, btvec.vector_tree);
    return *this;
}

template<typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& btvec) const noexcept {
    return BinaryTree<Data>::operator==(btvec);
}

template<typename Data>
bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& btvec) const noexcept {
    return !(*this = btvec);
}

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    if(size == 0)
        throw std::length_error("Errore: BinaryTreeVec vuoto!");

    return *vector_tree->operator[](0);
}

template<typename Data>
void BinaryTreeVec<Data>::Clear() {
    if(size > 0) {
        for (ulong i = 0; i < size; i++){
            delete vector_tree->operator[](i);
        }
        vector_tree->Clear();
        size = 0;
    }
}

template<typename Data>
void BinaryTreeVec<Data>::MapBreadth(MapFunctor funct, void* par) {
    for(ulong i = 0; i < size; i++) {
        funct(vector_tree->operator[](i)->Element(), par);
    }
}

template<typename Data>
void BinaryTreeVec<Data>::FoldBreadth(FoldFunctor funct, const void* par, void* accum) const {
    for(ulong i = 0; i < size; i++) {
        funct(vector_tree->operator[](i)->Element(), par, accum);
    }
}

/* ************************************************************************** */

}