
namespace lasd {
    
/* ************************************************************************** */

template <typename Data>
List<Data>::Node::Node(Data&& data) noexcept {
    std::swap(element, data);
}

template <typename Data>
List<Data>::Node::Node(Node&& node) noexcept {
    std::swap(element, node.element); 
    std::swap(next, node.next);
}

template <typename Data>
List<Data>::Node::~Node(){
    delete next;
}

template <typename Data>
bool List<Data>::Node::operator==(const Node& node) const noexcept {
    return (element == node.element) \
        && ((next == nullptr && node.next == nullptr) || (next != nullptr && node.next != nullptr) && (*next == *node.next));
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node& node) const noexcept { return !(*this = node); }

template <typename Data>
List<Data>::List(const LinearContainer<Data>& linear_container) {
    for (ulong index = 0; index < linear_container.Size(); ++index) {
        InsertAtBack(linear_container[index]);
    }
}

template<typename Data>
List<Data>::List(const List<Data>& other_list) {
    Node* temp_node = other_list.head;
    while(temp_node != nullptr) {
        InsertAtBack(temp_node->element);
        temp_node = temp_node->next; 
    }
}

template<typename Data>
List<Data>::List(List<Data>&& lista) noexcept {
    std::swap(tail, lista.tail);
    std::swap(head, lista.head);
    std::swap(this->size, lista.size);
}

template<typename Data>
List<Data>::~List() { 
    for (ulong i = 0; i < this->size; ++i) { 
        RemoveFromFront(); 
    }
}

template<typename Data>
List<Data>& List<Data>::operator=(const List<Data>& lista) {
    List<Data>* templist = new List<Data>(lista);
    std::swap(*templist, *this); 
    delete templist;
    return *this;
}

template<typename Data>
List<Data>& List<Data>::operator=(List<Data>&& lista) noexcept {
    std::swap(tail, lista.tail);
    std::swap(head, lista.head);
    std::swap(this->size, lista.size);

    return *this;
}

template<typename Data>
bool List<Data>::operator==(const List<Data>& lista) const noexcept {
    if(this->size == lista.size) {
        Node* temporary1 = head;
        Node* temporary2 = lista.head;

        while(temporary1 != nullptr) {
            if(temporary1->element != temporary2->element) {
                return false;
            }
            temporary1 = temporary1->next;
            temporary2 = temporary2->next;
        }

        return true;
    } else {
        return false;
    }
}

template<typename Data>
bool List<Data>::operator!=(const List<Data>& lista) const noexcept { 
    return !(*this == lista); 
}

template<typename Data>
void List<Data>::InsertAtFront(const Data& data) {
    if (head == nullptr) {
        head = new Node(data);
        head->next = nullptr;
        tail = head;
        this->size = 1;
    } else {
        Node* newnode = new Node(data); 
        newnode->next = head; 
        head = newnode;
        this->size++;
    }
}

template<typename Data> 
void List<Data>::InsertAtFront(Data&& data) {
    if (head == nullptr) {
        head = new Node;
        head->element = std::move(data);
        head->next = nullptr;
        tail = head;
        this->size = 1;
    } else {
        Node* newnode = new Node; 
        newnode->element = std::move(data);
        newnode->next = head; 
        head = newnode;
        this->size++;
    }
}

template<typename Data>
void List<Data>::RemoveFromFront() {
    if (this->size == 0) { throw std::length_error("Attenzione: la lista è vuota!"); }

    Node* temporary_node = head; 
    head = head->next; 
    temporary_node->next = nullptr;
    delete temporary_node;
    this->size--;
}

template<typename Data>
Data List<Data>::FrontNRemove() {
    if(this->size == 0) { throw std::length_error("Attenzione: la lista è vuota!"); }
    
    Node* temp = head;
    Data to_return = temp->element;
    head = head->next;
    temp->next = nullptr;
    delete temp; 
    this->size--;

    return to_return; 
}

template<typename Data>
void List<Data>::InsertAtBack(const Data& data) noexcept {
    if(head == nullptr) {
        head = new Node(data);
        head->next = nullptr;
        tail = head;
        this->size = 1;
    } else {
        Node* temp = new Node(data);
        tail->next = temp; 
        tail = temp;
        this->size++;
    }
}

template<typename Data>
void List<Data>::InsertAtBack(Data&& data) {
    if(head == nullptr) {
        head = new Node;
        head->element = std::move(data);
        head->next = nullptr;
        tail = head;
        this->size = 1;
    } else {
        Node* temp = new Node;
        temp->element = std::move(data);
        temp->next = nullptr;
        tail->next = temp; 
        tail = temp;
        this->size++;
    }
}

template<typename Data>
void List<Data>::Clear() {
    while(head != nullptr) {
        RemoveFromFront();
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<typename Data>
Data& List<Data>::Front() const {
    if(this->size == 0)
        throw std::length_error("Attenzione: la lista è vuota!");

    return head->element;
}

template<typename Data>
Data& List<Data>::Back() const {
    if(this->size == 0)
        throw std::length_error("Attenzione: la lista è vuota!");

    return tail->element;
}

template<typename Data>
Data& List<Data>::operator[](ulong indice) const {
    if( indice > this->size )
        throw std::out_of_range("Attenzione: accesso non consentito all'indice: " + indice);
    
    Node* temporarynode = head; 
        
    for (ulong i = 0; i < indice; ++i){
        temporarynode = temporarynode->next;
    }

    return temporarynode->element;
}

// MAP
template <typename Data>
inline void List<Data>::Map(MapFunctor funct, void* par) {
    MapPreOrder(funct, par);
}

template <typename Data>
inline void List<Data>::MapPreOrder(MapFunctor funct, void* par) {
    MapPreOrder(funct, par, head);
}

template <typename Data>
inline void List<Data>::MapPostOrder(MapFunctor funct, void* par) {
    MapPostOrder(funct, par, head);
}

// FOLD
template <typename Data>
inline void List<Data>::Fold(FoldFunctor funct, const void* par, void* accum) const {
    FoldPreOrder(funct, par, accum, head);
}

template <typename Data>
inline void List<Data>::FoldPreOrder(FoldFunctor funct, const void* par, void* accum) const {
    FoldPreOrder(funct, par, accum, head);
}

template <typename Data>
inline void List<Data>::FoldPostOrder(FoldFunctor funct, const void* par, void* accum) const {
    FoldPostOrder(funct, par, accum, head);
}

// FUNZIONI AUSILIARIE
template <typename Data>
void List<Data>::MapPreOrder(MapFunctor funct, void* par, Node* current) {
    for(; current != nullptr; current = current->next) {
        funct(current->element, par);
    }
}

template <typename Data>
void List<Data>::MapPostOrder(MapFunctor funct, void* par, Node* current) { // RICORSIVA IN CODA.
    if(current != nullptr) {
        MapPostOrder(funct, par, current->next);
        funct(current->element, par);
    }  
}

template <typename Data>
void List<Data>::FoldPreOrder(FoldFunctor funct, const void* par, void* accumulator, Node* current) const {
    for(; current != nullptr; current = current->next) {
        funct(current->element, par, accumulator);
    }
}

template <typename Data>
void List<Data>::FoldPostOrder(FoldFunctor funct, const void* par, void* accumulator, Node* current) const { // RICORSIVA IN CODA.
    if(current != nullptr) {
        FoldPostOrder(funct, par, accumulator, current->next); 
        funct(current->element, par, accumulator);
    }
}

}