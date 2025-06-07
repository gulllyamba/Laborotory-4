#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include <functional>
#include <tuple>
#include <utility>
#include <sstream>
#include <memory>
#include "../Iterator.hpp"
#include "../Container.hpp"

template <typename T>
class LinkedList;

template <typename T, bool IsConst>
class ListIterator;

template <typename T>
class TNode {
    public:
        TNode(T value) : Value(value), Next_Node(nullptr), Prev_Node(nullptr) {}
    private:
        template<typename U>
        friend class LinkedList;
        template <typename U, bool IsConst>
        friend class ListIterator;
        T Value;
        TNode<T>* Next_Node;
        TNode<T>* Prev_Node;
};

template <typename T, bool IsConst>
class ListIterator : public IIterator<T, IsConst> {
    public:
        using value_type = typename IIterator<T, IsConst>::value_type;
        using pointer = std::conditional_t<IsConst, const T*, T*>;
        using reference = typename IIterator<T, IsConst>::reference;
        using difference_type = typename IIterator<T, IsConst>::difference_type;
        using iterator_category = std::bidirectional_iterator_tag;

        ListIterator(TNode<T>* node) : current(node) {}

        bool HasNext() const override {
            return current != nullptr;
        }
        reference Current() override {
            if (!current) throw std::out_of_range("Iterator out of range");
            return current->Value;
        }
        void MoveNext() override {
            if (current) current = current->Next_Node;
        }

        reference operator*() const {
            if (!current) throw std::out_of_range("Iterator out of range");
            return current->Value;
        }

        pointer operator->() const {
            if (!current) throw std::out_of_range("Iterator out of range");
            return &(current->Value);
        }

        ListIterator& operator++() {
            if (current) current = current->Next_Node;
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator temp = *this;
            ++(*this);
            return temp;
        }

        ListIterator& operator--() {
            if (current) current = current->Prev_Node;
            return *this;
        }

        ListIterator operator--(int) {
            ListIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const ListIterator& other) const {
            return current == other.current;
        }
        bool operator!=(const ListIterator& other) const {
            return !(*this == other);
        } 

        template <bool OtherConst>
        bool operator==(const ListIterator<T, OtherConst>& other) const {
            return current == other.current;
        }
        template <bool OtherConst>
        bool operator!=(const ListIterator<T, OtherConst>& other) const {
            return !(*this == other);
        }

    private:
        friend class LinkedList<T>;
        template <typename U, bool OtherConst>
        friend class ListIterator;
        TNode<T>* current;
};

template <typename T>
using LIterator = ListIterator<T, false>;
template <typename T>
using LConstIterator = ListIterator<T, true>;

template <typename T>
class LinkedList : public Container<T>, public IEnumerable<T> {
    public:
        using value_type = T;
        using iterator = LIterator<T>;
        using const_iterator = LConstIterator<T>;

        iterator begin() { 
            return iterator(Head);
        }
        iterator end() {
            return iterator(nullptr);
        }
        const_iterator begin() const {
            return const_iterator(Head);
        }
        const_iterator end() const {
            return const_iterator(nullptr);
        }
        const_iterator cbegin() const {
            return const_iterator(Head);
        }
        const_iterator cend() const {
            return const_iterator(nullptr);
        }

        std::unique_ptr<IIterator<T, false>> GetIterator() override {
            return std::make_unique<iterator>(Head);
        }
        std::unique_ptr<IIterator<T, true>> GetConstIterator() const override {
            return std::make_unique<const_iterator>(Head);
        }

        LinkedList(const T* items, int count);
        LinkedList();
        LinkedList(int size);
        LinkedList(const LinkedList<T>& other);
        LinkedList(LinkedList<T>&& other) noexcept;

        T GetFirst() const override;
        T GetLast() const override;
        T Get(int index) const override;
        int GetSize() const override;

        void Append(const T& value) override;
        void Append(const T&& value) override;
        void Prepend(const T& value) override;
        void Prepend(const T&& value) override;
        void Set(int index, const T& value) override;
        void Set(int index, const T&& value) override;
        void InsertAt(int index, const T& value) override;
        void InsertAt(int index, const T&& value) override;
        void Resize(int size) override;
        void RemoveAt(int index) override;

        LinkedList<T>* GetSubContainer(int startIndex, int endIndex) const override;
        LinkedList<T>* Concat(Container<T>* other) const override;
        LinkedList<T>* Clutch(Container<T>* other) override;

