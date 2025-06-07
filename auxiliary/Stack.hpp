#ifndef STACK_HPP
#define STACK_HPP

#include "include/List/ListSequence.hpp"

template <typename T>
class Stack : public ListSequence<T> {
    public:
        Stack(const T* items, int size) : ListSequence<T>(items, size) {}
        Stack() : Stack(nullptr, 0) {}
        Stack(int size) : Stack(nullptr, size) {}
        Stack(const Stack<T>& other) : ListSequence<T>(other) {}
        Stack(const LinkedList<T>& other) : ListSequence<T>(other) {}

        Stack<T>& operator=(const Stack<T>& other) {
            if (this == &other) return *this;
            delete this->list;
            this->list = new LinkedList<T>(*other.list);
            return *this;
        }

        int GetSize() const override {
            return this->list->GetSize();
        }

        T Get(int index) const override {
            return this->list->Get(index);
        }

        T Top() const {
            if (IsEmpty()) throw std::out_of_range("Stack is empty");
            return this->GetLast();
        }
        
        void Push(const T& value) {
            this->AppendInternal(value);
        }
        void Push(T&& value) {
            this->AppendInternal(std::move(value));
        }

        void Pop() {
            if (IsEmpty()) throw std::out_of_range("Stack is empty");
            this->RemoveAtInternal(this->GetSize() - 1);
        }

        bool IsEmpty() const {
            return this->GetSize() == 0;
        }

        Stack<T>* GetSubSequence(int startIndex, int endIndex) const {
            LinkedList<T>* temp_list = this->list->GetSubContainer(startIndex, endIndex);
            Stack<T>* result = new Stack<T>(*temp_list);
            delete temp_list;
            return result;
        }

        int FindSubSequence(Stack<T>* sub) const {
            if (sub->IsEmpty()) return 0;
            if (this->GetSize() < sub->GetSize()) return -1;
            int i = 0, j = 0;
            while (this->operator[](i) != (*sub)[0] && i < this->GetSize()) {
                i++;
            }
            if (i == this->GetSize()) return -1;
            int index = i;
            while (j < sub->GetSize()) {
                if (i == this->GetSize() || this->operator[](i) != (*sub)[j]) return -1;
                i++;
                j++;
            }
            return index;
        }

        Stack<T>* Concat(Stack<T>* other) const {
            if (!other) return new Stack<T>(*this);
            LinkedList<T>* temp_list = this->list->Concat(other->list);
            Stack<T>* result = new Stack<T>(*temp_list);
            delete temp_list;
            return result;
        }

        Stack<T>* Clutch(Stack<T>* other) {
            if (!other) return this;
            this->list->Clutch(other->list);
            return this;
        }

        template <typename Container>
        Stack<T>* From(const Container& container) {
            this->list->From(container);
            return this;
        }

        template <typename U>
        Stack<U>* Map(std::function<U(T)> f) const {
            LinkedList<U>* temp_list = this->list->Map(f);
            Stack<U>* result = new Stack<U>(*temp_list);
            delete temp_list;
            return result;
        }

        template <typename U>
        Stack<T>* FlatMap(std::function<LinkedList<T>*(U)> f) const {
            LinkedList<T>* temp_list = this->list->FlatMap(f);
            Stack<T>* result = new Stack<T>(*temp_list);
            delete temp_list;
            return result;
        }

        Stack<T>* Where(std::function<bool(T)> f) const {
            LinkedList<T>* temp_list = this->list->Where(f);
            Stack<T>* result = new Stack<T>(*temp_list);
            delete temp_list;
            return result;
        }

        T Reduce(std::function<T(T, T)> f, const T& c) const {
            return this->list->Reduce(f, c);
        }

        template <typename... Stacks>
        Stack<std::tuple<T, typename Stacks::value_type...>>* Zip(const Stack<T>* first, const Stacks*... stacks) const {
            Stack<std::tuple<T, typename Stacks::value_type...>>* result = new Stack<std::tuple<T, typename Stacks::value_type...>>(*(this->list->Zip(first->list, (stacks->list)...)));
            return result;
        }

        template <typename... Tuples>
        std::tuple<Stack<Tuples>...>* UnZip() const {
            std::tuple<Stack<Tuples>...>* result = new std::tuple<Stack<Tuples>...>();
            for (auto it = this->begin(); it != this->end(); ++it) {
                auto unzip = [&]<size_t... Is>(std::index_sequence<Is...>) {
                    ((std::get<Is>(*result).Push(std::get<Is>(*it))), ...);
                };
                unzip(std::index_sequence_for<Tuples...>{});
            }
            return result;
        }

        std::string toString() const {
            return this->list->toString();
        }

        virtual ~Stack() {
            delete this->list;
        }

    private:
        Stack<T>* Instance() override {
            return this;
        }
};

#endif // STACK_HPP