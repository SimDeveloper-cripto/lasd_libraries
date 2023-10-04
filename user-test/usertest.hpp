#ifndef USER_TEST_HPP
#define USER_TEST_HPP

/* LIST OF ALL THE LIBRARIES */

#include "../vector/vector.hpp"
#include "../list/list.hpp"

#include "../stack/lst/stacklst.hpp" // Stack implemented by using a Linked List
#include "../stack/vec/stackvec.hpp" // Stack implemented by using a Vector

#include "../queue/lst/queuelst.hpp" // Queue implemented by using a Linked List
#include "../queue/vec/queuevec.hpp" // Queue implemented by using a Vector

#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/vec/binarytreevec.hpp" // Binary Tree implemented by using Vector

#include "../bst/bst.hpp" // Basic Binary Search Tree (it is not AVL nor Red-Black and so on...)

#include "../hashtable/clsadr/htclsadr.hpp" // HashTable implemented by closed addressing
#include "../hashtable/opnadr/htopnadr.hpp" // HashTable implemented by open addressing

namespace usertest {
    void run_test();
}

#endif /* USER_TEST_HPP */