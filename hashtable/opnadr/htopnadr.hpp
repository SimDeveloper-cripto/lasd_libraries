
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> { // Must extend HashTable<Data>

private:

protected:
  using HashTable<Data>::a;
  using HashTable<Data>::b;
  using HashTable<Data>::p;
  using HashTable<Data>::size;
  using HashTable<Data>::tab_size;
  using HashTable<Data>::HashKey;

  Vector<Data> vec {};
  Vector<ushort> vec_flag {};
  const ushort c = 7;

  /*
    Vettore delle flag:
      (0) indica che il dato non è presente.
      (1) indica che il dato era presente ma è stato cancellato.
      (2) indica che il dato è presente.
  */

public:
  // Default constructor
  HashTableOpnAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(const ulong);                               // A hash table of a given size
  HashTableOpnAdr(const LinearContainer<Data>&);              // A hash table obtained from a LinearContainer
  HashTableOpnAdr(const ulong, const LinearContainer<Data>&); // A hash table of a given size obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr&);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr&);

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr&) const noexcept;
  bool operator!=(const HashTableOpnAdr&) const noexcept;

  /* ************************************************************************ */

  virtual void Resize(ulong); // Resize the hashtable to a given size

  /* ************************************************************************ */

  virtual bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  virtual bool Insert(Data&&) override;      // Override DictionaryContainer member (Move of the value)
  virtual bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  virtual bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  using typename MappableContainer<Data>::MapFunctor;
  virtual void Map(MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  using typename FoldableContainer<Data>::FoldFunctor; 
  virtual void Fold(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  virtual void Clear() override; // Override Container member

protected:
  void Expand();
  void initializeVecFlag(const ulong);
  const ulong HashKey(const Data&, const ulong) const;
  const ulong findCorrectTableSize(ulong) const;
};

/* ************************************************************************** */

}

#include "htopnadr.cpp"
#endif