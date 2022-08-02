
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>
#include <cmath>

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hash {

public:
  ulong operator()(const Data&) const noexcept; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public DictionaryContainer<Data>, 
                  virtual public MappableContainer<Data>,
                  virtual public FoldableContainer<Data> { 

private:

protected:
  using DictionaryContainer<Data>::size;
  const unsigned long long p = 109297270343;
  unsigned long long a;
  unsigned long long b;
  ulong tab_size = 128;
  Hash<Data> hash;

  HashTable();
  HashTable(const HashTable&);
  HashTable(HashTable&&) noexcept;

public:
  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable& operator=(const HashTable&) = delete;     // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator=(HashTable&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable&) const noexcept = delete;
  bool operator!=(const HashTable&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function
  virtual void Resize(ulong) = 0; // Resize the hashtable to a given size

protected:
  const ulong HashKey(const Data&) const;

};

/* ************************************************************************** */

}

#include "hashtable.cpp"
#endif