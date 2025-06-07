#ifndef ARRAYSEQUENCE_HPP
#define ARRAYSEQUENCE_HPP

#include "../Sequence/Sequence.hpp"
#include "DynamicArray.hpp"

template <typename T>
class ArraySequence;

template <typename T, bool IsConst>
class ArraySequenceIterator : public IIterator<T, IsConst> {
    public:
        using value_type = typename IIterator<T, IsConst>::value_type;
        using pointer = std::conditional_t<IsConst, const T*, T*>;
        using reference = typename IIterator<T, IsConst>::reference;
        using difference_type = typename IIterator<T, IsConst>::difference_type;
        using iterator_category = std::random_access_iterator_tag;

        using base_iterator = std::conditional_t<IsConst, typename DynamicArray<T>::const_iterator, typename DynamicArray<T>::iterator>;

        ArraySequenceIterator(DynamicArray<T>* array, base_iterator ptr) : array(array), current(ptr) {}

        bool HasNext() const override {
            if (!array) return false;
            return current != array->cend();
        }
        reference Current() override {
            return **this;
        }
        void MoveNext() override {
            ++(*this);
        }

        reference operator*() const {
            if (!array || current == array->cend()) throw std::out_of_range("Iterator out of range");
            return *current;
        }

        pointer operator->() const {
            if (!array || current == array->cend()) throw std::out_of_range("Iterator out of range");
            return &(*current);
        }

        ArraySequenceIterator& operator++() {
            if (!array || current == array->cend()) throw std::out_of_range("Iterator out of range");
            ++current;
            return *this;
        }
        ArraySequenceIterator operator++(int) {
            ArraySequenceIterator temp = *this;
            ++(*this);
            return temp;
        }

        ArraySequenceIterator& operator--() {
            if (!array || current == array->cbegin()) throw std::out_of_range("Iterator out of range");
            --current;
            return *this;
        }
        ArraySequenceIterator operator--(int) {
            ArraySequenceIterator temp = *this;
            --(*this);
            return temp;
        }

        ArraySequenceIterator& operator+=(difference_type n) {
            if (!array || n < 0 || current + n > array->cend() || current + n < array->cbegin()) throw std::out_of_range("Iterator out of range");
            current += n;
            return *this; 
        }
        ArraySequenceIterator& operator-=(difference_type n) {
            return *this += -n; 
        }

        ArraySequenceIterator operator+(difference_type n) const {
            if (!array || n < 0 || current + n > array->cend() || current + n < array->cbegin()) throw std::out_of_range("Iterator out of range");
            return ArraySequenceIterator(array, current + n);
        }
        ArraySequenceIterator operator-(difference_type n) const {
            return *this + (-n);
        }
        difference_type operator-(const ArraySequenceIterator& other) const {
            if (!array || !other.array || array != other.array) throw std::invalid_argument("Iterators are incompatible");
            return current - other.current;
        }

        bool operator==(const ArraySequenceIterator& other) const {
            return array == other.array && current == other.current;
        }
        bool operator!=(const ArraySequenceIterator& other) const {
            return !(*this == other);
        }
        bool operator<(const ArraySequenceIterator& other) const {
            if (array != other.array) throw std::invalid_argument("Iterators are incompatible");
            return current < other.current;
        }
        bool operator>(const ArraySequenceIterator& other) const {
            return other < *this;
        }
        bool operator<=(const ArraySequenceIterator& other) const {
            return !(*this > other);
        }
        bool operator>=(const ArraySequenceIterator& other) const {
            return !(*this < other);
        }
    
        reference operator[](difference_type n) const {
            if (!array || current + n < array->cbegin() || current + n >= array->cend()) throw std::out_of_range("Iterator out of range");
            return *(current + n);
        }
    private:
        friend class ArraySequence<T>;
        DynamicArray<T>* array;
        base_iterator current;
};

template <typename T>
using ASIterator = ArraySequenceIterator<T, false>;
template <typename T>
using ASConstIterator = ArraySequenceIterator<T, true>;

template <typename T>
class ArraySequence : public Sequence<T>, public IEnumerable<T> {
    protected:
        DynamicArray<T>* array;

        T Get(int index) const override {
            return this->array->Get(index);
        }
        T GetFirst() const override {
            return this->array->GetFirst();
        }
        T GetLast() const override {
            return this->array->GetLast();
        }
        int GetSize() const override {
            return this->array->GetSize();
        }

        ArraySequence<T>* ReserveInternal(int newCapacity) {
            array->Reserve(newCapacity);
            return this;
        }

        ArraySequence<T>* SetInternal(int index, const T& value) {
            array->Set(index, value);
            return this;
        }

        ArraySequence<T>* AppendInternal(const T& value) {
            array->Append(value);
            return this;
        }

        ArraySequence<T>* PrependInternal(const T& value) {
            array->Prepend(value);
            return this;
        }

        ArraySequence<T>* InsertAtInternal(int index, const T& value) {
            array->InsertAt(index, value);
            return this;
        }

        ArraySequence<T>* ResizeInternal(int size) {
            array->Resize(size);
            return this;
        }

        ArraySequence<T>* RemoveAtInternal(int index) {
            array->RemoveAt(index);
            return this;
        }

        virtual ArraySequence<T>* Instance() = 0;
        
    public:
        using value_type = T;
        using iterator = ASIterator<T>;
        using const_iterator = ASConstIterator<T>;

        iterator begin() { 
            if (!array) throw std::runtime_error("Array is not initialized");
            return iterator(array, array->begin());
        }
        iterator end() {
            if (!array) throw std::runtime_error("Array is not initialized");
            return iterator(array, array->end());
        }
        const_iterator begin() const {
            if (!array) throw std::runtime_error("Array is not initialized");
            return const_iterator(array, array->cbegin());
        }
        const_iterator end() const {
            if (!array) throw std::runtime_error("Array is not initialized");
            return const_iterator(array, array->cend());
        }
        const_iterator cbegin() const {
            return begin();
        }
        const_iterator cend() const {
            return end();
        }

        std::unique_ptr<IIterator<T, false>> GetIterator() override {
            if (!array) throw std::runtime_error("Array is not initialized");
            return std::make_unique<iterator>(array, array->begin());
        }
        std::unique_ptr<IIterator<T, true>> GetConstIterator() const override {
            if (!array) throw std::runtime_error("Array is not initialized");
            return std::make_unique<const_iterator>(array, array->cbegin());
        }

        ArraySequence(const T* items, int count) {
            array = new DynamicArray<T>(items, count);
        }
        ArraySequence() : ArraySequence<T>(nullptr, 0) {}
        ArraySequence(int size) : ArraySequence<T>(nullptr, size) {}
        ArraySequence(const ArraySequence<T>& other) {
            array = new DynamicArray<T>(*(other.array));
        }
        ArraySequence(const DynamicArray<T>& other) {
            array = new DynamicArray<T>(other);
        }

        int GetCapacity() const {
            return this->array->GetCapacity();
        }

        ArraySequence<T>& operator=(const ArraySequence<T>& other) noexcept {
            *array = *other.array;
            return *this;
        }
        ArraySequence<T>& operator=(ArraySequence<T>&& other) noexcept {
            delete array;
            array = other.array;
            other.array = nullptr;
            return *this;
        }

        T& operator[](int index) {
            return array->operator[](index);
        }
        const T& operator[](int index) const {
            return array->operator[](index);
        }

        const DynamicArray<T>& GetArray() const {
            return *array;
        }
};

#endif // ARRAYSEQUENCE_HPP