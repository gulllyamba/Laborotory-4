#ifndef LISTSEQUENCE_HPP
#define LISTSEQUENCE_HPP

#include "../Sequence/Sequence.hpp"
#include "LinkedList.hpp"

template <typename T>
class ListSequence;

template <typename T, bool IsConst>
class ListSequenceIterator : public IIterator<T, IsConst> {
    public:
        using value_type = typename IIterator<T, IsConst>::value_type;
        using pointer = std::conditional_t<IsConst, const T*, T*>;
        using reference = typename IIterator<T, IsConst>::reference;
        using difference_type = typename IIterator<T, IsConst>::difference_type;
        using iterator_category = std::bidirectional_iterator_tag;

        using base_iterator = std::conditional_t<IsConst, typename LinkedList<T>::const_iterator, typename LinkedList<T>::iterator>;

        ListSequenceIterator(LinkedList<T>* list, base_iterator ptr) : list(list), current(ptr) {}

        bool HasNext() const override {
            if (!list) return false;
            return current != list->cend();
        }

        reference Current() override {
            return **this;
        }

        void MoveNext() override {
            ++(*this);
        }

        reference operator*() const {
            if (!list || current == list->cend()) throw std::out_of_range("Iterator out of range");
            return *current;
        }

        pointer operator->() const {
            if (!list || current == list->cend()) throw std::out_of_range("Iterator out of range");
            return &(*current);
        }

        ListSequenceIterator& operator++() {
            if (!list || current == list->cend()) throw std::out_of_range("Iterator out of range");
            ++current;
            return *this;
        }
        ListSequenceIterator operator++(int) {
            ListSequenceIterator temp = *this;
            ++(*this);
            return temp;
        }

        ListSequenceIterator& operator--() {
            if (!list || current == list->cbegin()) throw std::out_of_range("Iterator out of range");
            --current;
            return *this;
        }
        ListSequenceIterator operator--(int) {
            ListSequenceIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const ListSequenceIterator& other) const {
            return list == other.list && current == other.current;
        }
        bool operator!=(const ListSequenceIterator& other) const {
            return !(*this == other);
        }

    private:
        friend class ListSequence<T>;
        LinkedList<T>* list;
        base_iterator current;
};

template <typename T>
using LSIterator = ListSequenceIterator<T, false>;
template <typename T>
using LSConstIterator = ListSequenceIterator<T, true>;

template <typename T>
class ListSequence : public Sequence<T>, public IEnumerable<T> {
    protected:
        LinkedList<T>* list;

        T Get(int index) const override {
            return list->Get(index);
        }
        T GetFirst() const override {
            return list->GetFirst();
        }
        T GetLast() const override {
            return list->GetLast();
        }
        int GetSize() const override {
            return list->GetSize();
        }

        ListSequence<T>* SetInternal(int index, const T& value) {
            list->Set(index, value);
            return this;
        }

        ListSequence<T>* AppendInternal(const T& value) {
            list->Append(value);
            return this;
        }

        ListSequence<T>* PrependInternal(const T& value) {
            list->Prepend(value);
            return this;
        }

        ListSequence<T>* InsertAtInternal(int index, const T& value) {
            list->InsertAt(index, value);
            return this;
        }

        ListSequence<T>* ResizeInternal(int size) {
            list->Resize(size);
            return this;
        }

        ListSequence<T>* RemoveAtInternal(int index) {
            list->RemoveAt(index);
            return this;
        }

        virtual ListSequence<T>* Instance() = 0;

    public:
        using value_type = T;
        using iterator = LSIterator<T>;
        using const_iterator = LSConstIterator<T>;

        iterator begin() {
            if (!list) throw std::runtime_error("List is not initialized");
            return iterator(list, list->begin());
        }
        iterator end() {
            if (!list) throw std::runtime_error("List is not initialized");
            return iterator(list, list->end());
        }
        const_iterator begin() const {
            if (!list) throw std::runtime_error("List is not initialized");
            return const_iterator(list, list->cbegin());
        }
        const_iterator end() const {
            if (!list) throw std::runtime_error("List is not initialized");
            return const_iterator(list, list->cend());
        }
        const_iterator cbegin() const {
            return begin();
        }
        const_iterator cend() const {
            return end();
        }

        std::unique_ptr<IIterator<T, false>> GetIterator() override {
            if (!list) throw std::runtime_error("List is not initialized");
            return std::make_unique<iterator>(list, list->begin());
        }
        std::unique_ptr<IIterator<T, true>> GetConstIterator() const override {
            if (!list) throw std::runtime_error("List is not initialized");
            return std::make_unique<const_iterator>(list, list->cbegin());
        }

        ListSequence(const T* items, int count) {
            list = new LinkedList<T>(items, count);
        }
        ListSequence() : ListSequence(nullptr, 0) {}
        ListSequence(int size) : ListSequence(nullptr, size) {}
        ListSequence(const ListSequence<T>& other) {
            list = new LinkedList<T>(*(other.list));
        }
        ListSequence(const LinkedList<T>& other) {
            list = new LinkedList<T>(other);
        }

        ListSequence<T>& operator=(const ListSequence<T>& other) noexcept {
            *list = *other.list;
            return *this;
        }
        ListSequence<T>& operator=(ListSequence<T>&& other) noexcept {
            delete list;
            list = other.list;
            other.list = nullptr;
            return *this;
        }

        T& operator[](int index) {
            return list->operator[](index);
        }
        const T& operator[](int index) const {
            return list->operator[](index);
        }

        const LinkedList<T>& GetList() const {
            return *list;
        }
};

#endif // LISTSEQUENCE_HPP