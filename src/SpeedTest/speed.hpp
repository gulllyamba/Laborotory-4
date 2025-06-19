#ifndef SPEED_HPP
#define SPEED_HPP

#include <chrono>
#include "../tree/AVL.hpp"

void InsertTest(int size, const std::string& name) {
    std::cout << "--- Insert Test: " << name << " ---\n";
        
    AVL_Tree<int>* tree = new AVL_Tree<int>();
    
    for (int i = 1; i <= size; i++) {
        if (i == 1e3 || i == 5e3 || i == 1e4 || i == 5e4 || i == 1e5 || i == 5e5 || i ==1e6 || i == 2e6 || i == 3e6 || i == 5e6 || i == 7e6 || i == 1e7 || i == 2e7 || i == 3e7 || i == 4e7 || i == 5e7 || i == 6e7 || i == 7e7 || i == 8e7 || i == 9e7 || i == 1e8) {
            auto start = std::chrono::high_resolution_clock::now();
            tree->Insert(i);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            std::cout << "Time (" << i << "): " << duration.count() << " ns\n";
        }
        else tree->Insert(i);
    }
    std::cout << "Final size: " << tree->Size() << "\n";

    delete tree;
}

#endif // SPEED_HPP