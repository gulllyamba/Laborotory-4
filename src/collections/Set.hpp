#ifndef SET_HPP
#define SET_HPP

#include "../tree/AVL.hpp"
#include "../../auxiliary/Stack.hpp"
#include "../../auxiliary/Iterator.hpp"

template <typename T>
class Set : public IEnumerable<T> {
    public:
        using value_type = T;
        using iterator = typename AVL_Tree<T>::iterator;
        using const_iterator = typename AVL_Tree<T>::const_iterator;

        iterator begin() { 
            return tree->begin();
        }
        
        iterator end() {
            return tree->end();
        }
        
        const_iterator begin() const {
            return tree->begin();
        }
        
        const_iterator end() const {
            return tree->end();
        }
        
        const_iterator cbegin() const {
            return tree->cbegin();
        }
        
        const_iterator cend() const {
            return tree->cend();
        }

        std::unique_ptr<IIterator<T, false>> GetIterator() override {
            return tree->GetIterator();
        }
        
        std::unique_ptr<IIterator<T, true>> GetConstIterator() const override {
            return tree->GetConstIterator();
        }

        Set() : tree(new AVL_Tree<T>()) {}

        bool operator==(const Set<T>& other) const {
            if (Size() != other.Size()) return false;
            bool isEqual = true;
            tree->InOrder([&other, &isEqual](const T& value) {
                if (!other.Contains(value)) isEqual = false;
            });
            return isEqual;
        }
        bool operator!=(const Set<T>& other) const {
            return !(*this == other);
        }

        int Size() const {
            return tree->Size();
        }

        void Insert(const T& value) {
            if (!Contains(value)) tree->Insert(value);
        }

        bool Erase(const T& value) {
            return tree->Remove(value);
        }

        bool Contains(const T& value) const {
            return tree->Contains(value);
        }

        bool IsEmpty() const {
            return Size() == 0;
        }

        void Union(const Set<T>* other) {
            other->tree->PreOrder([this](const T& value) {this->Insert(value);});
        }
        static Set<T>* Union(const Set<T>* left, const Set<T>* right) {
            Set<T>* result = new Set<T>();
            left->tree->PreOrder([result](const T& value) {result->Insert(value);});
            right->tree->PreOrder([result](const T& value) {result->Insert(value);});
            return result;
        }

        void Intersection(const Set<T>* other) {
            std::vector<T> toRemove;
            tree->PreOrder([other, &toRemove](const T& value) {
                if (!other->Contains(value)) toRemove.push_back(value);
            });
            for (const T& value : toRemove) {
                tree->Remove(value);
            }
        }
        static Set<T>* Intersection(const Set<T>* left, const Set<T>* right) {
            Set<T>* result = new Set<T>();
            left->tree->PreOrder([right, result](const T& value) {
                if (right->Contains(value)) result->Insert(value);
            });
            return result;
        }

        void Difference(const Set<T>* other) {
            std::vector<T> toRemove;
            tree->PreOrder([other, &toRemove](const T& value) {
                if (other->Contains(value)) toRemove.push_back(value);
            });
            for (const T& value : toRemove) {
                tree->Remove(value);
            }
        }
        static Set<T>* Difference(const Set<T>* left, const Set<T>* right) {
            Set<T>* result = new Set<T>();
            left->tree->PreOrder([right, result](const T& value) {
                if (!right->Contains(value)) result->Insert(value);
            });
            return result;
        }

        template <typename U>
        Set<U>* Map(std::function<U(T)> f) const {
            Set<U>* result = new Set<U>();
            tree->PreOrder([result, f](const T& value) {
                result->Insert(f(value));
            });
            return result;
        }

        Set<T>* Where(std::function<bool(T)> f) const {
            Set<T>* result = new Set<T>();
            tree->PreOrder([result, f](const T& value) {
                if (f(value)) result->Insert(value);
            });
            return result;
        }

        T Reduce(std::function<T(T, T)> f, const T& c) const {
            T answer = 0;
            int i = 1;
            tree->PreOrder([&answer, &i, f, &c](const T& value) {
                if (i) {
                    answer = f(value, c);
                    i = 0;
                }
                answer = f(value, answer);
            });
            return answer;
        }

        static Set<T>* fromString(const std::string& data) {
            Set<T>* result = new Set<T>();
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

        std::string toString() const {
            std::ostringstream oss;
            oss << "[";
            bool first = true;
            tree->InOrder([&oss, &first](const T& value) { 
                if(!first) oss << ", ";
                oss << value; 
                first = false;
            });
            oss << "]";
            return oss.str();
        }

        void Clear() {
            tree->Clear();
        }

        ~Set() {
            delete tree;
        }

    private:
        AVL_Tree<T>* tree;
};

#endif // SET_HPP