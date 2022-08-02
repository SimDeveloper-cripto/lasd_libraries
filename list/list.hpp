#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public LinearContainer<Data>, 
             virtual public PreOrderMappableContainer<Data>, 
             virtual public PostOrderMappableContainer<Data>, 
             virtual public PreOrderFoldableContainer<Data>, 
             virtual public PostOrderFoldableContainer<Data> {
private:

protected:
  using LinearContainer<Data>::size;

  struct Node {
    Data element;
    Node* next = nullptr;

    /* ********************************************************************** */

    inline Node() = default; // Costruttore di default

    // Specific constructors
    inline Node(const Data& data) : element(data) {};
    inline Node(Data&&) noexcept;

    // Constructors
    inline Node(const Node& node) : element(node.element) {}; // Copy constructor
    inline Node(Node&& node) noexcept;                        // Move constructor

    // Destructor
    virtual ~Node(); 

    // Comparison operators
    bool operator==(const Node&) const noexcept;
    bool operator!=(const Node&) const noexcept;
  };

  Node* head = nullptr;
  Node* tail = nullptr;

public:
  List() = default;
  List(const LinearContainer<Data>&); // A list obtained from a LinearContainer.
  
  List(const List&);     // Copy constructor
  List(List&&) noexcept; // Move constructor

  virtual ~List(); // Destructor

  /* ************************************************************************ */

  List& operator=(const List&);     // Copy assignment
  List& operator=(List&&) noexcept; // Move assignment

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List&) const noexcept;
  bool operator!=(const List&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions
  void InsertAtFront(const Data&);    // Copy of the value
  void InsertAtFront(Data&&);         // Move of the value
  void RemoveFromFront();             // (must throw std::length_error when empty)
  Data FrontNRemove();                // (must throw std::length_error when empty)

  void InsertAtBack(const Data&) noexcept; // Copy of the value
  void InsertAtBack(Data&&);               // Move of the value

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& Front() const override;           // Override LinearContainer member (must throw std::length_error when empty)
  Data& Back() const override;            // Override LinearContainer member (must throw std::length_error when empty)
  Data& operator[](ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer).
  using typename MappableContainer<Data>::MapFunctor;
  void Map(MapFunctor, void*) override; 

  // Override MappableContainer member.
  void MapPreOrder(MapFunctor, void*) override;
  void MapPostOrder(MapFunctor, void*) override;

  // Specific member functions (inherited from FoldableContainer).
  using typename FoldableContainer<Data>::FoldFunctor;
  void Fold(FoldFunctor, const void*, void*) const override;

  // Override FoldableContainer member.
  void FoldPreOrder(FoldFunctor, const void*, void*) const override;
  void FoldPostOrder(FoldFunctor, const void*, void*) const override;

protected:
  void MapPreOrder(MapFunctor, void*, Node*);
  void MapPostOrder(MapFunctor, void*, Node*);
  void FoldPreOrder(FoldFunctor, const void*, void*, Node*) const;
  void FoldPostOrder(FoldFunctor, const void*, void*, Node*) const;
};

}

#include "list.cpp"
#endif