        std::string toString() const noexcept;

        T& operator[](int index) {
            if (index < 0 || index >= Size) throw std::out_of_range("Index out of range");
            TNode<T>* Actual_Node = nullptr;
            if (index >= Size / 2) {
                Actual_Node = Last;
                for (int i = Size - 1; i > index; i--) {
                    Actual_Node = Actual_Node->Prev_Node;
                }
            }
            else {
                Actual_Node = Head;
                for (int i = 0; i < index; i++) {
                    Actual_Node = Actual_Node->Next_Node;
                }
            }
            return Actual_Node->Value;
        }
        const T& operator[](int index) const {
            if (index < 0 || index >= Size) throw std::out_of_range("Index out of range");
            TNode<T>* Actual_Node = nullptr;
            if (index >= Size / 2) {
                Actual_Node = Last;
                for (int i = Size - 1; i > index; i--) {
                    Actual_Node = Actual_Node->Prev_Node;
                }
            }
            else {
                Actual_Node = Head;
                for (int i = 0; i < index; i++) {
                    Actual_Node = Actual_Node->Next_Node;
                }
            }
            return Actual_Node->Value;
        }
        LinkedList<T>& operator=(const LinkedList<T>& other) noexcept {
            if (this == &other) return *this;
            Delete();
            if (other.Head && other.Size > 0) {
                TNode<T>* Actual_Node = other.Head;
                Head = new TNode<T>(Actual_Node->Value);
                Last = Head;
                for (int i = 1; i < other.Size; i++) {
                    Actual_Node = Actual_Node->Next_Node;
                    Last->Next_Node = new TNode<T>(Actual_Node->Value);
                    Last->Next_Node->Prev_Node = Last;
                    Last = Last->Next_Node;
                }
                Size = other.Size;
            }
            return *this;
        }
        LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
            if (this == &other) return *this;
            Delete();
            if (other.Head && other.Size > 0) {
                Head = other.Head;
                Last = other.Last;
                Size = other.Size;
                other.Head = nullptr;
                other.Last = nullptr;
                other.Size = 0;
            }
            return *this;
        }

        template <typename Container>
        LinkedList<T>* From(const Container& container);
        template <typename U>
        LinkedList<U>* Map(std::function<U(T)> f) const;
        template <typename U>
        LinkedList<T>* FlatMap(std::function<LinkedList<T>*(U)> f) const;
        LinkedList<T>* Where(std::function<bool(T)> f) const;
        T Reduce(std::function<T(T, T)> f, const T& c) const;

        template <typename... Lists>
        LinkedList<std::tuple<T, typename Lists::value_type...>>* Zip(const LinkedList<T>* first, const Lists*... lists) const;
        template <typename... Tuples>
        std::tuple<LinkedList<Tuples>...>* UnZip() const;

        void Delete() noexcept;

        ~LinkedList() noexcept;

    private:
        TNode<T>* Head = nullptr;
        TNode<T>* Last = nullptr;
        int Size = 0;

        template <typename U>
        friend class LinkedList;
};

template <typename T>
LinkedList<T>::LinkedList(const T* items, int count) {
    if (count < 0) throw std::invalid_argument("Size cannot be negative");
    else if (count == 0) {
        Head = nullptr;
        Last = nullptr;
        Size = 0;
        return;
    }
    else if (items) {
        Size = count;
        Head = new TNode<T>(items[0]);
        Last = Head;
        for (int i = 1; i < Size; i++) {
            Last->Next_Node = new TNode<T>(items[i]);
            Last->Next_Node->Prev_Node = Last;
            Last = Last->Next_Node;
        }
    }
    else {
        Size = count;
        Head = new TNode<T>(T{});
        Last = Head;
        for (int i = 1; i < Size; i++) {
            Last->Next_Node = new TNode<T>(T{});
            Last->Next_Node->Prev_Node = Last;
            Last = Last->Next_Node;
        }
    }
}

template <typename T>
LinkedList<T>::LinkedList() : LinkedList(nullptr, 0) {}

