#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include "../../auxiliary/Stack.hpp"
#include "../../auxiliary/Iterator.hpp"

template <typename T>
class PriorityQueue;

template <typename T>
struct PQ_Node {
    PQ_Node(T value, int k, PQ_Node<T>* p = nullptr) : value(value), key(k), height(1), left(nullptr), right(nullptr), parent(p) {}
    T value;
    int key;
    unsigned char height;
    PQ_Node<T>* left;
    PQ_Node<T>* right;
    PQ_Node<T>* parent;
};

template <typename T, bool IsConst>
class PQIterator : public IIterator<T, IsConst> {
    public:
        using value_type = typename IIterator<T, IsConst>::value_type;
        using pointer = std::conditional_t<IsConst, const T*, T*>;
        using reference = typename IIterator<T, IsConst>::reference;
        using difference_type = typename IIterator<T, IsConst>::difference_type;
        using iterator_category = std::bidirectional_iterator_tag;

        using PQ_Ptr = std::conditional_t<IsConst, const PriorityQueue<T>*, PriorityQueue<T>*>;

        PQIterator(PQ_Node<T>* node, PQ_Ptr t) : current(node), queue(t) {}

        bool HasNext() const override {
            if (!current) return false;
            if (current->right) return true;
            PQ_Node<T>* node = current;
            while (node->parent && node == node->parent->right) {
                node = node->parent;
            }
            return node->parent != nullptr;
        }

        bool HasPrev() const {
            if (!current) return false;
            if (current->left) return true;
            PQ_Node<T>* node = current;
            while (node->parent && node == node->parent->left) {
                node = node->parent;
            }
            return node->parent != nullptr;
        }

        reference Current() override {
            return operator*();
        }

        void MoveNext() override {
            operator++();
        }

        void MovePrev() {
            operator--();
        }

        PQIterator& operator++() {
            toNext();
            return *this;
        }

        PQIterator operator++(int) {
            PQIterator tmp = *this;
            toNext();
            return tmp;
        }

        PQIterator& operator--() {
            toPrev();
            return *this;
        }

        PQIterator operator--(int) {
            PQIterator tmp = *this;
            toPrev();
            return tmp;
        }

        reference operator*() const {
            if (!current) throw std::out_of_range("Iterator out of range");
            return current->value;
        }

        pointer operator->() const {
            return &(operator*());
        }

        bool operator==(const PQIterator& other) const {
            return current == other.current;
        }

        bool operator!=(const PQIterator& other) const {
            return !(*this == other);
        }

    private:
        PQ_Node<T>* current;
        PQ_Ptr queue;

        void toNext() {
            if (!current) {
                throw std::out_of_range("Iterator out of range");
            }
            if (current == queue->FindMax(queue->root)) {
                current = nullptr;
                return;
            }
            if (current->right) {
                current = current->right;
                while (current->left) {
                    current = current->left;
                }
                return;
            }
            PQ_Node<T>* p = current->parent;
            while (p && current == p->right) {
                current = p;
                p = p->parent;
            }
            current = p;
        }

        void toPrev() {
             if (!current) {
                if (!queue || !queue->root) {
                    throw std::out_of_range("Iterator out of range");
                }
                current = queue->root;
                while (current->right) {
                    current = current->right;
                }
                return;
            }
            if (current == queue->FindMin(queue->root)) {
                current = nullptr;
                return;
            }
            if (current->left) {
                current = current->left;
                while (current->right) {
                    current = current->right;
                }
                return;
            }
            PQ_Node<T>* p = current->parent;
            while (p && current == p->left) {
                current = p;
                p = p->parent;
            }
            current = p;
        }
};

template <typename T>
class PriorityQueue : public IEnumerable<T> {
    public:
        using value_type = T;
        using iterator = PQIterator<T, false>;
        using const_iterator = PQIterator<T, true>;

