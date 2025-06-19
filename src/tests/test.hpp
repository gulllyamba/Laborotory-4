#ifndef TEST_HPP
#define TEST_HPP

#include "../tree/AVL.hpp"
#include "../collections/Set.hpp"
#include "../collections/PriorityQueue.hpp"

void TestTree() {
    std::cout << "AVL_Tree testing...\n\n";

    bool flag = true;
    AVL_Tree<int>* tree = new AVL_Tree<int>();

    try {
        if (tree->Size() != 0) throw std::runtime_error("Size must be 0");
        if (tree->IsEmpty() != 1) throw std::runtime_error("Tree must be empty");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }

    tree->Insert(1);
    try {
        if (tree->Size() != 1) throw std::runtime_error("Size must be 1");
        if (tree->IsEmpty() != 0) throw std::runtime_error("Tree mustn't be empty");
        if (tree->GetMin() != 1) throw std::runtime_error("Min element must be 1");
        if (tree->GetMax() != 1) throw std::runtime_error("Max element must be 1");
        if (tree->Contains(1) != 1) throw std::runtime_error("Element [1] must be contained");
        if (tree->Contains(0) != 0) throw std::runtime_error("Element [0] mustn't be contained");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }

    for (int i = 2; i < 6; i++) tree->Insert(i);
    try {
        if (tree->Size() != 5) throw std::runtime_error("Size must be 5");
        if (tree->IsEmpty() != 0) throw std::runtime_error("Tree mustn't be empty");
        if (tree->GetMin() != 1) throw std::runtime_error("Min element must be 1");
        if (tree->GetMax() != 5) throw std::runtime_error("Max element must be 5");
        if (tree->Contains(1) != 1) throw std::runtime_error("Element [1] must be contained");
        if (tree->Contains(2) != 1) throw std::runtime_error("Element [2] must be contained");
        if (tree->Contains(3) != 1) throw std::runtime_error("Element [3] must be contained");
        if (tree->Contains(4) != 1) throw std::runtime_error("Element [4] must be contained");
        if (tree->Contains(5) != 1) throw std::runtime_error("Element [5] must be contained");
        if (tree->Contains(0) != 0) throw std::runtime_error("Element [0] mustn't be contained");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }

    AVL_Tree<int>* GetSub = tree->GetSubTree(4);
    try {
        if (GetSub->Size() != 3) throw std::runtime_error("Size must be 3");
        if (GetSub->IsEmpty() != 0) throw std::runtime_error("Tree mustn't be empty");
        if (GetSub->GetMin() != 3) throw std::runtime_error("Min element must be 3");
        if (GetSub->GetMax() != 5) throw std::runtime_error("Max element must be 5");
        if (GetSub->Contains(1) != 0) throw std::runtime_error("Element [1] mustn't be contained");
        if (GetSub->Contains(2) != 0) throw std::runtime_error("Element [2] mustn't be contained");
        if (GetSub->Contains(3) != 1) throw std::runtime_error("Element [3] must be contained");
        if (GetSub->Contains(4) != 1) throw std::runtime_error("Element [4] must be contained");
        if (GetSub->Contains(5) != 1) throw std::runtime_error("Element [5] must be contained");
        if (GetSub->Contains(0) != 0) throw std::runtime_error("Element [0] mustn't be contained");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }
    delete GetSub;

    AVL_Tree<int>* Con = tree->Concat(tree);
    try {
        if (Con->Size() != 10) throw std::runtime_error("Size must be 10");
        if (Con->IsEmpty() != 0) throw std::runtime_error("Tree mustn't be empty");
        if (Con->GetMin() != 1) throw std::runtime_error("Min element must be 1");
        if (Con->GetMax() != 5) throw std::runtime_error("Max element must be 5");
        if (Con->Contains(1) != 1) throw std::runtime_error("Element [1] must be contained");
        if (Con->Contains(2) != 1) throw std::runtime_error("Element [2] must be contained");
        if (Con->Contains(3) != 1) throw std::runtime_error("Element [3] must be contained");
        if (Con->Contains(4) != 1) throw std::runtime_error("Element [4] must be contained");
        if (Con->Contains(5) != 1) throw std::runtime_error("Element [5] must be contained");
        if (Con->Contains(0) != 0) throw std::runtime_error("Element [0] mustn't be contained");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }
    delete Con;

    tree->Remove(1);
    try {
        if (tree->Size() != 4) throw std::runtime_error("Size must be 4");
        if (tree->IsEmpty() != 0) throw std::runtime_error("Tree mustn't be empty");
        if (tree->GetMin() != 2) throw std::runtime_error("Min element must be 2");
        if (tree->GetMax() != 5) throw std::runtime_error("Max element must be 5");
        if (tree->Contains(1) != 0) throw std::runtime_error("Element [1] mustn't be contained");
        if (tree->Contains(2) != 1) throw std::runtime_error("Element [2] must be contained");
        if (tree->Contains(3) != 1) throw std::runtime_error("Element [3] must be contained");
        if (tree->Contains(4) != 1) throw std::runtime_error("Element [4] must be contained");
        if (tree->Contains(5) != 1) throw std::runtime_error("Element [5] must be contained");
        if (tree->Contains(0) != 0) throw std::runtime_error("Element [0] mustn't be contained");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }

    if (flag) std::cout << "Tests completed\n\n";
    else std::cout << "Tests not completed\n\n";

    delete tree;
}

