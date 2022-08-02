
namespace lasd {

/* ************************************************************************** */

template<typename Data>
BST<Data>::BST(const LinearContainer<Data>& lc) {
    for (ulong i = 0; i < lc.Size(); i++){
        Insert( lc[i] );
    }
}

template<typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& bst) {
    BinaryTreeLnk<Data>::operator=( bst ); 
    return *this;
}

template<typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept {
    BinaryTreeLnk<Data>::operator=( std::move(bst) ); 
    return *this;
}

template<typename Data>
inline bool BST<Data>::operator==(const BST<Data>& bst) const noexcept {
    if(size == bst.size) {
        BTInOrderIterator<Data> iter_1(*this);
        BTInOrderIterator<Data> iter_2(bst);

        for(; !iter_1.Terminated(); ++iter_1, ++iter_2) {
            if( *iter_1 != *iter_2 ) {
                return false;
            }
        }

        return true;
    } else {
        return false;
    }
}

template<typename Data>
inline bool BST<Data>::operator!=(const BST<Data>& bst) const noexcept {
    return !(*this == bst);
}

template<typename Data>
const Data& BST<Data>::Min() const {
    if (root == nullptr) {
        throw std::length_error("Errore: BST vuoto!");
    } else {
        return FindPointerToMin(root)->Element();
    }
}

template<typename Data>
Data BST<Data>::MinNRemove() {
    if (root == nullptr) {
        throw std::length_error("Errore: BST vuoto!");
    } else {
        return DataNDelete(DetachMin(root));
    }
}

template<typename Data>
void BST<Data>::RemoveMin() {
    if (root == nullptr) {
        throw std::length_error("Errore: BST vuoto!");
    } else {
        delete Detach(FindPointerToMin(root));
    }
}

template<typename Data>
const Data& BST<Data>::Max() const {
    if (root == nullptr) {
        throw std::length_error("Errore: BST vuoto!");
    } else {
        return FindPointerToMax(root)->Element();
    }
}

template<typename Data>
Data BST<Data>::MaxNRemove() {
    if (root == nullptr) {
        throw std::length_error("Errore: BST vuoto!");
    } else {
        return DataNDelete(DetachMax(root));
    }
}

template<typename Data>
void BST<Data>::RemoveMax() {
    if (root == nullptr) {
        throw std::length_error("Errore: BST vuoto!");
    } else {
        delete Detach(FindPointerToMax(root));
    }
}

template<typename Data>
const Data& BST<Data>::Predecessor(const Data& data) const {
    if (root == nullptr) {
        throw std::length_error("Errore: BST vuoto!");
    } else {
        NodeLnk* const* to_return = FindPointerToPredecessor(root, data); 
        if (to_return == nullptr) {
            throw std::length_error("Errore: predecessore non trovato!");
        } else {
            return (*to_return)->Element();
        }
    }
}

template<typename Data>
Data BST<Data>::PredecessorNRemove(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("Errore: BST vuoto!");
    } else {
        NodeLnk** to_return = FindPointerToPredecessor(root, data);

        if (to_return == nullptr)
            throw std::length_error("Errore: predecessore non trovato!");
        

        return DataNDelete(Detach(*to_return));
    }
}

template<typename Data>
void BST<Data>::RemovePredecessor(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("Errore: BST vuoto!");
    } else {
        NodeLnk** to_return = FindPointerToPredecessor(root, data);
        
        if (to_return == nullptr)
            throw std::length_error("Errore: predecessore non esistente.");
        
        NodeLnk*& detach = *to_return;
        NodeLnk* destroy = Detach(detach);
        delete destroy;
    }
}

template<typename Data>
const Data& BST<Data>::Successor(const Data& data) const {
    if (root == nullptr) {
        throw std::length_error("Errore: BST vuoto!");
    } else {
        NodeLnk* const* to_return = FindPointerToSuccessor(root, data); 
        if (to_return == nullptr) {
            throw std::length_error("Errore: successore non trovato!");
        } else {
            return (*to_return)->Element();
        }
    }
}
  
template<typename Data>
Data BST<Data>::SuccessorNRemove(const Data& data) {
    if (root == nullptr) {
        throw std::length_error("Errore: BST vuoto!");
    } else {
        NodeLnk** to_return = FindPointerToSuccessor(root, data);

        if (to_return == nullptr)
            throw std::length_error("Errore: successore non trovato!");


        return DataNDelete(Detach(*to_return));
    }
}

template<typename Data>
void BST<Data>::RemoveSuccessor(const Data& data){
    if (root == nullptr) {
        throw std::length_error("Errore: BST vuoto!");
    } else {
        NodeLnk** to_return = FindPointerToSuccessor(root, data);
        
        if (to_return == nullptr)
            throw std::length_error("Errore: successore non esiste.");
        
        NodeLnk*& detach = *to_return;
        NodeLnk* destroy = Detach(detach);
        delete destroy;
    }
}

template<typename Data>
bool BST<Data>::Insert(const Data& data) {
    NodeLnk* newnode = new NodeLnk(data);
    NodeLnk* parent = nullptr;
    NodeLnk* current = root;

    if (root == nullptr) {
        root = newnode;
        size = 1;
        return true;
    } else {
        while(current != nullptr) {
            parent = current;
            if (newnode->element > current->element){
                current = current->rightchild;
            } else if (newnode->element < current->element) {
                current = current->leftchild;
            } else { 
                delete newnode;
                return false;
            }
        }

        if (newnode->element < parent->element) {
            parent->leftchild = newnode;
            size++;
            return true;
        } else {
            parent->rightchild = newnode;
            size++;
            return true;
        }
    }
}