        iterator begin() { 
            return iterator(FindMin(root), this);
        }
        iterator end() {
            return iterator(nullptr, this);
        }
        const_iterator begin() const {
            return const_iterator(FindMin(root), this);
        }
        const_iterator end() const {
            return const_iterator(nullptr, this);
        }
        const_iterator cbegin() const {
            return const_iterator(FindMin(root), this);
        }
        const_iterator cend() const {
            return const_iterator(nullptr, this);
        }

        std::unique_ptr<IIterator<T, false>> GetIterator() override {
            return std::make_unique<iterator>(begin());
        }
        std::unique_ptr<IIterator<T, true>> GetConstIterator() const override {
            return std::make_unique<const_iterator>(cbegin());
        }

        PriorityQueue() : root(nullptr), size(0) {}
        PriorityQueue(const PriorityQueue<T>& other) : root(nullptr), size(0) {
            if (other.size < 0) throw std::invalid_argument("Size cannot be negative");
            Stack<PQ_Node<T>*> stack;
            if (other.root) stack.Push(other.root);
            while (!stack.IsEmpty()) {
                PQ_Node<T>* current = stack.Top();
                stack.Pop();
                this->Push(current->value, current->key);
                if (current->right) stack.Push(current->right);
                if (current->left) stack.Push(current->left);
            }
        } 

        int Size() {
            return size;
        }

        void Push(const T& value, int key) {
            Insert(value, key);
        }

        T Pop() {
            if (IsEmpty()) throw std::out_of_range("PriorityQueue is empty");
            PQ_Node<T>* p = root;
            while (p->right) {
                p = p->right;
            }
            T result = p->value;
            Remove(p->key);
            return result;
        }

        const T& Top() const {
            if (IsEmpty()) throw std::out_of_range("PriorityQueue is empty");
            PQ_Node<T>* p = root;
            while (p->right) {
                p = p->right;
            }
            return p->value;
        }

        bool IsEmpty() const {
            return size == 0;
        }

        PriorityQueue<T>* GetSubQueue(int startIndex, int endIndex) const {
            if (startIndex < 0 || startIndex >= size || endIndex > size || startIndex > endIndex) throw std::out_of_range("Index out of range");
            PriorityQueue<T>* result = new PriorityQueue<T>();
            int i = 0;
            InOrder([result, &i, &startIndex, &endIndex](const T& value, int k) {
                if (i >= startIndex && i < endIndex) result->Push(value, k);
                i++;
            });
            return result;
        }

        PriorityQueue<T>* Concat(PriorityQueue<T>* other) const {
            PriorityQueue<T>* result = new PriorityQueue<T>(*this);
            if (other->size <= 0 || !other->root) return result;
            Stack<PQ_Node<T>*> stack;
            if (other->root) stack.Push(other->root);
            while (!stack.IsEmpty()) {
                PQ_Node<T>* current = stack.Top();
                stack.Pop();
                result->Push(current->value, current->key);
                if (current->right) stack.Push(current->right);
                if (current->left) stack.Push(current->left);
            }
            return result;
        }

        PriorityQueue<T>* Clutch(PriorityQueue<T>* other) {
            if (other->size <= 0 || !other->root) return this;
            Stack<PQ_Node<T>*> stack;
            if (other->root) stack.Push(other->root);
            while (!stack.IsEmpty()) {
                PQ_Node<T>* current = stack.Top();
                stack.Pop();
                this->Push(current->value, current->key);
                if (current->right) stack.Push(current->right);
                if (current->left) stack.Push(current->left);
            }
            return this;
        }

        template <typename U>
        PriorityQueue<U>* Map(std::function<U(T)> f) const {
            PriorityQueue<U>* result = new PriorityQueue<U>();
            InOrder([result, f](const T& value, int k) {
                result->Push(f(value), k);
            });
            return result;
        }

