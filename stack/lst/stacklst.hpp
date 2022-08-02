
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>, 
                 virtual protected List<Data> {
private:

protected:
  using List<Data>::size;
  using List<Data>::head;

public:
  // Default constructor
  StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor: a stack obtained from a LinearContainer.
  StackLst(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor and Move constructor.
  StackLst(const StackLst&);
  StackLst(StackLst&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackLst();

  /* ************************************************************************ */

  // Copy assignment and Move assignment. 
  StackLst& operator=(const StackLst&);
  StackLst& operator=(StackLst&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackLst&) const noexcept;
  inline bool operator!=(const StackLst&) const noexcept;

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
  void Clear() override; // Override Container member
};

/* ************************************************************************** */

}

#include "stacklst.cpp"
#endif