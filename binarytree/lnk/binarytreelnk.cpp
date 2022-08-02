
namespace lasd {

/* ************************************************************************** */

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& data) {
   element = data; 
   leftchild = nullptr;
   rightchild = nullptr;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& node) {
   element = node.element; 
   leftchild = node.leftchild;
   rightchild = node.rightchild;
   return *this;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& node) noexcept {
   std::swap(element, node.element); 
   std::swap(leftchild, node.leftchild);
   std::swap(rightchild, node.rightchild);
   return *this;
}

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
    delete leftchild;
    delete rightchild;
    leftchild = rightchild = nullptr;
}

template<typename Data>
inline Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept { 
    return element; 
}

template<typename Data>
inline const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept { 
    return element; 
}

template<typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept { 
    return (leftchild != nullptr); 
}

template<typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept { 
    return (rightchild != nullptr); 
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::NodeLnk::LeftChild() const {
    if(leftchild == nullptr)
        throw std::out_of_range("lefchild == nullptr");

    return *leftchild;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::NodeLnk::RightChild() const {
    if(rightchild == nullptr)
        throw std::out_of_range("rightchild == nullptr");

    return *rightchild;
}

template<typename Data>
void BinaryTreeLnk<Data>::versaLinearContainerInBinaryTree(int start_index, BinaryTreeLnk<Data>::NodeLnk* node, const LinearContainer<Data>& lc) {
    if( ((start_index*2) + 1) <= (lc.Size() - 1) ){
        node->leftchild = new BinaryTreeLnk<Data>::NodeLnk( lc[(start_index*2) + 1] );
        versaLinearContainerInBinaryTree(start_index*2 + 1, node->leftchild, lc);
    }

    if( ((start_index*2) + 2) <= (lc.Size() - 1) ) {
        node->rightchild = new BinaryTreeLnk<Data>::NodeLnk( lc[(start_index*2) + 2] );
        versaLinearContainerInBinaryTree(start_index*2 + 2, node->rightchild, lc);
    }
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::copiaAlbero(NodeLnk* da_copiare){
    BinaryTreeLnk<Data>::NodeLnk* node = nullptr;

    if(da_copiare != nullptr) {
        node = new BinaryTreeLnk<Data>::NodeLnk(da_copiare->element);

        if(da_copiare->HasLeftChild()) {
            node->leftchild = copiaAlbero(&(da_copiare->LeftChild())); // inserimento nell'albero del sinistro.
        }

        if(da_copiare->HasRightChild()) {
            node->rightchild = copiaAlbero(&(da_copiare->RightChild())); // inserimento nell'albero del destro.
        }
    }

    return node;
}

template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& lc) {
    if( !lc.Empty() ) {   
        size = lc.Size(); 
        root = new BinaryTreeLnk<Data>::NodeLnk(lc[0]);
        versaLinearContainerInBinaryTree(0, root, lc);    
    } else {
        size = 0; 
        root = nullptr;    
    }
}

template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& btlnk) {
    size = btlnk.size;

    if(size > 0)
        root = copiaAlbero( &btlnk.Root() );
}

template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& btlnk) noexcept {
    std::swap(root, btlnk.root); 
    std::swap(size, btlnk.size);
}

template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() { 
    delete root;
}

template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& bt) {
    BinaryTreeLnk<Data>* temp = new BinaryTreeLnk<Data>(bt); 
    std::swap(*this, *temp);
    delete temp;
    return *this;
}

template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& bt) noexcept {
    std::swap(root, bt.root);
    std::swap(size, bt.size); 
    return *this;
}

template<typename Data>
inline bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& bt) const noexcept {
    return BinaryTree<Data>::operator==(bt);
}

template<typename Data>
inline bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& bt) const noexcept {
    return !(*this == bt);
}

template<typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
    if(root == nullptr)
        throw std::length_error("Errore: l'albero è vuoto!");

    return *root;
}

template<typename Data>
void BinaryTreeLnk<Data>::Clear(){
    size = 0;
    delete root;
    root = nullptr;
}

/* ************************************************************************** */

}