        PriorityQueue<T>* Where(std::function<bool(T)> f) const {
            PriorityQueue<T>* result = new PriorityQueue<T>();
            InOrder([result, f](const T& value, int k) {
                if (f(value)) result->Push(value, k);
            });
            return result;
        }

        T Reduce(std::function<T(T, T)> f, const T& c) const {
            T answer = 0;
            int i = 1;
            InOrder([&answer, &i, f, &c](const T& value, int k) {
                if (i) {
                    answer = f(value, c);
                    i = 0;
                }
                answer = f(value, answer);
            });
            return answer;
        }

        std::tuple<PriorityQueue<T>*, PriorityQueue<T>*> Split(std::function<bool(const T&)> f) const {
            PriorityQueue<T>* first = new PriorityQueue<T>();
            PriorityQueue<T>* second = new PriorityQueue<T>();
            InOrder([first, second, f](const T& value, int key) {
                if (f(value)) {
                    first->Push(value, key);
                } else {
                    second->Push(value, key);
                }
            }); 
            return std::make_tuple(first, second);
        }

        static PriorityQueue<T>* fromString(const std::string& data) {
            PriorityQueue<T>* result = new PriorityQueue<T>();
            std::istringstream iss(data);
            char c;
            T value;
            int k;
            while (iss >> c && c == '(') {
                iss >> value >> c;
                if (c != ',') {
                    delete result;
                    throw std::invalid_argument("Invalid format");
                }
                iss >> k >> c;
                if (c != ')') {
                    delete result;
                    throw std::invalid_argument("Invalid format");
                }
                result->Push(value, k);
            }    
            return result;
        }

        std::string toString() const {
            std::ostringstream oss;
            oss << "[";
            bool first = true;
            InOrder([&oss, &first](const T& value, int key) { 
                if(!first) oss << ", ";
                oss << "(" << value << ", " << key << ")"; 
                first = false;
            });
            oss << "]";
            return oss.str();
        }

        void Clear() {
            if (!root) return;
            Stack<PQ_Node<T>*> stack;
            stack.Push(root);
            while (!stack.IsEmpty()) {
                PQ_Node<T>* current = stack.Top();
                stack.Pop();
                if (current->left) stack.Push(current->left);
                if (current->right) stack.Push(current->right);
                delete current;
            }
            root = nullptr;
            size = 0;
        }

        ~PriorityQueue() { 
            Clear();
        }

    private:
        PQ_Node<T>* root;
        int size;

        template <typename U, bool IsConst>
        friend class PQIterator;

        void UpdateParent(PQ_Node<T>* node, PQ_Node<T>* newParent) {
            if (node == root) node->parent = nullptr;
            if (node) {
                node->parent = newParent;
            }
        }

        void Insert(const T& value, int k) {
            if (!root) {
                root = new PQ_Node<T>(value, k, nullptr);
                size++;
                return;
            }
            Stack<PQ_Node<T>**> path;
            PQ_Node<T>** current = &root;
            PQ_Node<T>* parent = nullptr;
            while (*current) {
                path.Push(current);
                parent = *current;
                if (k < (*current)->key) current = &(*current)->left;
                else current = &(*current)->right;
            }
            *current = new PQ_Node<T>(value, k, parent);
            while (!path.IsEmpty()) {
                PQ_Node<T>** p = path.Top();
                path.Pop();
                *p = Balance(*p);
            }
            size++;
            root = Balance(root);
        }

