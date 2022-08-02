
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../../bst/bst.hpp"
#include "../../vector/vector.hpp"
#include "../hashtable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr : virtual public HashTable<Data> { // Must extend HashTable<Data>

private:

protected:
  using HashTable<Data>::a;
  using HashTable<Data>::b;
  using HashTable<Data>::p;
  using HashTable<Data>::size;
  using HashTable<Data>::tab_size;
  using HashTable<Data>::HashKey;

  Vector<BST<Data>> vec {};

public:
  // Default constructor
  HashTableClsAdr() = default;

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(const ulong);                               // A hash table of a given size
  HashTableClsAdr(const LinearContainer<Data>&);              // A hash table obtained from a LinearContainer
  HashTableClsAdr(const ulong, const LinearContainer<Data>&); // A hash table of a given size obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr&);

  // Move constructor
  HashTableClsAdr(HashTableClsAdr&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableClsAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr& operator=(const HashTableClsAdr&);

  // Move assignment
  HashTableClsAdr& operator=(HashTableClsAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr&) const noexcept;
  bool operator!=(const HashTableClsAdr&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from HashTable)

  virtual void Resize(ulong); // Resize the hashtable to a given size

  /* ************************************************************************ */

  virtual bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  virtual bool Insert(Data&&) override;      // Override DictionaryContainer member (Move of the value)
  virtual bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  virtual bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  using typename MappableContainer<Data>::MapFunctor;
  void Map(MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  using typename FoldableContainer<Data>::FoldFunctor; 
  void Fold(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  virtual void Clear() override; // Override Container member
};

/* ************************************************************************** */

}

#include "htclsadr.cpp"
#endif