void TestSet() {
    std::cout << "Set testing...\n\n";

    bool flag = true;
    Set<int>* set = new Set<int>();

    try {
        if (set->Size() != 0) throw std::runtime_error("Size must be 0");
        if (set->IsEmpty() != 1) throw std::runtime_error("Set must be empty");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }

    set->Insert(1);
    try {
        if (set->Size() != 1) throw std::runtime_error("Size must be 1");
        if (set->IsEmpty() != 0) throw std::runtime_error("Set mustn't be empty");
        if (set->Contains(1) != 1) throw std::runtime_error("Element [1] must be contained");
        if (set->Contains(0) != 0) throw std::runtime_error("Element [0] mustn't be contained");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }

    for (int i = 2; i < 6; i++) set->Insert(i);
    try {
        if (set->Size() != 5) throw std::runtime_error("Size must be 5");
        if (set->IsEmpty() != 0) throw std::runtime_error("Set mustn't be empty");
        if (set->Contains(1) != 1) throw std::runtime_error("Element [1] must be contained");
        if (set->Contains(2) != 1) throw std::runtime_error("Element [2] must be contained");
        if (set->Contains(3) != 1) throw std::runtime_error("Element [3] must be contained");
        if (set->Contains(4) != 1) throw std::runtime_error("Element [4] must be contained");
        if (set->Contains(5) != 1) throw std::runtime_error("Element [5] must be contained");
        if (set->Contains(0) != 0) throw std::runtime_error("Element [0] mustn't be contained");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }

    Set<int>* with_Union = new Set<int>();
    for (int i = 6; i < 9; i++) with_Union->Insert(i);
    Set<int>* Union = Set<int>::Union(set, with_Union);
    try {
        if (Union->Size() != 8) throw std::runtime_error("Size must be 8");
        if (Union->IsEmpty() != 0) throw std::runtime_error("Set mustn't be empty");
        if (Union->Contains(1) != 1) throw std::runtime_error("Element [1] must be contained");
        if (Union->Contains(2) != 1) throw std::runtime_error("Element [2] must be contained");
        if (Union->Contains(3) != 1) throw std::runtime_error("Element [3] must be contained");
        if (Union->Contains(4) != 1) throw std::runtime_error("Element [4] must be contained");
        if (Union->Contains(5) != 1) throw std::runtime_error("Element [5] must be contained");
        if (Union->Contains(6) != 1) throw std::runtime_error("Element [6] must be contained");
        if (Union->Contains(7) != 1) throw std::runtime_error("Element [7] must be contained");
        if (Union->Contains(8) != 1) throw std::runtime_error("Element [8] must be contained");
        if (Union->Contains(0) != 0) throw std::runtime_error("Element [0] mustn't be contained");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }
    delete Union;
    delete with_Union;

    Set<int>* with_Intersection = new Set<int>();
    for (int i = 4; i < 9; i++) with_Intersection->Insert(i);
    Set<int>* Intersection = Set<int>::Intersection(set, with_Intersection);
    try {
        if (Intersection->Size() != 2) throw std::runtime_error("Size must be 2");
        if (Intersection->IsEmpty() != 0) throw std::runtime_error("Set mustn't be empty");
        if (Intersection->Contains(1) != 0) throw std::runtime_error("Element [1] mustn't be contained");
        if (Intersection->Contains(2) != 0) throw std::runtime_error("Element [2] mustn't be contained");
        if (Intersection->Contains(3) != 0) throw std::runtime_error("Element [3] mustn't be contained");
        if (Intersection->Contains(4) != 1) throw std::runtime_error("Element [4] mustn be contained");
        if (Intersection->Contains(5) != 1) throw std::runtime_error("Element [5] mustn be contained");
        if (Intersection->Contains(0) != 0) throw std::runtime_error("Element [0] mustn't be contained");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }
    delete Intersection;
    delete with_Intersection;

    Set<int>* with_Difference = new Set<int>();
    for (int i = 4; i < 9; i++) with_Difference->Insert(i);
    Set<int>* Difference = Set<int>::Difference(set, with_Difference);
    try {
        if (Difference->Size() != 3) throw std::runtime_error("Size must be 3");
        if (Difference->IsEmpty() != 0) throw std::runtime_error("Set mustn't be empty");
        if (Difference->Contains(1) != 1) throw std::runtime_error("Element [1] must be contained");
        if (Difference->Contains(2) != 1) throw std::runtime_error("Element [2] must be contained");
        if (Difference->Contains(3) != 1) throw std::runtime_error("Element [3] must be contained");
        if (Difference->Contains(4) != 0) throw std::runtime_error("Element [4] mustn't be contained");
        if (Difference->Contains(5) != 0) throw std::runtime_error("Element [5] mustn't be contained");
        if (Difference->Contains(0) != 0) throw std::runtime_error("Element [0] mustn't be contained");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }
    delete Difference;
    delete with_Difference;

    set->Erase(1);
    try {
        if (set->Size() != 4) throw std::runtime_error("Size must be 4");
        if (set->IsEmpty() != 0) throw std::runtime_error("Set mustn't be empty");
        if (set->Contains(1) != 0) throw std::runtime_error("Element [1] mustn't be contained");
        if (set->Contains(2) != 1) throw std::runtime_error("Element [2] must be contained");
        if (set->Contains(3) != 1) throw std::runtime_error("Element [3] must be contained");
        if (set->Contains(4) != 1) throw std::runtime_error("Element [4] must be contained");
        if (set->Contains(5) != 1) throw std::runtime_error("Element [5] must be contained");
        if (set->Contains(0) != 0) throw std::runtime_error("Element [0] mustn't be contained");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }

    if (flag) std::cout << "Tests completed\n\n";
    else std::cout << "Tests not completed\n\n";

    delete set;
}

