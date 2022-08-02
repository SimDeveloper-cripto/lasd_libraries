#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : virtual public Queue<Data>, virtual protected Vector<Data> {
private:

protected:  
  ulong testa = 0;
  ulong coda = 0;
  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:
  // Default constructor
  QueueVec() : Vector<Data>(1) {};

  /* ************************************************************************ */

  // Specific constructor: a queue obtained from a LinearContainer
  QueueVec(const LinearContainer<Data>&); 

  /* ************************************************************************ */

  // Copy constructor and Move constructor.
  QueueVec(const QueueVec& queue) : Vector<Data>(queue), testa(queue.testa), coda(queue.coda) {};
  QueueVec(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  QueueVec& operator=(const QueueVec&);
  QueueVec& operator=(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec&) const noexcept;
  inline bool operator!=(const QueueVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)
  const Data& Head() const override;  // Override Queue member (constant version; must throw std::length_error when empty)
  Data& Head() override;              // Override Queue member (must throw std::length_error when empty)
  void Dequeue() override;            // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override;       // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) override;      // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  inline bool Empty() const noexcept override; // Override Container member
  inline ulong Size() const noexcept override; // Override Container member
  void Clear() override;                       // Override Container member

protected:
  void Expand();
  void Reduce();
  void SwapVectors(ulong);
};

/* ************************************************************************** */
}

#include "queuevec.cpp"
#endif