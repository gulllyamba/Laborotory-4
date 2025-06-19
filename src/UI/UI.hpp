#ifndef UI_HPP
#define UI_HPP

#include "../tree/AVL.hpp"
#include "../collections/PriorityQueue.hpp"
#include "../collections/Set.hpp"
#include <cmath>
#include <iomanip>

int container_num, method;

AVL_Tree<int>* tree;
Set<int>* set;
PriorityQueue<int>* queue;

void run_container() {
    std::cout << "\nВыберите тип структуры данных:\n";
    std::cout << "1. AVL_Tree\n";
    std::cout << "2. Set\n";
    std::cout << "3. PriorityQueue\n";
    std::cout << "0. Выйти\n";
    std::cout << "Введите выбор: ";
    std::cin >>container_num;
    while (container_num < 0 || container_num > 3) {
        std::cout << "\nОшибка. Введите число от 0 до 3: ";
        std::cin >>container_num;
    }
    switch (container_num) 
    {
        case 1: {
            tree = new AVL_Tree<int>();
            std::cout << "\nВы создали пустое AVL_Tree()\n";
            break;
        }
        case 2: {
            set = new Set<int>();
            std::cout << "\nВы создали пустой Set()\n";
            break;
        }
        case 3: {
            queue = new PriorityQueue<int>();
            std::cout << "\nВы создали пустую PriorityQueue()\n";
            break;
        }
        default: break;
    }
    return;
}