void TestPriorityQueue() {
    std::cout << "PriorityQueue testing...\n\n";

    bool flag = true;
    PriorityQueue<int>* queue = new PriorityQueue<int>();

    try {
        if (queue->Size() != 0) throw std::runtime_error("Size must be 0");
        if (queue->IsEmpty() != 1) throw std::runtime_error("Tree must be empty");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }

    queue->Push(1, 1);
    try {
        if (queue->Size() != 1) throw std::runtime_error("Size must be 1");
        if (queue->IsEmpty() != 0) throw std::runtime_error("Tree mustn't be empty");
        if (queue->Top() != 1) throw std::runtime_error("Top element must be 1");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }

    for (int i = 2; i < 6; i++) queue->Push(i, i);
    try {
        if (queue->Size() != 5) throw std::runtime_error("Size must be 5");
        if (queue->IsEmpty() != 0) throw std::runtime_error("Tree mustn't be empty");
        if (queue->Top() != 5) throw std::runtime_error("Top element must be 5");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }

    PriorityQueue<int>* GetSub = queue->GetSubQueue(1, 4);
    try {
        if (GetSub->Size() != 3) throw std::runtime_error("Size must be 3");
        if (GetSub->IsEmpty() != 0) throw std::runtime_error("Tree mustn't be empty");
        if (GetSub->Top() != 4) throw std::runtime_error("Top element must be 4");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }
    delete GetSub;

    PriorityQueue<int>* Con = queue->Concat(queue);
    try {
        if (Con->Size() != 10) throw std::runtime_error("Size must be 10");
        if (Con->IsEmpty() != 0) throw std::runtime_error("Tree mustn't be empty");
        if (Con->Top() != 5) throw std::runtime_error("Top element must be 5");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }
    delete Con;

    queue->Pop();
    try {
        if (queue->Size() != 4) throw std::runtime_error("Size must be 4");
        if (queue->IsEmpty() != 0) throw std::runtime_error("Tree mustn't be empty");
        if (queue->Top() != 4) throw std::runtime_error("Top element must be 4");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error. " << e.what() << "\n";
        flag = false;
    }
    catch (...) {
        std::cerr << "Unknown error!" << "\n";
        flag = false;
    }

    if (flag) std::cout << "Tests completed\n\n";
    else std::cout << "Tests not completed\n\n";

    delete queue;
}

#endif // TEST_HPP