
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

#include <stdexcept>
#include <functional>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

private:

protected:
  ulong size = 0; 

public:
  // Destructor
  virtual ~Container() = default;

  /* ************************************************************************ */

  // Copy assignment
  Container& operator=(const Container&) = delete;
  // Move assignment
  Container& operator=(Container&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Container&) const noexcept = delete;
  bool operator!=(const Container&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  inline virtual bool Empty() const { // (concrete function should not throw exceptions).
    return (size == 0);
  } 

  inline virtual ulong Size() const noexcept { // (concrete function should not throw exceptions).
    return size;
  }

  virtual void Clear() = 0; // A questo livello di astrazioni non siamo in grado di implementarla.
};

/* ************************************************************************** */

template <typename Data> 
class LinearContainer : virtual public Container { // Must extend Container

private:

protected:

public:
  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer& operator=(const LinearContainer&) = delete;
  // Move assignment
  LinearContainer& operator=(LinearContainer&&) noexcept = delete;
  
  /* ************************************************************************ */

  // Comparison operators: // Comparison of abstract types is possible.
  inline bool operator==(const LinearContainer&) const noexcept;
  inline bool operator!=(const LinearContainer&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions
  inline virtual Data& Front() const;        // (concrete function must throw std::length_error when empty)
  inline virtual Data& Back() const;         // (concrete function must throw std::length_error when empty)
  virtual Data& operator[](ulong) const = 0; // (concrete function must throw std::out_of_range when out of range)
};

/* ************************************************************************** */

template <typename Data>
class TestableContainer : virtual public Container { // Must extend Container

private:

protected:

public:
  // Destructor
  virtual ~TestableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  TestableContainer& operator=(const TestableContainer&) = delete;

  // Move assignment
  TestableContainer& operator=(TestableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TestableContainer&) const noexcept = delete;
  bool operator!=(const TestableContainer&) const noexcept = delete;
  
  /* ************************************************************************ */

  // Specific member functions
  virtual bool Exists(const Data&) const noexcept = 0; // (concrete function should not throw exceptions) 
};

/* ************************************************************************** */

template<typename Data>
class DictionaryContainer : virtual public TestableContainer<Data> {

private: 

protected: 

public: 
  // Destructor
  virtual ~DictionaryContainer() = default;

  // Copy assignment 
  DictionaryContainer& operator=(const DictionaryContainer&) = delete;     // Copy assignment of abstract types should not be possible

  // Move assignment
  DictionaryContainer& operator=(DictionaryContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible

  // Comparison operators : comparison of abstract type class might not be possible.
  bool operator==(const DictionaryContainer&) const noexcept = delete; 
  bool operator!=(const DictionaryContainer&) const noexcept = delete;

  // Specific member functions
  virtual bool Insert(const Data&) = 0; // Copy of the value.
  virtual bool Insert(Data&&) = 0;      // Move of the value.
  virtual bool Remove(const Data&) = 0;

  virtual void Insert(const LinearContainer<Data>&); // Copy of the value; From LinearContainer
  virtual void Insert(LinearContainer<Data>&&);      // Move of the value; From LinearContainer
  virtual void Remove(const LinearContainer<Data>&); // From LinearContainer
};

/* ************************************************************************** */


template <typename Data>
class MappableContainer : virtual public Container { // Must extend Container

private:

protected:

public:
  // Destructor
  virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MappableContainer& operator=(const MappableContainer&) = delete;

  // Move assignment
  MappableContainer& operator=(MappableContainer&&) noexcept = delete;
  
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MappableContainer&) const noexcept = delete;
  bool operator!=(const MappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  typedef std::function<void(Data&, void*)> MapFunctor;
  virtual void Map(MapFunctor, void*) = 0; // A tale livello di astrazione non può essere implementata.
};

/* ************************************************************************** */

template <typename Data>
class FoldableContainer : virtual public TestableContainer<Data> { // Must extend TestableContainer<Data>

private:

protected:

public:
  // Destructor
  virtual ~FoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  FoldableContainer& operator=(const FoldableContainer&) = delete;
  // Move assignment
  FoldableContainer& operator=(FoldableContainer&&) noexcept = delete;
  
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const FoldableContainer&) const noexcept = delete;
  bool operator!=(const FoldableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  typedef std::function<void(const Data&, const void*, void*)> FoldFunctor;
  virtual void Fold(FoldFunctor, const void*, void*) const = 0;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  inline virtual bool Exists(const Data&) const noexcept override; // Override TestableContainer member
};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer : virtual public MappableContainer<Data> { // Must extend MappableContainer<Data>

private:

protected:

public:
  // Destructor
  virtual ~PreOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderMappableContainer& operator=(const PreOrderMappableContainer&) = delete;

  // Move assignment
  PreOrderMappableContainer& operator=(PreOrderMappableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderMappableContainer&) const noexcept = delete;
  bool operator!=(const PreOrderMappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  using typename MappableContainer<Data>::MapFunctor;
  virtual void MapPreOrder(MapFunctor, void*) = 0;

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)
  inline virtual void Map(MapFunctor, void*) override; // Override MappableContainer member
};

/* ************************************************************************** */

template <typename Data>
class PreOrderFoldableContainer : virtual public FoldableContainer<Data> { // Must extend FoldableContainer<Data>

private:

protected:

public:
  // Destructor
  virtual ~PreOrderFoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderFoldableContainer& operator=(const PreOrderFoldableContainer&) = delete;

