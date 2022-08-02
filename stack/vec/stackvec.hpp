#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>, 
                 virtual protected Vector<Data> {
private:

protected:
  ulong index = 0;          // POSIZIONE DELLA TESTA STACK
  using Vector<Data>::size; // DIMENSIONE DELL'ARRAY
  using Vector<Data>::Elements;

public:
  // Default constructor
  StackVec() : Vector<Data>(1) {};

  /* ************************************************************************ */

  StackVec(const LinearContainer<Data>& linear_container) : Vector<Data>(linear_container), index(size) {}; 

  /* ************************************************************************ */

  // Copy constructor and Move constructor
  StackVec(const StackVec& stack) : Vector<Data>(stack), index(stack.index) {};
  StackVec(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  StackVec& operator=(const StackVec&);
  StackVec& operator=(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec&) const noexcept;
  inline bool operator!=(const StackVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)
  const Data& Top() const override; // Override Stack member (constant version; must throw std::length_error when empty)
  Data& Top() override;             // Override Stack member (must throw std::length_error when empty)
  void Pop() override;              // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override;          // Override Stack member (must throw std::length_error when empty)
  void Push(const Data&) override;  // Override Stack member (copy of the value)
  void Push(Data&&) override;       // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  inline bool Empty() const noexcept override; // Override Container member
  inline ulong Size() const noexcept override; // Override Container member
  void Clear() override;                       // Override Container member

protected:
  void Expand();
  void Reduce();
};

/* ************************************************************************** */
}

#include "stackvec.cpp"
#endif