        bool Remove(const T& value, int k) {
            if (!root) return false;
            Stack<PQ_Node<T>**> path;
            PQ_Node<T>** current = &root;
            PQ_Node<T>* parent = nullptr;
            while (*current && (*current)->key != k) {
                path.Push(current);
                parent = *current;
                if (k < (*current)->key) current = &(*current)->left;
                else current = &(*current)->right;
            }
            if (!*current) return false;
            PQ_Node<T>* toDelete = *current;
            PQ_Node<T>* leftChild = toDelete->left;
            PQ_Node<T>* rightChild = toDelete->right;
            
            if (!rightChild) {
                *current = leftChild;
                if (leftChild) {
                    leftChild->parent = parent;
                }
            } else {
                PQ_Node<T>* min = FindMin(rightChild);
                min->right = RemoveMin(rightChild);
                min->left = leftChild;
                
                if (min->right) min->right->parent = min;
                if (min->left) min->left->parent = min;
                
                *current = Balance(min);
                (*current)->parent = parent;
            }
            
            delete toDelete;
            
            while (!path.IsEmpty()) {
                PQ_Node<T>** p = path.Top();
                path.Pop();
                *p = Balance(*p);
            }
            
            if (*current != root) {
                root = Balance(root);
            }
            
            size--;
            return true;
        }

        void InOrder(std::function<void(const T&, int)> visit) const { // ЛКП
            Stack<PQ_Node<T>*> stack;
            PQ_Node<T>* current = root;

            while (current || !stack.IsEmpty()) {
                while (current) {
                    stack.Push(current);
                    current = current->left;
                }
                current = stack.Top();
                stack.Pop();
                visit(current->value, current->key);
                current = current->right;
            }
        }

        unsigned char Height(PQ_Node<T>* p) {
            return p ? p->height : 0;
        }

        int BFactor(PQ_Node<T>* p) {
            return Height(p->right) - Height(p->left);
        }

        void FixHeight(PQ_Node<T>* p) {
            unsigned char hl = Height(p->left);
            unsigned char hr = Height(p->right);
            p->height = (hl > hr ? hl : hr) + 1;
        }

        PQ_Node<T>* RotateRight(PQ_Node<T>* p) {
            PQ_Node<T>* q = p->left;
            p->left = q->right;
            UpdateParent(q->right, p);
            q->right = p;
            UpdateParent(q, p->parent);
            UpdateParent(p, q);
            FixHeight(p);
            FixHeight(q);
            return q;
        }

        PQ_Node<T>* RotateLeft(PQ_Node<T>* q) {
            PQ_Node<T>* p = q->right;
            q->right = p->left;
            UpdateParent(p->left, q);
            p->left = q;
            UpdateParent(p, q->parent);
            UpdateParent(q, p);
            FixHeight(q);
            FixHeight(p);
            return p;
        }

        PQ_Node<T>* Balance(PQ_Node<T>* p) {
            FixHeight(p);
            if (BFactor(p) == 2) {
                if (BFactor(p->right) < 0) p->right = RotateRight(p->right);
                return RotateLeft(p);
            }
            if (BFactor(p) == -2) {
                if (BFactor(p->left) > 0) p->left = RotateLeft(p->left);
                return RotateRight(p);
            }
            return p;
        }

        PQ_Node<T>* RemoveMin(PQ_Node<T>* p) {
            if (!p->left) {
                if (p->right) {
                    p->right->parent = p->parent;
                }
                return p->right;
            }
            Stack<PQ_Node<T>**> path;
            PQ_Node<T>** current = &p;
            PQ_Node<T>* parent = p->parent;
            while ((*current)->left) {
                path.Push(current);
                parent = *current;
                current = &(*current)->left;
            }
            *current = (*current)->right;
            if (*current) {
                (*current)->parent = parent;
            }
            while (!path.IsEmpty()) {
                PQ_Node<T>** q = path.Top();
                path.Pop();
                *q = Balance(*q);
            }
            return Balance(p);
        }

        PQ_Node<T>* FindMin(PQ_Node<T>* p) const {
            if (!p) return nullptr;
            while (p->left) {
                p = p->left;
            }
            return p;
        }

        PQ_Node<T>* FindMax(PQ_Node<T>* p) const {
            if (!p) return nullptr;
            while (p->right) {
                p = p->right;
            }
            return p;
        }
};

#endif // PRIORITYQUEUE_HPP