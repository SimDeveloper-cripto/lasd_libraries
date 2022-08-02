
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Iterator {

private:

protected:

public:
  // Destructor
  virtual ~Iterator() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  Iterator& operator=(const Iterator&) = delete;
  Iterator& operator=(Iterator&&) noexcept = delete; 

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Iterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Iterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  virtual Data& operator*() const = 0;          // (concrete function must throw std::out_of_range when terminated)
  virtual bool Terminated() const noexcept = 0; // (concrete function should not throw exceptions)
};

/* ************************************************************************** */

template <typename Data>
class ForwardIterator : virtual public Iterator<Data> { // Must extend Iterator<Data>

private:

protected:

public:
  // Destructor
  virtual ~ForwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  ForwardIterator& operator=(const ForwardIterator&) = delete;     // Copy assignment of abstract types should not be possible.
  ForwardIterator& operator=(ForwardIterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ForwardIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const ForwardIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  virtual ForwardIterator& operator++() = 0; // (concrete function must throw std::out_of_range when terminated)
};

/* ************************************************************************** */

template <typename Data>
class BackwardIterator : virtual public Iterator<Data> { // Must extend Iterator<Data>

private:

protected:

public:
  // Destructor
  virtual ~BackwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  BackwardIterator& operator=(const BackwardIterator&) = delete;     // Copy assignment of abstract types should not be possible.
  BackwardIterator& operator=(BackwardIterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BackwardIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BackwardIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  virtual BackwardIterator& operator--() = 0; // (concrete function must throw std::out_of_range when terminated)
};

/* ************************************************************************** */

template <typename Data>
class BidirectionalIterator : virtual public ForwardIterator<Data>, virtual public BackwardIterator<Data> {

private:

protected:

public:
  // Destructor
  virtual ~BidirectionalIterator() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  BidirectionalIterator& operator=(const BidirectionalIterator&) = delete;     // Copy assignment of abstract types should not be possible.
  BidirectionalIterator& operator=(BidirectionalIterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BidirectionalIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BidirectionalIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  virtual bool Terminated() const noexcept override;    // Override Iterator member

  virtual bool ForwardTerminated() const noexcept  = 0; // (concrete function should not throw exceptions)
  virtual bool BackwardTerminated() const noexcept = 0; // (concrete function should not throw exceptions)
};

/* ************************************************************************** */

template <typename Data>
class ResettableIterator : virtual public Iterator<Data> { // Must extend Iterator<Data>

private:

protected:

public:
  // Destructor
  virtual ~ResettableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment and Move assignment
  ResettableIterator& operator=(const ResettableIterator&) = delete;     // Copy assignment of abstract types should not be possible.
  ResettableIterator& operator=(ResettableIterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResettableIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const ResettableIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  virtual void Reset() noexcept = 0; // (concrete function should not throw exceptions)
};

/* ************************************************************************** */

}

#endif