template<typename Data>
bool BST<Data>::Insert(Data&& data){
    NodeLnk* newnode = new NodeLnk(std::move(data));
    NodeLnk* parent = nullptr;
    NodeLnk* current = root;

    if (root == nullptr) {
        root = newnode;
        size = 1;
        return true;
    } else {
        while(current != nullptr) {
            parent = current;
            if (newnode->element > current->element) {
                current = current->rightchild;
            } else if (newnode->element < current->element) {
                current = current->leftchild;
            } else {
                delete newnode;
                return false;
            }
        }

        if (newnode->element < parent->element) {
            parent->leftchild = newnode;
            size++;
            return true;
        } else {
            parent->rightchild = newnode;
            size++;
            return true;
        }
    }
}

template<typename Data>
bool BST<Data>::Remove(const Data& data) {
    if (root != nullptr) {
        NodeLnk* node = Detach(FindPointerTo(root, data));
        if (node != nullptr) {
            delete node;
            return true;
        }
    }
    return false;
}

template<typename Data>
bool BST<Data>::Exists(const Data& data) const noexcept {
    if (root != nullptr) {
        NodeLnk* temp = root;
            
        while(temp != nullptr) {
            if (temp->element > data) {
                if (temp->HasLeftChild()) {
                    temp = temp->leftchild;
                } else {
                    return false;
                }
            } else if (temp->element < data) {
                if (temp->HasRightChild()) {
                    temp = temp->rightchild;
                } else {
                    return false;
                }
            } else {
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}

template<typename Data>
Data BST<Data>::DataNDelete(NodeLnk* node) {
    Data elem = node->element;
    delete node;
    return elem;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& node) noexcept {
    if (node != nullptr) {
        if (node->leftchild == nullptr) {
            return Skip2Right(node);
        } else if (node->rightchild == nullptr) {
            return Skip2Left(node);
        } else {
            NodeLnk* detach = DetachMax(node->leftchild);
            std::swap(node->element, detach->element);
            return detach;
        }
    }

    return nullptr;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& node) noexcept {
    return Skip2Right( FindPointerToMin(node) );
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& node) noexcept {
    return Skip2Left( FindPointerToMax(node) );
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(NodeLnk*& node) noexcept {
    NodeLnk* sinistro = nullptr;

    if(node != nullptr){
        std::swap(sinistro, node->leftchild);
        std::swap(sinistro, node);
        size--;
    }
    return sinistro;    
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(NodeLnk*& node) noexcept {
    NodeLnk* destro = nullptr;

    if(node != nullptr){
        std::swap(destro, node->rightchild);
        std::swap(destro, node);
        size--;
    }
    return destro;    
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& node) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(NodeLnk* const& node) const noexcept {
    NodeLnk* const* point = &node;
    NodeLnk* curr = node;

    if (curr != nullptr) {
        while (curr->leftchild != nullptr) {
            point = &curr->leftchild;
            curr = curr->leftchild;
        }
    }
    return *point;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& node) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(NodeLnk* const& node) const noexcept {
    NodeLnk* const* point = &node;
    NodeLnk* curr = node;

    if(curr != nullptr) {
        while (curr->rightchild != nullptr) {
            point = &curr->rightchild;
            curr = curr->rightchild;
        }
    }
    return *point;
}

template <typename Data>
inline typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& node, const Data& elem) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerTo(node, elem));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& node, const Data& elem) const noexcept {
    NodeLnk* const* point = &node;
    NodeLnk* curr = node;

    while (curr != nullptr) {
        if (curr->element < elem) {
            point = &curr->rightchild;
            curr = curr->rightchild;
        } else if (curr->element > elem) {
            point = &curr->leftchild;
            curr = curr->leftchild;
        } else {
            break;
        }
    }
    return *point;
}

template <typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(NodeLnk*& node, const Data& elem) noexcept {
    return const_cast<NodeLnk**>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(node, elem));
}

template <typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToPredecessor(NodeLnk* const& node , const Data& elem) const noexcept {
    NodeLnk* const* point = &node;
    NodeLnk* const* ptr = nullptr;

    while (true) {
        NodeLnk& current = **point;
        if(current.element < elem) {
            ptr = point;
            if(current.rightchild == nullptr) {
                return ptr;
            } else {
                point = &current.rightchild;
            }
        } else {
            if (current.leftchild == nullptr) {
                return ptr;
            } else {
                if (current.element > elem){
                    point = &current.leftchild;
                } else {
                    return &FindPointerToMax(current.leftchild);
                }
            }
        }
    }
}


template<typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(NodeLnk*& node, const Data& data) noexcept {
    return const_cast<NodeLnk**>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(node, data));
}

template<typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToSuccessor(NodeLnk* const& node, const Data& data) const noexcept {
    NodeLnk* const* point = &node;
    NodeLnk* const* ptr = nullptr;

    while(true) {
        NodeLnk& current = **point;
        if(current.element > data) {
            ptr = point;
            if(current.leftchild == nullptr){
                return ptr;
            } else {
                point = &current.leftchild;
            }
        } else {
            if(current.rightchild == nullptr) {
                return ptr;
            } else {
                if(current.element < data) {
                    point = &current.rightchild;
                } else {
                    return &FindPointerToMin(current.rightchild);
                }
            }
        }
    }
}

/* ************************************************************************** */

}