void run_method() {
    int index, value;
    if (container_num == 1) {
        std::cout << "\nВыберите метод:\n";
        std::cout << "1. GetMin\n";
        std::cout << "2. GetMax\n"; 
        std::cout << "3. GetSize\n";
        std::cout << "4. IsEmpty\n";
        std::cout << "5. Insert\n";
        std::cout << "6. Remove\n";
        std::cout << "7. Contains\n";
        std::cout << "8. GetSubTree\n";
        std::cout << "9. Concat\n";
        std::cout << "10. fromString\n";
        std::cout << "11. Обход КЛП\n";
        std::cout << "12. Обход КПЛ\n";
        std::cout << "13. Обход ЛКП\n";
        std::cout << "14. Обход ПКЛ\n";
        std::cout << "15. Обход ЛПК\n";
        std::cout << "16. Обход ПЛК\n";
        std::cout << "0. Выйти\n";
        std::cout << "Введите выбор: ";
        while (std::cin >> method && method) {
            while (method < 0 || method > 16) {
                std::cout << "\nОшибка. Введите число от 0 до 16: ";
                std::cin >>method;
            }
            switch (method)
            {
            case 1: {
                std::cout << "\n-----GetMin-----\n";
                std::cout << tree->GetMin() << "\n";
                break;
            }
            case 2: {
                std::cout << "\n-----GetMax------\n";
                std::cout << tree->GetMax() << "\n";
                break;
            }
            case 3: {
                std::cout << "\n-----GetSize----------\n";
                std::cout << tree->Size() << "\n";
                break;
            }
            case 4: {
                std::cout << "\n-----IsEmpty------\n";
                if (tree->IsEmpty()) std::cout << "Tree is empty\n";
                else std::cout << "Tree isn't empty\n";
                break;
            }
            case 5: {
                std::cout << "\n-----Insert-------\n";
                std::cout << "Введите значение: ";
                std::cin >> value;
                tree->Insert(value);
                break;
            }
            case 6: {
                std::cout << "\n-----Remove------\n";
                std::cout << "Введите значение: ";
                std::cin >> value;
                tree->Remove(value);
                break;
            }
            case 7: {
                std::cout << "\n-----Contains----------\n";
                std::cout << "Введите значение: ";
                std::cin >> value;
                std::cout << tree->Contains(value) << "\n";
                break;
            }
            case 8: {
                std::cout << "\n-----GetSubTree-----\n";
                std::cout << "Введите значение: ";
                std::cin >> value;
                AVL_Tree<int>* copy = new AVL_Tree<int>(*tree);
                delete tree;
                tree = copy->GetSubTree(value);
                delete copy;
                break;
            }
            case 9: {
                std::cout << "\n-----Concat(Clutch)-----\n";
                std::cout << "Введите размер последовательности: ";
                std::cin >> index;
                std::cout << "Введите последовательность <int>: ";
                AVL_Tree<int>* with = new AVL_Tree<int>();
                for (int i = 0; i < index; i++) {
                    std::cin >> value;
                    with->Insert(value);
                }
                tree->Clutch(with);
                delete with;
                break;
            }
            case 10: {
                std::cout << "\n-----fromString-----\n";
                std::cout << "Введите строку чисел <int> через пробел: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string s;
                std::getline(std::cin, s);
                delete tree;
                tree = AVL_Tree<int>::fromString(s);
                break;
            }
            case 11: {
                std::cout << "\n-----Обход КЛП-----\n";
                tree->PreOrder([](const int& value) {std::cout << value << " ";});
                std::cout << "\n";
                break;
            }
            case 12: {
                std::cout << "\n-----Обход КПЛ-----\n";
                tree->ReversePreOrder([](const int& value) {std::cout << value << " ";});
                std::cout << "\n";
                break;
            }
            case 13: {
                std::cout << "\n-----Обход ЛКП-----\n";
                tree->InOrder([](const int& value) {std::cout << value << " ";});
                std::cout << "\n";
                break;
            }
            case 14: {
                std::cout << "\n-----Обход ПКЛ-----\n";
                tree->ReverseInOrder([](const int& value) {std::cout << value << " ";});
                std::cout << "\n";
                break;
            }
            case 15: {
                std::cout << "\n-----Обход ЛПК-----\n";
                tree->PostOrder([](const int& value) {std::cout << value << " ";});
                std::cout << "\n";
                break;
            }
            case 16: {
                std::cout << "\n-----Обход ПЛК-----\n";
                tree->ReversePostOrder([](const int& value) {std::cout << value << " ";});
                std::cout << "\n";
                break;
            }
            default: {
                delete tree;
                delete set;
                delete queue;
            }
            }
            std::cout << "Ваше AVL_Tree: " << tree->toString(BypassType::InOrder) << "\n";
            std::cout << "Нажмите Enter для выхода в меню";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (method != 10) std::cin.get();
            std::cout << "\nВыберите метод:\n";
            std::cout << "1. GetMin\n";
            std::cout << "2. GetMax\n"; 
            std::cout << "3. GetSize\n";
            std::cout << "4. IsEmpty\n";
            std::cout << "5. Insert\n";
            std::cout << "6. Remove\n";
            std::cout << "7. Contains\n";
            std::cout << "8. GetSubTree\n";
            std::cout << "9. Concat\n";
            std::cout << "10. fromString\n";
            std::cout << "11. Обход КЛП\n";
            std::cout << "12. Обход КПЛ\n";
            std::cout << "13. Обход ЛКП\n";
            std::cout << "14. Обход ПКЛ\n";
            std::cout << "15. Обход ЛПК\n";
            std::cout << "16. Обход ПЛК\n";
            std::cout << "0. Выйти\n";
            std::cout << "Введите выбор: ";
        }
    }
    else if (container_num == 2) {
        std::cout << "\nВыберите метод:\n";
        std::cout << "1. GetSize\n";
        std::cout << "2. IsEmpty\n";
        std::cout << "3. Insert\n";
        std::cout << "4. Erase\n";
        std::cout << "5. Contains\n";
        std::cout << "6. Union\n";
        std::cout << "7. Intersection\n";
        std::cout << "8. Difference\n";
        std::cout << "9. fromString\n";
        std::cout << "0. Выйти\n";
        std::cout << "Введите выбор: ";
        while (std::cin >> method && method) {
            while (method < 0 || method > 9) {
                std::cout << "\nОшибка. Введите число от 0 до 9: ";
                std::cin >>method;
            }
            switch (method)
            {
            case 1: {
                std::cout << "\n-----GetSize----------\n";
                std::cout << set->Size() << "\n";
                break;
            }
            case 2: {
                std::cout << "\n-----IsEmpty------\n";
                if (set->IsEmpty()) std::cout << "Set is empty\n";
                else std::cout << "Set isn't empty\n";
                break;
            }
            case 3: {
                std::cout << "\n-----Insert-------\n";
                std::cout << "Введите значение: ";
                std::cin >> value;
                set->Insert(value);
                break;
            }
            case 4: {
                std::cout << "\n-----Erase------\n";
                std::cout << "Введите значение: ";
                std::cin >> value;
                set->Erase(value);
                break;
            }
            case 5: {
                std::cout << "\n-----Contains----------\n";
                std::cout << "Введите значение: ";
                std::cin >> value;
                std::cout << set->Contains(value) << "\n";
                break;
            }
            case 6: {
                std::cout << "\n-----Union----------\n";
                std::cout << "Введите размер множества: ";
                std::cin >> index;
                std::cout << "Введите последовательность <int>: ";
                Set<int>* with = new Set<int>();
                for (int i = 0; i < index; i++) {
                    std::cin >> value;
                    with->Insert(value);
                }
                set->Union(with);
                delete with;
                break;
            }
            case 7: {
                std::cout << "\n-----Intersection----------\n";
                std::cout << "Введите размер множества: ";
                std::cin >> index;
                std::cout << "Введите последовательность <int>: ";
                Set<int>* with = new Set<int>();
                for (int i = 0; i < index; i++) {
                    std::cin >> value;
                    with->Insert(value);
                }
                set->Intersection(with);
                delete with;
                break;
            }
            case 8: {
                std::cout << "\n-----Difference----------\n";
                std::cout << "Введите размер множества: ";
                std::cin >> index;
                std::cout << "Введите последовательность <int>: ";
                Set<int>* with = new Set<int>();
                for (int i = 0; i < index; i++) {
                    std::cin >> value;
                    with->Insert(value);
                }
                set->Difference(with);
                delete with;
                break;
            }
            case 9: {
                std::cout << "\n-----fromString-----\n";
                std::cout << "Введите строку чисел <int> через пробел: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string s;
                std::getline(std::cin, s);
                delete set;
                set = Set<int>::fromString(s);
                break;
            }
            default: {
                delete tree;
                delete set;
                delete queue;
            }
            }
            std::cout << "Ваш Set: ";
            std::cout << set->toString() << "\n";
            std::cout << "Нажмите Enter для выхода в меню";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (method != 9) std::cin.get();
            std::cout << "\nВыберите метод:\n";
            std::cout << "1. GetSize\n";
            std::cout << "2. IsEmpty\n";
            std::cout << "3. Insert\n";
            std::cout << "4. Erase\n";
            std::cout << "5. Contains\n";
            std::cout << "6. Union\n";
            std::cout << "7. Intersection\n";
            std::cout << "8. Difference\n";
            std::cout << "9. fromString\n";
            std::cout << "0. Выйти\n";
            std::cout << "Введите выбор: ";
        }
    }
    else {
        std::cout << "\nВыберите метод:\n";
        std::cout << "1. GetSize\n";
        std::cout << "2. Top\n";
        std::cout << "3. IsEmpty\n";
        std::cout << "4. Push\n";
        std::cout << "5. Pop\n";
        std::cout << "6. GetSubQueue\n";
        std::cout << "7. Concat\n";
        std::cout << "8. fromString\n";
        std::cout << "0. Выйти\n";
        std::cout << "Введите выбор: ";
        while (std::cin >> method && method) {
            while (method < 0 || method > 8) {
                std::cout << "\nОшибка. Введите число от 0 до 8: ";
                std::cin >>method;
            }
            switch (method)
            {
            case 1: {
                std::cout << "\n-----GetSize----------\n";
                std::cout << queue->Size() << "\n";
                break;
            }
            case 2: {
                std::cout << "\n-----Top--------\n";
                std::cout << queue->Top() << "\n";
                break;
            }
            case 3: {
                std::cout << "\n-----IsEmpty------\n";
                if (queue->IsEmpty()) std::cout << "Queue is empty\n";
                else std::cout << "Queue isn't empty\n";
                break;
            }
            case 4: {
                std::cout << "\n-----Push-------\n";
                std::cout << "Введите значение и приоритет: ";
                std::cin >> value >> index;
                queue->Push(value, index);
                break;
            }
            case 5: {
                std::cout << "\n-----Pop------\n";
                queue->Pop();
                break;
            }
            case 6: {
                std::cout << "\n-----GetSubQueue----------\n";
                std::cout << "Введите индексы начала и конца: ";
                int start, end;
                std::cin >> start >> end;
                PriorityQueue<int>* copy = new PriorityQueue<int>(*queue);
                delete queue;
                queue = copy->GetSubQueue(start, end);
                delete copy;
                break;
            }
            case 7: {
                std::cout << "\n-----Concat(Clutch)-----\n";
                std::cout << "Введите размер последовательности: ";
                std::cin >> index;
                std::cout << "Введите последовательность <int> с приоритетами: ";
                PriorityQueue<int>* with = new PriorityQueue<int>();
                for (int i = 0; i < index; i++) {
                    int priority;
                    std::cin >> value >> priority;
                    with->Push(value, priority);
                }
                queue->Clutch(with);
                delete with;
                break;
            }
            case 8: {
                std::cout << "\n-----fromString-----\n";
                std::cout << "Введите строку чисел <int> в формате '(value, priority)' через пробел: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string s;
                std::getline(std::cin, s);
                delete queue;
                queue = PriorityQueue<int>::fromString(s);
                break;
            }
            default: {
                delete tree;
                delete set;
                delete queue;
            }
            }
            std::cout << "Ваша PriorityQueue: ";
            std::cout << queue->toString() << "\n";
            std::cout << "Нажмите Enter для выхода в меню";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (method != 8) std::cin.get();
            std::cout << "\nВыберите метод:\n";
            std::cout << "1. GetSize\n";
            std::cout << "2. Top\n";
            std::cout << "3. IsEmpty\n";
            std::cout << "4. Push\n";
            std::cout << "5. Pop\n";
            std::cout << "6. GetSubQueue\n";
            std::cout << "7. Concat\n";
            std::cout << "8. fromString\n";
            std::cout << "0. Выйти\n";
            std::cout << "Введите выбор: ";
        }
    }
    return;
}

#endif // UI_HPP