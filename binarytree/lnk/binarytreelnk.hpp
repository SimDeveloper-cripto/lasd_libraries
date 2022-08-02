
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data> { 

private:

protected:
  using BinaryTree<Data>::size;

  struct NodeLnk : virtual public BinaryTree<Data>::Node { // Must extend Node 

  private:

  protected:

  public:
    Data element; 
    NodeLnk* leftchild = nullptr;
    NodeLnk* rightchild = nullptr;

    // COSTRUTTORE
    NodeLnk(const Data&);
    
    // DISTRUTTORE
    virtual ~NodeLnk();

    NodeLnk& operator=(const NodeLnk&);
    NodeLnk& operator=(NodeLnk&&) noexcept;

    Data& Element() noexcept override;
    const Data& Element() const noexcept override;
    bool HasLeftChild() const noexcept override;
    bool HasRightChild() const noexcept override;
    NodeLnk& LeftChild() const override;
    NodeLnk& RightChild() const override;
  };

  void versaLinearContainerInBinaryTree(int, NodeLnk*, const LinearContainer<Data>&);
  NodeLnk* copiaAlbero(NodeLnk*);
  NodeLnk* root = nullptr;

public:
  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk&) const noexcept;
  bool operator!=(const BinaryTreeLnk&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  void Clear() override; // Override Container member
};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"
#endif