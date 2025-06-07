#include "tree/AVL.hpp"
#include "collections/Set.hpp"
#include "collections/PriorityQueue.hpp"
#include "../auxiliary/Complex.hpp"

int main() {
    // Дерево - int

    // AVL_Tree<int>* tree = new AVL_Tree<int>();

    // for (int i = 0; i < 10; i++) {
    //     tree->Insert(i);
    // }
    
    // std::cout << "Iterator++: ";
    // for (auto it = tree->begin(); it != tree->end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << "\n\n";

    // std::cout << "Iterator--: ";
    // for (auto it = --tree->end(); it != tree->begin(); --it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << *tree->begin() << "\n\n";

    // tree->PreOrder([](const int& value) {std::cout << value << " ";});
    // std::cout << "\tКЛП\n";
    // tree->ReversePreOrder([](const int& value) {std::cout << value << " ";});
    // std::cout << "\tКПЛ\n";
    // tree->InOrder([](const int& value) {std::cout << value << " ";});
    // std::cout << "\tЛКП\n";
    // tree->ReverseInOrder([](const int& value) {std::cout << value << " ";});
    // std::cout << "\tПКЛ\n";
    // tree->PostOrder([](const int& value) {std::cout << value << " ";});
    // std::cout << "\tЛПК\n";
    // tree->ReversePostOrder([](const int& value) {std::cout << value << " ";});
    // std::cout << "\tПЛК\n\n";

    // std::cout << "min: " << tree->GetMin() << "\n";
    // std::cout << "max: " << tree->GetMax() << "\n\n";

    // AVL_Tree<int>* copy = new AVL_Tree<int>(*tree);
    // std::cout << "Copy: ";
    // copy->InOrder([](const int& value) {std::cout << value << " ";});
    // std::cout << "\n\n";

    // AVL_Tree<int>* sub = tree->GetSubTree(3);
    // std::cout << "GetSubTree: ";
    // sub->InOrder([](const int& value) {std::cout << value << " ";});
    // std::cout << "\n\n";

    // AVL_Tree<int>* con = tree->Concat(tree);
    // std::cout << "Con: ";
    // con->InOrder([](const int& value) {std::cout << value << " ";});
    // std::cout << "\n\n";

    // con->Clutch(tree);
    // std::cout << "Clutch: ";
    // con->InOrder([](const int& value) {std::cout << value << " ";});
    // std::cout << "\n\n";

    // std::function<int(int)> square = [](int x) ->int {return x * x;};
    // AVL_Tree<int>* Map = tree->Map(square);
    // std::cout << "Map: ";
    // Map->InOrder([](const int& value) {std::cout << value << " ";});
    // std::cout << "\n\n";

    // std::function<bool(int)> If = [](int x) ->int {return x >= 5;};
    // AVL_Tree<int>* Where = tree->Where(If);
    // std::cout << "Where: ";
    // Where->InOrder([](const int& value) {std::cout << value << " ";});
    // std::cout << "\n\n";

    // std::string s = "10, 20, 30, 40, 50";
    // AVL_Tree<int>* fromString = AVL_Tree<int>::fromString(s);
    // std::cout << "fromString: ";
    // fromString->InOrder([](const int& value) {std::cout << value << " ";});
    // std::cout << "\n\n";

    // std::cout << "toString:\n";
    // std::cout << tree->toString(BypassType::PreOrder) << "\tКЛП\n";
    // std::cout << tree->toString(BypassType::ReversePreOrder) << "\tКПЛ\n";
    // std::cout << tree->toString(BypassType::InOrder) << "\tЛКП\n";
    // std::cout << tree->toString(BypassType::ReverseInOrder) << "\tПКЛ\n";
    // std::cout << tree->toString(BypassType::PostOrder) << "\tЛПК\n";
    // std::cout << tree->toString(BypassType::ReversePostOrder) << "\tПЛК\n\n";

    // delete tree;
    // delete copy;
    // delete sub;
    // delete con;
    // delete Map;
    // delete Where;
    // delete fromString;

    //AVL with Complex

    // AVL_Tree<Complex<int>>* tree = new AVL_Tree<Complex<int>>();

    // for (int i = 0; i < 10; i++) {
    //     tree->Insert(Complex<int>(i, i));
    //     std::cout << "Вставили: " << Complex<int>(i, i).toString_Complex() << "\n";
    // }

    // tree->Insert(Complex<int>(3, 3));

    // std::cout << "\nSize: " << tree->Size() << "\n";

    // tree->PreOrder([](const Complex<int>& value) {std::cout << value.toString_Complex() << " ";});
    // std::cout << "\tКЛП\n";
    // tree->ReversePreOrder([](const Complex<int>& value) {std::cout << value.toString_Complex() << " ";});
    // std::cout << "\tКПЛ\n";
    // tree->InOrder([](const Complex<int>& value) {std::cout << value.toString_Complex() << " ";});
    // std::cout << "\tЛКП\n";
    // tree->ReverseInOrder([](const Complex<int>& value) {std::cout << value.toString_Complex() << " ";});
    // std::cout << "\tПКЛ\n";
    // tree->PostOrder([](const Complex<int>& value) {std::cout << value.toString_Complex() << " ";});
    // std::cout << "\tЛПК\n";
    // tree->ReversePostOrder([](const Complex<int>& value) {std::cout << value.toString_Complex() << " ";});
    // std::cout << "\tПЛК\n";

    // std::cout << "min: " << tree->GetMin().toString_Complex() << "\n";
    // std::cout << "max: " << tree->GetMax().toString_Complex() << "\n";

    // for (int i = 9; i >= 0; i--) {
    //     if (tree->Remove(Complex<int>(i, i))) std::cout << "Удалили: " << Complex<int>(i, i).toString_Complex() << "\n";
    //     else {
    //         std::cout << "error\n";
    //         delete tree;
    //         return 0;
    //     }
    // }

    // tree->Remove(Complex<int>(3, 3));

    // std::cout << "\nSize: " << tree->Size() << "\n";

    // delete tree;

    ///////////////////////////////////////////////////////////////////////

    // Дерево - char
    // AVL_Tree<char>* tree = new AVL_Tree<char>();

    // tree->Insert('a');
    // tree->Insert('b');
    // tree->Insert('c');

    // std::cout << "\nSize: " << tree->Size() << "\n";

    // tree->PreOrder([](const char& value) {std::cout << value << " ";});
    // std::cout << "\tКЛП\n";
    // tree->ReversePreOrder([](const char& value) {std::cout << value << " ";});
    // std::cout << "\tКПЛ\n";
    // tree->InOrder([](const char& value) {std::cout << value << " ";});
    // std::cout << "\tЛКП\n";
    // tree->ReverseInOrder([](const char& value) {std::cout << value << " ";});
    // std::cout << "\tПКЛ\n";
    // tree->PostOrder([](const char& value) {std::cout << value << " ";});
    // std::cout << "\tЛПК\n";
    // tree->ReversePostOrder([](const char& value) {std::cout << value << " ";});
    // std::cout << "\tПЛК\n";

    // tree->Remove('a');
    // tree->Remove('b');
    // tree->Remove('c');
    // tree->Remove('d');

    // std::cout << "\nSize: " << tree->Size() << "\n";

    // delete tree;

    //////////////////////////////////////////////////////////

    // Set

    // Set<int>* A = new Set<int>();
    // Set<int>* B = new Set<int>();

    // A->Insert(1); B->Insert(4);
    // A->Insert(2); B->Insert(5);
    // A->Insert(3); B->Insert(3);

    // std::cout << "Iterator++: ";
    // for (auto it = A->begin(); it != A->end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << "\n\n";

    // std::cout << "Iterator--: ";
    // for (auto it = --A->end(); it != A->begin(); --it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << *A->begin() << "\n\n";

    // std::cout << "A: " << A->toString() << "\n";
    // std::cout << "B: " << B->toString() << "\n\n";

    // A->Union(B);
    // std::cout << "Union: " << A->toString() << "\n";
    // Set<int>* C = Set<int>::Union(A, B);
    // std::cout << "Union C: " << C->toString() << "\n\n";

    // A->Intersection(B);
    // std::cout << "Intersection: " << A->toString() << "\n";
    // Set<int>* D = Set<int>::Intersection(C, B);
    // std::cout << "Intersection D: " << D->toString() << "\n\n";

    // A->Difference(B);
    // std::cout << "Difference: " << A->toString() << "\n";
    // Set<int>* E = Set<int>::Difference(C, B);
    // std::cout << "Difference E: " << E->toString() << "\n\n";

    // std::function<int(int)> square = [](int x) ->int {return x * x;};
    // Set<int>* Map = D->Map(square);
    // std::cout << "Map: " << Map->toString() << "\n\n";

    // std::function<bool(int)> If = [](int x) ->int {return x >= 5;};
    // Set<int>* Where = D->Where(If);
    // std::cout << "Where: " << Where->toString() << "\n\n";

    // std::function<int(int, int)> foo = [](int x1, int x2) ->int {return 2 * x1 + 3 * x2;};
    // std::cout << "Reduce: " << Map->Reduce(foo, 4) << "\n\n";

    // std::string s = "10, 20, 10, 30, 40";
    // Set<int>* fromString = Set<int>::fromString(s);
    // std::cout << "fromString: " << fromString->toString() << "\n";
    
    // delete A;
    // delete B;
    // delete C;
    // delete D;
    // delete E;
    // delete Map;
    // delete Where;
    // delete fromString;

    //Set string

    // Set<std::string>* set = new Set<std::string>();

    // for (int i = 0; i < 5; i++) {
    //     std::string s;
    //     std::cin >> s;
    //     set->Insert(s);
    //     std::cout << set->toString() << "\n";
    // }

    // for (int i = 0; i < 2; i++) {
    //     std::string s;
    //     std::cin >> s;
    //     set->Erase(s);
    //     std::cout << set->toString() << "\n";
    // }
    
    // delete set;

    //////////////////////////////////////////////////////////////////////////
    // Priority_Queue

    // PriorityQueue<int>* queue = new PriorityQueue<int>();

    // for (int i = 0; i < 5; i++) {
    //     queue->Push(i, 5 - i);
    // }
    // std::cout << "Queue: " << queue->toString() << "\n\n";

    // std::cout << "Iterator++: ";
    // for (auto it = queue->begin(); it != queue->end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << "\n\n";

    // std::cout << "Iterator--: ";
    // for (auto it = --queue->end(); it != queue->begin(); --it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << *queue->begin() << "\n\n";

    // PriorityQueue<int>* sub = queue->GetSubQueue(1, 4);
    // std::cout << "Sub: " << sub->toString() << "\n\n";

    // PriorityQueue<int>* con = queue->Concat(queue);
    // std::cout << "Con: " << con->toString() << "\n\n";

    // con->Clutch(queue);
    // std::cout << "Clutch: "<< con->toString() << "\n\n";

    // std::function<int(int)> square = [](int x) ->int {return x * x;};
    // PriorityQueue<int>* Map = queue->Map(square);
    // std::cout << "Map: " << Map->toString() << "\n\n";

    // std::function<bool(int)> If = [](int x) ->int {return x > 2;};
    // PriorityQueue<int>* Where = queue->Where(If);
    // std::cout << "Where: " << Where->toString() << "\n\n";

    // std::function<int(int, int)> foo = [](int x1, int x2) ->int {return 2 * x1 + 3 * x2;};
    // std::cout << "Reduce: " << Map->Reduce(foo, 4) << "\n\n";

    // PriorityQueue<int>* split = new PriorityQueue<int>();
    // for (int i = 0; i < 6; i++) {
    //     if (i % 2 == 0) split->Push(i + 10, i);
    //     else split->Push(i - 10, i);
    // }
    // std::tuple<PriorityQueue<int>*, PriorityQueue<int>*> other = split->Split(If);

    // PriorityQueue<int>* one = std::get<0>(other);
    // PriorityQueue<int>* two = std::get<1>(other);

    // std::cout << "Split: " << one->toString() << " " << two->toString();
    // std::cout << "\n\n";

    // std::string s = "(1, 1) (2, 2) (3, 3)";
    // PriorityQueue<int>* fromString = PriorityQueue<int>::fromString(s);
    // std::cout << "fromString: " << fromString->toString() << "\n";

    // delete queue;
    // delete sub;
    // delete con;
    // delete Map;
    // delete Where;
    // delete split;
    // delete one;
    // delete two;
    // delete fromString;

    // PriorityQueue<std::string>* queue = new PriorityQueue<std::string>();

    // for (int i = 0; i < 5; i++) {
    //     std::string x;
    //     int j;
    //     std::cin >> x >> j;
    //     queue->Push(x, j);
    //     std::cout << queue->toString() << "\n";
    // }

    // for (int i = 0; i < 5; i++) {
    //     std::cout << queue->Pop() << "\n";
    // }
    // std::cout << queue->toString() << "\n";
    // delete queue;
}