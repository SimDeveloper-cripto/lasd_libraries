
#include <random>
#include <iostream>
#include "usertest.hpp"

using namespace lasd; // Each Data Structure is defined inside "lasd" namespace

int generate_random_number() {
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> dist(-200, 200);
    return dist(generator);
}

namespace usertest {
    void run_test() {
        std::cout << std::endl << "[OK] USER TEST STARTED" << std::endl << std::endl;

        /* [INSERT YOUR CODE HERE] */

/* (THIS WAS AN OLD TEST MADE FOR SORTING ALGORITHMS)
        Vector<int>* vec = new Vector<int>(10);
        for (int i = 0; i < 10; i++) {
            vec->operator[](i) = generate_random_number();
        }

        for (int i = 0; i < vec->Size(); i++)
            std::cout << vec->operator[](i) << " ";

        std::cout << std::endl << std::endl << "Sorted Vector: " << std::endl;
        vec->InsertionSort();
        // vec->SelectionSort();
        for (int i = 0; i < vec->Size(); i++) std::cout << vec->operator[](i) << " ";

        std::cout << std::endl;
        delete vec;
*/

        Vector<int>* vec = new Vector<int>(10);
        for (int i = 0; i < 10; i++) {
            vec->operator[](i) = generate_random_number();
        }

        // Initialize BTLink with the LinearContainer (a Vector in this case)
        BinaryTreeLnk<int> bt(*vec);
        delete vec;

        bt.Reverse(&bt.Root());
        /* [END] */
    }
}