  // Move assignment
  PreOrderFoldableContainer& operator=(PreOrderFoldableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderFoldableContainer&)const noexcept = delete;
  bool operator!=(const PreOrderFoldableContainer&)const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  using typename FoldableContainer<Data>::FoldFunctor;
  virtual void FoldPreOrder(FoldFunctor, const void*, void*) const = 0;

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)
  inline virtual void Fold(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member  
};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer : virtual public MappableContainer<Data> { // Must extend MappableContainer<Data>

private:

protected:

public:
  // Destructor
  virtual ~PostOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderMappableContainer& operator=(const PostOrderMappableContainer&) = delete;

  // Move assignment
  PostOrderMappableContainer& operator=(PostOrderMappableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderMappableContainer&) const noexcept = delete;
  bool operator!=(const PostOrderMappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  using typename MappableContainer<Data>::MapFunctor;
  virtual void MapPostOrder(MapFunctor, void*) = 0;

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)
  inline virtual void Map(MapFunctor, void*) override; // Override MappableContainer member
};

/* ************************************************************************** */

template <typename Data>
class PostOrderFoldableContainer : virtual public FoldableContainer<Data> { // Must extend FoldableContainer<Data>

private:

protected:

public:
  // Destructor
  virtual ~PostOrderFoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderFoldableContainer& operator=(const PostOrderFoldableContainer&) = delete;

  // Move assignment
  PostOrderFoldableContainer& operator=(PostOrderFoldableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderFoldableContainer&) const noexcept = delete;
  bool operator!=(const PostOrderFoldableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  using typename FoldableContainer<Data>::FoldFunctor;
  virtual void FoldPostOrder(FoldFunctor, const void*, void*) const = 0;

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)
  inline virtual void Fold(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
};

/* ************************************************************************** */

template <typename Data>
class InOrderMappableContainer : virtual public MappableContainer<Data> { // Must extend MappableContainer<Data>

private:

protected:

public:
  // Destructor
  virtual ~InOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  InOrderMappableContainer& operator=(const InOrderMappableContainer&) = delete;     // Copy assignment of abstract types should not be possible.
  InOrderMappableContainer& operator=(InOrderMappableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderMappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const InOrderMappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  using typename MappableContainer<Data>::MapFunctor;
  virtual void MapInOrder(MapFunctor, void*) = 0;

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)
  inline virtual void Map(MapFunctor, void*) override; // Override MappableContainer member
};

/* ************************************************************************** */

template <typename Data>
class InOrderFoldableContainer : virtual public FoldableContainer<Data> { // Must extend FoldableContainer<Data>

private:

protected:

public:
  // Destructor
  virtual ~InOrderFoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  InOrderFoldableContainer& operator=(const InOrderFoldableContainer&) = delete;     // Copy assignment of abstract types should not be possible.
  InOrderFoldableContainer& operator=(InOrderFoldableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderFoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const InOrderFoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  using typename FoldableContainer<Data>::FoldFunctor;
  virtual void FoldInOrder(FoldFunctor, const void*, void*) const = 0;

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)
  inline virtual void Fold(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
};

/* ************************************************************************** */

template <typename Data>
class BreadthMappableContainer : virtual public MappableContainer<Data> { // Must extend MappableContainer<Data>

private:

protected:

public:
  // Destructor
  virtual ~BreadthMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  BreadthMappableContainer& operator=(const BreadthMappableContainer&) = delete;     // Copy assignment of abstract types should not be possible.
  BreadthMappableContainer& operator=(BreadthMappableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthMappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BreadthMappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  using typename MappableContainer<Data>::MapFunctor;
  virtual void MapBreadth(MapFunctor, void*) = 0;

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)
  inline virtual void Map(MapFunctor, void*) override; // Override MappableContainer member
};

/* ************************************************************************** */

template <typename Data>
class BreadthFoldableContainer : virtual public FoldableContainer<Data> { // Must extend FoldableContainer<Data>

private:

protected:

public:
  // Destructor
  virtual ~BreadthFoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  BreadthFoldableContainer& operator=(const BreadthFoldableContainer&) = delete;     // Copy assignment of abstract types should not be possible.
  BreadthFoldableContainer& operator=(BreadthFoldableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthFoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BreadthFoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  using typename FoldableContainer<Data>::FoldFunctor;
  virtual void FoldBreadth(FoldFunctor, const void*, void*) const = 0;

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)
  inline virtual void Fold(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
};

/* ************************************************************************** */

}

#include "container.cpp"
#endif