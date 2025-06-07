#ifndef TREE_HPP
#define TREE_HPP

#include <functional>

template <typename T>
class Tree {
    public:
        virtual int Size() const = 0;
        virtual void Insert(const T& k) = 0;
        virtual bool Remove(const T& k) = 0;
        virtual bool Contains(const T& k) const = 0;
        virtual void PreOrder(std::function<void(const T&)> visit) const = 0;
        virtual void ReversePreOrder(std::function<void(const T&)> visit) const = 0;
        virtual void InOrder(std::function<void(const T&)> visit) const = 0;
        virtual void ReverseInOrder(std::function<void(const T&)> visit) const = 0;
        virtual void PostOrder(std::function<void(const T&)> visit) const = 0;
        virtual void ReversePostOrder(std::function<void(const T&)> visit) const = 0;
        virtual Tree<T>* GetSubTree(const T& k) const = 0;
        virtual Tree<T>* Concat(Tree<T>* other) const = 0;
        virtual Tree<T>* Clutch(Tree<T>* other) = 0;
        virtual void Clear() = 0;
        virtual ~Tree() = default;
};

#endif //TREE_HPP