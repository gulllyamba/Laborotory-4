#ifndef AVL_HPP
#define AVL_HPP

#include "../../auxiliary/Stack.hpp"
#include "../../auxiliary/Iterator.hpp"
#include "Tree.hpp"

enum class BypassType {
    PreOrder,
    ReversePreOrder,
    InOrder,
    ReverseInOrder,
    PostOrder,
    ReversePostOrder
};

template <typename T>
class AVL_Tree;

template <typename T>
class Node {
    public:
        Node(T k, Node<T>* p = nullptr) : key(k), height(1), left(nullptr), right(nullptr), parent(p) {}
        T key;
        unsigned char height;
        Node<T>* left;
        Node<T>* right;
        Node<T>* parent;
};

template <typename T, bool IsConst>
class TreeIterator : public IIterator<T, IsConst> {
    public:
        using value_type = typename IIterator<T, IsConst>::value_type;
        using pointer = std::conditional_t<IsConst, const T*, T*>;
        using reference = typename IIterator<T, IsConst>::reference;
        using difference_type = typename IIterator<T, IsConst>::difference_type;
        using iterator_category = std::bidirectional_iterator_tag;

        using TreePtr = std::conditional_t<IsConst, const AVL_Tree<T>*, AVL_Tree<T>*>;

        TreeIterator(Node<T>* node, TreePtr t) : current(node), tree(t) {}

        bool HasNext() const override {
            if (!current) return false;
            if (current->right) return true;
            Node<T>* node = current;
            while (node->parent && node == node->parent->right) {
                node = node->parent;
            }
            return node->parent != nullptr;
        }

