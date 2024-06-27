#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public LinearContainer<Data>, 
               virtual public PreOrderMappableContainer<Data>,
               virtual public PostOrderMappableContainer<Data>,
               virtual public PreOrderFoldableContainer<Data>,
               virtual public PostOrderFoldableContainer<Data> {
private:

protected:
  using LinearContainer<Data>::size;
  Data* Elements = nullptr;

public:
  Vector() = default;                   // Default constructor
  Vector(const ulong);                  // A vector with a given initial dimension
  Vector(const LinearContainer<Data>&); // A vector obtained from a LinearContainer
  
  /* ************************************************************************ */

  Vector(const Vector&);     // Copy constructor
  Vector(Vector&&) noexcept; // Move constructor

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  Vector& operator=(const Vector&) noexcept; // Copy assignment
  Vector& operator=(Vector&&) noexcept;      // Move assignment
  
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector&) const noexcept;
  inline bool operator!=(const Vector&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions
  void Resize(const ulong); // Resize the vector to a given size

  // Specific member functions (inherited from Container)
  void Clear() override; // Override Container member

  // Specific member functions (inherited from LinearContainer)
  Data& Front() const override;                 // Override LinearContainer member (must throw std::length_error when empty)
  Data& Back() const override;                  // Override LinearContainer member (must throw std::length_error when empty)
  Data& operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFunctor;
  void Map(MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PreOrderMappableContainer)
  void MapPreOrder(MapFunctor, void*) override; // Override PreOrderMappableContainer member

  // Specific member functions (inherited from PostOrderMappableContainer)
  void MapPostOrder(MapFunctor, void*) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)
  using typename FoldableContainer<Data>::FoldFunctor;
  void Fold(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  // Specific member functions (inherited from PreOrderFoldableContainer)
  void FoldPreOrder(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  // Specific member functions (inherited from PostOrderFoldableContainer)
  void FoldPostOrder(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************** */
  // SECTION DEDICATED TO SORTING ALGORITHMS

  int FindMax(const int limit); // Helper function

  void InsertionSort();
  void SelectionSort();
  // void MergeSort();
  // void QuickSort();
  // void HeapSort();

  /* ************************************************************************** */

};

/* ************************************************************************** */

}

#include "vector.cpp"
#endif