template <typename T>
LinkedList<T>::LinkedList(int size) : LinkedList(nullptr, size) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : Head(nullptr), Last(nullptr), Size(0) {
    if (other.Head) {
        Size = other.Size;
        TNode<T>* Actual_Node = other.Head;
        Head = new TNode<T>(Actual_Node->Value);
        Last = Head;
        for (int i = 1; i < Size; i++) {
            Actual_Node = Actual_Node->Next_Node;
            Last->Next_Node = new TNode<T>(Actual_Node->Value);
            Last->Next_Node->Prev_Node = Last;
            Last = Last->Next_Node;
        }
    }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept : Head(other.Head), Last(other.Last), Size(other.Size) {
    other.Head = nullptr;
    other.Last = nullptr;
    other.Size = 0;
}

template <typename T>
T LinkedList<T>::GetFirst() const {
    if (Size <= 0 || !Head || !Last) throw std::out_of_range("List is empty");
    return Head->Value;
}

template <typename T>
T LinkedList<T>::GetLast() const {
    if (Size <= 0 || !Head || !Last) throw std::out_of_range("List is empty");
    return Last->Value;
}

template <typename T>
T LinkedList<T>::Get(int index) const {
    if (!Head || !Last || Size <= 0) throw std::out_of_range("List is empty");
    if (index < 0 || index >= Size) throw std::out_of_range("Index out of range");
    TNode<T>* Actual_Node = nullptr;
    if (index >= Size / 2) {
        Actual_Node = Last;
        for (int i = Size - 1; i > index; i--) {
            Actual_Node = Actual_Node->Prev_Node;
        }
    }
    else {
        Actual_Node = Head;
        for (int i = 1; i <= index; i++) {
            Actual_Node = Actual_Node->Next_Node;
        }
    }
    return Actual_Node->Value;
}

template <typename T>
int LinkedList<T>::GetSize() const {
    return Size;
}

template <typename T>
void LinkedList<T>::Append(const T& value) {
    TNode<T>* new_Node = new TNode<T>(value);
    if (!Head) {
        Head = new_Node;
        Last = new_Node;
    }
    else {
        new_Node->Prev_Node = Last;
        Last->Next_Node = new_Node;
        Last = new_Node;
    } 
    Size++;
}

template <typename T>
void LinkedList<T>::Append(const T&& value) {
    TNode<T>* new_Node = new TNode<T>(std::move(value));
    if (!Head) {
        Head = new_Node;
        Last = new_Node;
    }
    else {
        new_Node->Prev_Node = Last;
        Last->Next_Node = new_Node;
        Last = new_Node;
    }
    Size++;
}

template <typename T>
void LinkedList<T>::Prepend(const T& value) {
    TNode<T>* new_Node = new TNode<T>(value);
    if (Head == nullptr) {
        Head = new_Node;
        Last = new_Node;
    }
    else {
        new_Node->Next_Node = Head;
        Head->Prev_Node = new_Node;
        Head = new_Node;
    }
    Size++;
}

template <typename T>
void LinkedList<T>::Prepend(const T&& value) {
    TNode<T>* new_Node = new TNode<T>(std::move(value));
    if (Head == nullptr) {
        Head = new_Node;
        Last = new_Node;
    }
    else {
        new_Node->Next_Node = Head;
        Head->Prev_Node = new_Node;
        Head = new_Node;
    }
    Size++;
}

template <typename T>
void LinkedList<T>::Set(int index, const T& value) {
    if (!Head || !Last || Size <= 0) return;
    if (index < 0 || index >= Size) throw std::out_of_range("Index out of range");
    TNode<T>* Actual_Node = nullptr;
    if (index >= Size / 2) {
        Actual_Node = Last;
        for (int i = Size - 1; i > index; i--) {
            Actual_Node = Actual_Node->Prev_Node;
        }
    }
    else {
        Actual_Node = Head;
        for (int i = 1; i <= index; i++) {
            Actual_Node = Actual_Node->Next_Node;
        }
    }
    Actual_Node->Value = value;
}

template <typename T>
void LinkedList<T>::Set(int index, const T&& value) {
    if (!Head || !Last || Size <= 0) return;
    if (index < 0 || index >= Size) throw std::out_of_range("Index out of range");
    TNode<T>* Actual_Node = nullptr;
    if (index >= Size / 2) {
        Actual_Node = Last;
        for (int i = Size - 1; i > index; i--) {
            Actual_Node = Actual_Node->Prev_Node;
        }
    }
    else {
        Actual_Node = Head;
        for (int i = 1; i <= index; i++) {
            Actual_Node = Actual_Node->Next_Node;
        }
    }
    Actual_Node->Value = std::move(value);
}

template <typename T>
void LinkedList<T>::InsertAt(int index, const T& value) {
    if (index < 0 || index > Size) throw std::out_of_range("Index out of range");
    if (index == 0) Prepend(value);
    else if (index == Size) Append(value);
    else if (index >= Size / 2) {
        TNode<T>* Actual_Node = Last;
        for (int i = Size - 1; i > index; i--) {
            Actual_Node = Actual_Node->Prev_Node;
        }
        TNode<T>* new_Node = new TNode<T>(value);
        new_Node->Next_Node = Actual_Node;
        new_Node->Prev_Node = Actual_Node->Prev_Node;
        Actual_Node->Prev_Node->Next_Node = new_Node;
        Actual_Node->Prev_Node = new_Node;
        Size++;
    }
    else {
        TNode<T>* Actual_Node = Head;
        for (int i = 0; i < index; i++) {
            Actual_Node = Actual_Node->Next_Node;
        }
        TNode<T>* new_Node = new TNode<T>(value);
        new_Node->Next_Node = Actual_Node;
        new_Node->Prev_Node = Actual_Node->Prev_Node;
        Actual_Node->Prev_Node->Next_Node = new_Node;
        Actual_Node->Prev_Node = new_Node;
        Size++;
    }
}

template <typename T>
void LinkedList<T>::InsertAt(int index, const T&& value) {
    if (index < 0 || index > Size) throw std::out_of_range("Index out of range");
    if (index == 0) Prepend(std::move(value));
    else if (index == Size) Append(std::move(value));
    else if (index >= Size / 2) {
        TNode<T>* Actual_Node = Last;
        for (int i = Size - 1; i > index; i--) {
            Actual_Node = Actual_Node->Prev_Node;
        }
        TNode<T>* new_Node = new TNode<T>(std::move(value));
        new_Node->Next_Node = Actual_Node;
        new_Node->Prev_Node = Actual_Node->Prev_Node;
        Actual_Node->Prev_Node->Next_Node = new_Node;
        Actual_Node->Prev_Node = new_Node;
        Size++;
    }
    else {
        TNode<T>* Actual_Node = Head;
        for (int i = 0; i < index; i++) {
            Actual_Node = Actual_Node->Next_Node;
        }
        TNode<T>* new_Node = new TNode<T>(std::move(value));
        new_Node->Next_Node = Actual_Node;
        new_Node->Prev_Node = Actual_Node->Prev_Node;
        Actual_Node->Prev_Node->Next_Node = new_Node;
        Actual_Node->Prev_Node = new_Node;
        Size++;
    }
}

template <typename T>
void LinkedList<T>::Resize(int size) {
    if (size < 0) throw std::invalid_argument("Size cannot be negative");
    else if (size == 0) {
        Delete();
        Head = nullptr;
        Last = nullptr;
        Size = 0;
    }
    else {
        if (size <= Size) {
            TNode<T>* Actual_Node = Head;
            for (int i = 0; i < size; i++) {
                Actual_Node = Actual_Node->Next_Node;
            }
            TNode<T>* temp = Actual_Node;
            while (temp) {
                TNode<T>* next = temp->Next_Node;
                delete temp;
                temp = next;
            }
            Last = Actual_Node->Prev_Node;
            if (Last) Last->Next_Node = nullptr;
            Size = size;
        }
        else {
            for (int i = Size; i < size; i++) {
                Append(T{});
            }
        }
    }
}

template <typename T>
void LinkedList<T>::RemoveAt(int index) {
    if (index < 0 || index >= Size) throw std::out_of_range("Index out of range");
    TNode<T>* Actual_Node = nullptr;
    if (index >= Size / 2) {
        Actual_Node = Last;
        for (int i = Size - 1; i > index; i--) {
            Actual_Node = Actual_Node->Prev_Node;
        }
    }
    else {
        Actual_Node = Head;
        for (int i = 0; i < index; i++) {
            Actual_Node = Actual_Node->Next_Node;
        }
    }
    if (Actual_Node == Head) {
        Head = Head->Next_Node;
        if (Head) Head->Prev_Node = nullptr;
    }
    else if (Actual_Node == Last) {
        Last = Last->Prev_Node;
        Last->Next_Node = nullptr;
    }
    else {
        Actual_Node->Prev_Node->Next_Node = Actual_Node->Next_Node;
        Actual_Node->Next_Node->Prev_Node = Actual_Node->Prev_Node;
    }
    delete Actual_Node;
    Size--;
    if (Size == 0) {
        Head = nullptr;
        Last = nullptr;
    }
}

template <typename T>
LinkedList<T>* LinkedList<T>::GetSubContainer(int startIndex, int endIndex) const {
    if (startIndex < 0 || startIndex >= Size || endIndex > Size || startIndex > endIndex) throw std::out_of_range("Index out of range");
    LinkedList<T>* list = new LinkedList<T>();
    TNode<T>* Actual_Node = nullptr;
    if (startIndex >= Size / 2) {
        Actual_Node = Last;
        for (int i = Size - 1; i > startIndex; i--) {
            Actual_Node = Actual_Node->Prev_Node;
        }
    }
    else {
        Actual_Node = Head;
        for (int i = 1; i <= startIndex; i++) {
            Actual_Node = Actual_Node->Next_Node;
        }
    }
    for (int i = startIndex; i < endIndex; i++) {
        list->Append(Actual_Node->Value);
        Actual_Node = Actual_Node->Next_Node;
    }
    return list;
}

template <typename T>
LinkedList<T>* LinkedList<T>::Concat(Container<T>* other) const {
    LinkedList<T>* result = new LinkedList<T>(*this);
    if (!dynamic_cast<LinkedList<T>*>(other) || !(dynamic_cast<LinkedList<T>*>(other))->Head || !(dynamic_cast<LinkedList<T>*>(other))->Last || (dynamic_cast<LinkedList<T>*>(other))->Size <= 0) return result;
    TNode<T>* Actual_Node = (dynamic_cast<LinkedList<T>*>(other))->Head;
    if (result->Size == 0) {
        result->Head = new TNode<T>(Actual_Node->Value);
        result->Last = result->Head;
        for (int i = 1; i < (dynamic_cast<LinkedList<T>*>(other))->Size; i++) {
            Actual_Node = Actual_Node->Next_Node;
            result->Last->Next_Node = new TNode<T>(Actual_Node->Value);
            result->Last->Next_Node->Prev_Node = result->Last;
            result->Last = result->Last->Next_Node;
        }
    }
    else {
        result->Last->Next_Node = new TNode<T>(Actual_Node->Value);
        result->Last->Next_Node->Prev_Node = result->Last;
        result->Last = result->Last->Next_Node;
        for (int i = 1; i < (dynamic_cast<LinkedList<T>*>(other))->Size; i++) {
            Actual_Node = Actual_Node->Next_Node;
            result->Last->Next_Node = new TNode<T>(Actual_Node->Value);
            result->Last->Next_Node->Prev_Node = result->Last;
            result->Last = result->Last->Next_Node;
        }
    }
    result->Size += (dynamic_cast<LinkedList<T>*>(other))->Size;
    return result;
}

template <typename T>
LinkedList<T>* LinkedList<T>::Clutch(Container<T>* other) {
    if (!dynamic_cast<LinkedList<T>*>(other) || !(dynamic_cast<LinkedList<T>*>(other))->Head || !(dynamic_cast<LinkedList<T>*>(other))->Last || (dynamic_cast<LinkedList<T>*>(other))->Size <= 0) return this;
    TNode<T>* Actual_Node = (dynamic_cast<LinkedList<T>*>(other))->Head;
    if (this->Size == 0) {
        this->Head = new TNode<T>(Actual_Node->Value);
        this->Last = this->Head;
        for (int i = 1; i < (dynamic_cast<LinkedList<T>*>(other))->Size; i++) {
            Actual_Node = Actual_Node->Next_Node;
            this->Last->Next_Node = new TNode<T>(Actual_Node->Value);
            this->Last->Next_Node->Prev_Node = this->Last;
            this->Last = this->Last->Next_Node;
        }
    }
    else {
        this->Last->Next_Node = new TNode<T>(Actual_Node->Value);
        this->Last->Next_Node->Prev_Node = this->Last;
        this->Last = this->Last->Next_Node;
        for (int i = 1; i < (dynamic_cast<LinkedList<T>*>(other))->Size; i++) {
            Actual_Node = Actual_Node->Next_Node;
            this->Last->Next_Node = new TNode<T>(Actual_Node->Value);
            this->Last->Next_Node->Prev_Node = this->Last;
            this->Last = this->Last->Next_Node;
        }
    }
    this->Size += (dynamic_cast<LinkedList<T>*>(other))->Size;
    return this;
}

template <typename T>
std::string LinkedList<T>::toString() const noexcept {
    std::ostringstream oss;
    oss << "[";
    if (Size > 0 && Head ) {
        TNode<T>* Actual_Node = Head;
        oss << Actual_Node->Value;
        for (int i = 1; i < Size; i++) {
            Actual_Node = Actual_Node->Next_Node;
            oss << ", " << Actual_Node->Value;
        }
    }
    oss << "]";
    return oss.str();
}

template <typename T>
template <typename Container>
LinkedList<T>* LinkedList<T>::From(const Container& container) {
    Delete();
    for (auto it = container.begin(); it != container.end(); ++it) {
        Append(*it);
    }
    return this;
}

template <typename T>
template <typename U>
LinkedList<U>* LinkedList<T>::Map(std::function<U(T)> f) const {
    LinkedList<U>* result = new LinkedList<U>();
    if (!Head || !Last || Size <= 0) return result;
    TNode<T>* Actual_Node = Head;
    while (Actual_Node) {
        result->Append(f(Actual_Node->Value));
        Actual_Node = Actual_Node->Next_Node;
    }
    return result;
}

template <typename T>
template <typename U>
LinkedList<T>* LinkedList<T>::FlatMap(std::function<LinkedList<T>*(U)> f) const {
    LinkedList<T>* result = new LinkedList<T>();
    for (auto it = begin(); it != end(); ++it) {
        LinkedList<T>* temp = f(*it);
        if (temp) {
            for (auto tempIt = temp->begin(); tempIt != temp->end(); ++tempIt) {
                result->Append(*tempIt);
            }
            delete temp;
        }
    }
    return result;
}

template <typename T>
LinkedList<T>* LinkedList<T>::Where(std::function<bool(T)> f) const {
    LinkedList<T>* result = new LinkedList<T>();
    if (!Head || !Last || Size <= 0) return result;
    TNode<T>* Actual_Node = Head;
    while (Actual_Node) {
        if (f(Actual_Node->Value)) {
            result->Append(Actual_Node->Value);
        }
        Actual_Node = Actual_Node->Next_Node;
    }
    return result;
}

template <typename T>
T LinkedList<T>::Reduce(std::function<T(T, T)> f, const T& c) const {
    if (!Head || !Last || Size <= 0) return c;
    T answer = f(Head->Value, c);
    TNode<T>* Actual_Node = Head->Next_Node;
    for (int i = 1; i < Size; i++) {
        answer = f(Actual_Node->Value, answer);
        Actual_Node = Actual_Node->Next_Node;
    }
    return answer;
}

template <typename T>
template <typename... Lists>
LinkedList<std::tuple<T, typename Lists::value_type...>>* LinkedList<T>::Zip(const LinkedList<T>* first, const Lists*... lists) const {
    LinkedList<std::tuple<T, typename Lists::value_type...>>* result = new LinkedList<std::tuple<T, typename Lists::value_type...>>();

    auto it_first = first->begin();
    auto iters = std::make_tuple(lists->begin()...);

    auto all_valid = [&](const auto& iters) {
        bool valid = it_first != first->end();
        if (!valid) return false;

        auto check = [&]<size_t... Is>(std::index_sequence<Is...>) {
            return ((std::get<Is>(iters) != lists->end()) && ...);
        };
        return valid && check(std::index_sequence_for<Lists...>{});
    };

    while (all_valid(iters)) {
        auto tuple = std::apply([&](const auto&... its) {
            return std::make_tuple(*it_first, (*its)...);
        }, iters);
        result->Append(tuple);

        ++it_first;
        std::apply([](auto&... its) {
            ((++its), ...);
        }, iters);
    }
    return result;
}

template <typename T>
template <typename... Tuples>
std::tuple<LinkedList<Tuples>...>* LinkedList<T>::UnZip() const {
    std::tuple<LinkedList<Tuples>...>* result = new std::tuple<LinkedList<Tuples>...>();
    for (auto it = begin(); it != end(); ++it) {
        auto unzip = [&]<size_t... Is>(std::index_sequence<Is...>) {
            ((std::get<Is>(*result).Append(std::get<Is>(*it))), ...);
        };
        unzip(std::index_sequence_for<Tuples...>{});
    }
    return result;
}



template <typename T>
void LinkedList<T>::Delete() noexcept {
    while (Head) {
        TNode<T>* temp = Head->Next_Node;
        delete Head;
        Head = temp;
    }
    Head = nullptr;
    Last = nullptr;
    Size = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() noexcept {
    Delete();
}

#endif // LINKED_LIST_HPP