        bool HasPrev() const {
            if (!current) return false;
            if (current->left) return true;
            Node<T>* node = current;
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

        TreeIterator& operator++() {
            toNext();
            return *this;
        }

        TreeIterator operator++(int) {
            TreeIterator tmp = *this;
            toNext();
            return tmp;
        }

        TreeIterator& operator--() {
            toPrev();
            return *this;
        }

        TreeIterator operator--(int) {
            TreeIterator tmp = *this;
            toPrev();
            return tmp;
        }

        reference operator*() const {
            if (!current) throw std::out_of_range("Iterator out of range");
            return current->key;
        }

        pointer operator->() const {
            return &(operator*());
        }

        bool operator==(const TreeIterator& other) const {
            return current == other.current;
        }

        bool operator!=(const TreeIterator& other) const {
            return !(*this == other);
        }

    private:
        Node<T>* current;
        TreePtr tree;

        void toNext() {
            if (!current) {
                throw std::out_of_range("Iterator out of range");
            }
            if (current == tree->FindMax(tree->root)) {
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
            Node<T>* p = current->parent;
            while (p && current == p->right) {
                current = p;
                p = p->parent;
            }
            current = p;
        }

        void toPrev() {
             if (!current) {
                if (!tree || !tree->root) {
                    throw std::out_of_range("Iterator out of range");
                }
                current = tree->root;
                while (current->right) {
                    current = current->right;
                }
                return;
            }
            if (current == tree->FindMin(tree->root)) {
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
            Node<T>* p = current->parent;
            while (p && current == p->left) {
                current = p;
                p = p->parent;
            }
            current = p;
        }
};

template <typename T>
class AVL_Tree : public Tree<T>, public IEnumerable<T> {
    public:
        using value_type = T;
        using iterator = TreeIterator<T, false>;
        using const_iterator = TreeIterator<T, true>;

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

        AVL_Tree() : root(nullptr), size(0) {}
        AVL_Tree(const AVL_Tree<T>& other) : root(nullptr), size(0) {
            if (other.size < 0) throw std::invalid_argument("Size cannot be negative");
            Stack<Node<T>*> stack;
            if (other.root) stack.Push(other.root);
            while (!stack.IsEmpty()) {
                Node<T>* current = stack.Top();
                stack.Pop();
                this->Insert(current->key);
                if (current->right) stack.Push(current->right);
                if (current->left) stack.Push(current->left);
            }
        } 

        int Size() const override {
            return size;
        }

        T GetMin() const {
            Node<T>* p = root;
            if (!root) throw std::out_of_range("Tree is empty");
            while (p->left) {
                p = p->left;
            }
            return p->key;
        }

        T GetMax() const {
            Node<T>* p = root;
            if (!root) throw std::out_of_range("Tree is empty");
            while (p->right) {
                p = p->right;
            }
            return p->key;
        }

        bool IsEmpty() const {
            return size == 0;
        }

        void Insert(const T& k) override {
            if (!root) {
                root = new Node<T>(k, nullptr);
                size++;
                return;
            }
            Stack<Node<T>**> path;
            Node<T>** current = &root;
            Node<T>* parent = nullptr;
            while (*current) {
                path.Push(current);
                parent = *current;
                if (k < (*current)->key) current = &(*current)->left;
                else current = &(*current)->right;
            }
            *current = new Node<T>(k, parent);
            while (!path.IsEmpty()) {
                Node<T>** p = path.Top();
                path.Pop();
                *p = Balance(*p);
            }
            size++;
            root = Balance(root);
        }

        bool Remove(const T& k) override {
            if (!root) return false;
            Stack<Node<T>**> path;
            Node<T>** current = &root;
            Node<T>* parent = nullptr;
            while (*current && (*current)->key != k) {
                path.Push(current);
                parent = *current;
                if (k < (*current)->key) current = &(*current)->left;
                else current = &(*current)->right;
            }
            if (!*current) return false;
            Node<T>* toDelete = *current;
            Node<T>* leftChild = toDelete->left;
            Node<T>* rightChild = toDelete->right;
            
            if (!rightChild) {
                *current = leftChild;
                if (leftChild) {
                    leftChild->parent = parent;
                }
            } else {
                Node<T>* min = FindMin(rightChild);
                min->right = RemoveMin(rightChild);
                min->left = leftChild;
                
                if (min->right) min->right->parent = min;
                if (min->left) min->left->parent = min;
                
                *current = Balance(min);
                (*current)->parent = parent;
            }
            
            delete toDelete;
            
            while (!path.IsEmpty()) {
                Node<T>** p = path.Top();
                path.Pop();
                *p = Balance(*p);
            }
            
            if (*current != root) {
                root = Balance(root);
            }
            
            size--;
            return true;
        }

        bool Contains(const T& k) const override {
            Node<T>* current = root;
            while (current) {
                if (k == current->key) return true;
                else if (k < current->key) current = current->left;
                else current = current->right;
            }
            return false;
        }

        // Обходы
        void PreOrder(std::function<void(const T&)> visit) const override { // КЛП
            Stack<Node<T>*> stack;
            if (root) stack.Push(root);

            while (!stack.IsEmpty()) {
                Node<T>* current = stack.Top();
                stack.Pop();
                visit(current->key);
                if (current->right) stack.Push(current->right);
                if (current->left) stack.Push(current->left);
            }
        }

        void ReversePreOrder(std::function<void(const T&)> visit) const override { // КПЛ
            Stack<Node<T>*> stack;
            if (root) stack.Push(root);

            while (!stack.IsEmpty()) {
                Node<T>* current = stack.Top();
                stack.Pop();
                visit(current->key);
                if (current->left) stack.Push(current->left);
                if (current->right) stack.Push(current->right);
            }
        }

        void InOrder(std::function<void(const T&)> visit) const override { // ЛКП
            Stack<Node<T>*> stack;
            Node<T>* current = root;

            while (current || !stack.IsEmpty()) {
                while (current) {
                    stack.Push(current);
                    current = current->left;
                }
                current = stack.Top();
                stack.Pop();
                visit(current->key);
                current = current->right;
            }
        }

        void ReverseInOrder(std::function<void(const T&)> visit) const override { // ПКЛ
            Stack<Node<T>*> stack;
            Node<T>* current = root;

            while (current || !stack.IsEmpty()) {
                while (current) {
                    stack.Push(current);
                    current = current->right;
                }
                current = stack.Top();
                stack.Pop();
                visit(current->key);
                current = current->left;
            }
        }

        void PostOrder(std::function<void(const T&)> visit) const override { // ЛПК
            Stack<Node<T>*> stack;
            Node<T>* current = root;
            Node<T>* lastVisited = nullptr;

            while (current || !stack.IsEmpty()) {
                if (current) {
                    stack.Push(current);
                    current = current->left;
                } else {
                    Node<T>* peek = stack.Top();
                    if (peek->right && lastVisited != peek->right) {
                        current = peek->right;
                    } else {
                        visit(peek->key);
                        lastVisited = peek;
                        stack.Pop();
                    }
                }
            }
        }

        void ReversePostOrder(std::function<void(const T&)> visit) const override { // ПЛК
            Stack<Node<T>*> stack;
            Node<T>* current = root;
            Node<T>* lastVisited = nullptr;

            while (current || !stack.IsEmpty()) {
                if (current) {
                    stack.Push(current);
                    current = current->right;
                } else {
                    Node<T>* peek = stack.Top();
                    if (peek->left && lastVisited != peek->left) {
                        current = peek->left;
                    } else {
                        visit(peek->key);
                        lastVisited = peek;
                        stack.Pop();
                    }
                }
            }
        }

        AVL_Tree<T>* GetSubTree(const T& k) const override {
            AVL_Tree<T>* result = new AVL_Tree<T>();
            Node<T>* Actual_Node = root;
            while (Actual_Node) {
                if (k == Actual_Node->key) break;
                else if (k < Actual_Node->key) Actual_Node = Actual_Node->left;
                else Actual_Node = Actual_Node->right;
            }
            if (!Actual_Node) return result;
            Stack<Node<T>*> stack;
            stack.Push(Actual_Node);
            while (!stack.IsEmpty()) {
                Node<T>* current = stack.Top();
                stack.Pop();
                result->Insert(current->key);
                if (current->right) stack.Push(current->right);
                if (current->left) stack.Push(current->left);
            }
            return result;
        }

        AVL_Tree<T>* Concat(Tree<T>* other) const override {
            AVL_Tree<T>* result = new AVL_Tree<T>(*this);
            if (dynamic_cast<AVL_Tree<T>*>(other)->size <= 0 || !dynamic_cast<AVL_Tree<T>*>(other)->root) return result;
            Stack<Node<T>*> stack;
            if (dynamic_cast<AVL_Tree<T>*>(other)->root) stack.Push(dynamic_cast<AVL_Tree<T>*>(other)->root);
            while (!stack.IsEmpty()) {
                Node<T>* current = stack.Top();
                stack.Pop();
                result->Insert(current->key);
                if (current->right) stack.Push(current->right);
                if (current->left) stack.Push(current->left);
            }
            return result;
        }

        AVL_Tree<T>* Clutch(Tree<T>* other) override {
            if (dynamic_cast<AVL_Tree<T>*>(other)->size <= 0 || !dynamic_cast<AVL_Tree<T>*>(other)->root) return this;
            Stack<Node<T>*> stack;
            if (dynamic_cast<AVL_Tree<T>*>(other)->root) stack.Push(dynamic_cast<AVL_Tree<T>*>(other)->root);
            while (!stack.IsEmpty()) {
                Node<T>* current = stack.Top();
                stack.Pop();
                this->Insert(current->key);
                if (current->right) stack.Push(current->right);
                if (current->left) stack.Push(current->left);
            }
            return this;
        }

        template <typename U>
        AVL_Tree<U>* Map(std::function<U(T)> f) const {
            AVL_Tree<U>* result = new AVL_Tree<U>();
            if (!root || size <= 0) return result;

            Stack<Node<T>*> stack;
            if (root) stack.Push(root);

            while (!stack.IsEmpty()) {
                Node<T>* current = stack.Top();
                stack.Pop();
                result->Insert(f(current->key));
                if (current->right) stack.Push(current->right);
                if (current->left) stack.Push(current->left);
            }
            return result;
        }

        AVL_Tree<T>* Where(std::function<bool(T)> f) const {
            AVL_Tree<T>* result = new AVL_Tree<T>();
            if (!root || size <= 0) return result;
            
            Stack<Node<T>*> stack;
            if (root) stack.Push(root);

            while (!stack.IsEmpty()) {
                Node<T>* current = stack.Top();
                stack.Pop();
                if (f(current->key)) result->Insert(current->key);
                if (current->right) stack.Push(current->right);
                if (current->left) stack.Push(current->left);
            }
            return result;
        }

        static AVL_Tree<T>* fromString(const std::string& data) {
            AVL_Tree<T>* result = new AVL_Tree<T>();
            std::istringstream iss(data);
            char c;
            T value;
            if (iss >> value) {
                result->Insert(value);
                while (iss >> c >> value) {
                    if (c != ',') break;
                    result->Insert(value);
                }
            }
            return result;
        }

        std::string toString(BypassType order = BypassType::InOrder) const {
            std::ostringstream oss;
            switch (order) {
                case BypassType::PreOrder : {
                    PreOrder([&oss](const T& value) {oss << value << " ";});
                    break;
                }
                case BypassType::ReversePreOrder : {
                    ReversePreOrder([&oss](const T& value) {oss << value << " ";});
                    break;
                }
                case BypassType::InOrder : {
                    InOrder([&oss](const T& value) {oss << value << " ";});
                    break;
                }
                case BypassType::ReverseInOrder : {
                    ReverseInOrder([&oss](const T& value) {oss << value << " ";});
                    break;
                }
                case BypassType::PostOrder : {
                    PostOrder([&oss](const T& value) {oss << value << " ";});
                    break;
                }
                case BypassType::ReversePostOrder : {
                    ReversePostOrder([&oss](const T& value) {oss << value << " ";});
                    break;
                }
                default:
                    throw std::invalid_argument("Unknown Bypass type");
            }
            return oss.str();
        }

        void Clear() override {
            if (!root) return;
            Stack<Node<T>*> stack;
            stack.Push(root);
            while (!stack.IsEmpty()) {
                Node<T>* current = stack.Top();
                stack.Pop();
                if (current->left) stack.Push(current->left);
                if (current->right) stack.Push(current->right);
                delete current;
            }
            root = nullptr;
            size = 0;
        }

        ~AVL_Tree() override { 
            Clear();
        }

    private:
        Node<T>* root;
        int size;

        template <typename U, bool IsConst>
        friend class TreeIterator;

        void UpdateParent(Node<T>* node, Node<T>* newParent) {
            if (node == root) node->parent = nullptr;
            if (node) {
                node->parent = newParent;
            }
        }

        unsigned char Height(Node<T>* p) {
            return p ? p->height : 0;
        }

        int BFactor(Node<T>* p) {
            return Height(p->right) - Height(p->left);
        }

        void FixHeight(Node<T>* p) {
            unsigned char hl = Height(p->left);
            unsigned char hr = Height(p->right);
            p->height = (hl > hr ? hl : hr) + 1;
        }

        Node<T>* RotateRight(Node<T>* p) {
            Node<T>* q = p->left;
            p->left = q->right;
            UpdateParent(q->right, p);
            q->right = p;
            UpdateParent(q, p->parent);
            UpdateParent(p, q);
            FixHeight(p);
            FixHeight(q);
            return q;
        }

        Node<T>* RotateLeft(Node<T>* q) {
            Node<T>* p = q->right;
            q->right = p->left;
            UpdateParent(p->left, q);
            p->left = q;
            UpdateParent(p, q->parent);
            UpdateParent(q, p);
            FixHeight(q);
            FixHeight(p);
            return p;
        }

        Node<T>* Balance(Node<T>* p) {
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

        Node<T>* RemoveMin(Node<T>* p) {
            if (!p->left) {
                if (p->right) {
                    p->right->parent = p->parent;
                }
                return p->right;
            }
            Stack<Node<T>**> path;
            Node<T>** current = &p;
            Node<T>* parent = p->parent;
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
                Node<T>** q = path.Top();
                path.Pop();
                *q = Balance(*q);
            }
            return Balance(p);
        }

        Node<T>* FindMin(Node<T>* p) const {
            if (!p) return nullptr;
            while (p->left) {
                p = p->left;
            }
            return p;
        }

        Node<T>* FindMax(Node<T>* p) const {
            if (!p) return nullptr;
            while (p->right) {
                p = p->right;
            }
            return p;
        }
};

#endif // AVL_HPP