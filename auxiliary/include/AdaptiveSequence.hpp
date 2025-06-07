#ifndef ADAPTIVESEQUENCE_HPP
#define ADAPTIVESEQUENCE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include "Iterator.hpp"
#include "Container.hpp"

template <typename T>
class AdaptiveSequence;

template <typename T, bool IsConst>
class AdaptIterator : public IIterator<T, IsConst> {
    public:
        using value_type = typename IIterator<T, IsConst>::value_type;
        using pointer = std::conditional_t<IsConst, const T*, T*>;
        using reference = typename IIterator<T, IsConst>::reference;
        using difference_type = typename IIterator<T, IsConst>::difference_type;
        using iterator_category = std::random_access_iterator_tag;

        AdaptIterator(pointer ptr) : current(ptr) {}

        bool HasNext() const override {
            return true;
        }
        reference Current() override {
            return *current;
        }
        void MoveNext() override {
            ++current;
        }

        reference operator*() const {
            if (!current) throw std::out_of_range("Iterator out of range");
            return *current;
        }

        pointer operator->() const {
            if (!current) throw std::out_of_range("Iterator out of range");
            return current;
        }

        AdaptIterator& operator++() {
            ++current;
            return *this;
        }
        AdaptIterator operator++(int) {
            AdaptIterator temp = *this;
            ++current;
            return temp;
        }

        AdaptIterator& operator--() {
            --current;
            return *this;
        }
        AdaptIterator operator--(int) {
            AdaptIterator temp = *this;
            --current;
            return temp;
        }

        AdaptIterator& operator+=(difference_type n) {
            current += n;
            return *this; 
        }
        AdaptIterator& operator-=(difference_type n) {
            current -= n;
            return *this; 
        }

        AdaptIterator operator+(difference_type n) const {
            return AdaptIterator(current + n);
        }
        AdaptIterator operator-(difference_type n) const {
            return AdaptIterator(current - n);
        }
        difference_type operator-(const AdaptIterator& other) const {
            return current - other.current;
        }

        bool operator==(const AdaptIterator& other) const {
            return current == other.current;
        }
        bool operator!=(const AdaptIterator& other) const {
            return !(current == other.current);
        }
        bool operator<(const AdaptIterator& other) const {
            return current < other.current;
        }
        bool operator>(const AdaptIterator& other) const {
            return current > other.current;
        }
        bool operator<=(const AdaptIterator& other) const {
            return current <= other.current;
        }
        bool operator>=(const AdaptIterator& other) const {
            return current >= other.current;
        }
    
        reference operator[](difference_type n) const {
            return *(current + n);
        }


    private:
        friend class AdaptiveSequence<T>;
        pointer current;
};

template <typename T>
using AdIterator = AdaptIterator<T, false>;
template <typename T>
using AdConstIterator = AdaptIterator<T, true>;

template <typename T>
class AdaptiveSequence : public Container<T>, public IEnumerable<T> {
    public:
        using value_type = T;
        using iterator = AdIterator<T>;
        using const_iterator = AdConstIterator<T>;

        iterator begin() {
            return iterator(Data + correctLeft);
        }
        iterator end() {
            return iterator(Data + correctLeft + Size);
        }
        const_iterator begin() const {
            return const_iterator(Data + correctLeft);
        }
        const_iterator end() const {
            return const_iterator(Data + correctLeft + Size);
        }
        const_iterator cbegin() const {
            return const_iterator(Data + correctLeft);
        }
        const_iterator cend() const {
            return const_iterator(Data + correctLeft + Size);
        }

        std::unique_ptr<IIterator<T, false>> GetIterator() override {
            return std::make_unique<iterator>(Data + correctLeft);
        }
        std::unique_ptr<IIterator<T, true>> GetConstIterator() const override {
            return std::make_unique<const_iterator>(Data + correctLeft);
        }

        AdaptiveSequence(T* items, int size) {
            if (size < 0) throw std::invalid_argument("Size cannot be negative");
            else if (size == 0) {
                Size = 0;
                correctLeft = 0;
                correctRight = 1;
                Data  = new T[correctRight]{};
                return;
            }
            else if (items) {
                Size = size;
                correctLeft = Size / 2;
                if (size % 2 == 0) correctRight = Size / 2;
                else correctRight = Size / 2 + 1;
                Data = new T[Size * 2]{};
                for (int i = 0; i < Size; i++) {
                    Data[i + correctLeft] = items[i];
                }
            }
            else {
                Size = size;
                correctLeft = Size / 2;
                if (size % 2 == 0) correctRight = Size / 2;
                else correctRight = Size / 2 + 1;
                Data = new T[Size * 2]{};
            }
        }
        AdaptiveSequence(): AdaptiveSequence(nullptr, 0) {}
        AdaptiveSequence(int size): AdaptiveSequence(nullptr, size) {}
        AdaptiveSequence(const AdaptiveSequence<T>& other) {
            if (other.Size < 0) throw std::invalid_argument("Size cannot be negative");
            else if (other.Size == 0) {
                Size = 0;
                correctLeft = 0;
                correctRight = 1;
                Data  = new T[correctRight]{};
                return;
            }
            Size = other.Size;
            correctLeft = Size / 2;
            if (other.Size % 2 == 0) correctRight = Size / 2;
            else correctRight = Size / 2 + 1;
            Data = new T[Size * 2]{};
            for (int i = 0; i < Size; i++) {
                Data[i + correctLeft] = other.Get(i);
            }
        }
        AdaptiveSequence(AdaptiveSequence<T>&& other) noexcept {
            Data = other.Data;
            Size = other.Size;
            correctLeft = other.correctLeft;
            correctRight = other.correctRight;
        
            other.Data = nullptr;
            other.Size = 0;
            other.correctLeft = 0;
            other.correctRight = 0;
        }
        
        int GetCorrectLeft() const {
            return correctLeft;
        }
        int GetCorrectRight() const {
            return correctRight;
        }
        T GetFirst() const override {
            if (!Data || Size <= 0) throw std::out_of_range("Array is empty");
            return Data[correctLeft];
        }
        T GetLast() const override {
            if (!Data || Size <= 0) throw std::out_of_range("Array is empty");
            return Data[correctLeft + Size - 1];   
        }
        T Get(int index) const override {
            if (!Data || Size <= 0) throw std::out_of_range("Array is empty");
            if (index >= Size || index < 0) throw std::out_of_range("Index out of range");
            return Data[correctLeft + index]; 
        }
        int GetSize() const override {
            return Size;
        }
        
        void Append(const T& value) override {
            if (correctRight == 0 && correctLeft == 0) Resize(Size);
            if (correctLeft >= correctRight) {
                for (int i = 0; i < Size; i++) {
                    Data[correctLeft + i - 1] = Data[correctLeft + i];
                }
                Data[correctLeft + Size - 1] = value;
                correctLeft--;
            }
            else {
                Data[correctLeft + Size] = value;
                correctRight--;
            }
            Size++;
        }
        void Append(const T&& value) override {
            if (correctRight == 0 && correctLeft == 0) Resize(Size);
            if (correctLeft >= correctRight) {
                for (int i = 0; i < Size; i++) {
                    Data[correctLeft + i - 1] = Data[correctLeft + i];
                }
                Data[correctLeft + Size - 1] = std::move(value);
                correctLeft--;
            }
            else {
                Data[correctLeft + Size] = std::move(value);
                correctRight--;
            }
            Size++;
        }

        void Prepend(const T& value) override {
            if (correctRight == 0 && correctLeft == 0) Resize(Size);
            if (correctLeft >= correctRight) {
                Data[correctLeft - 1] = value;
                correctLeft--;
            }
            else {
                for (int i = Size; i > 0; i--) {
                    Data[correctLeft + i] = Data[correctLeft + i - 1];
                }
                Data[correctLeft] = value;
                correctRight--;
            }
            Size++;
        }
        void Prepend(const T&& value) override {
            if (correctRight == 0 && correctLeft == 0) Resize(Size);
            if (correctLeft >= correctRight) {
                Data[correctLeft - 1] = std::move(value);
                correctLeft--;
            }
            else {
                for (int i = Size; i > 0; i--) {
                    Data[correctLeft + i] = Data[correctLeft + i - 1];
                }
                Data[correctLeft] = std::move(value);
                correctRight--;
            }
            Size++;
        }

        void Set(int index, const T& value) override {
            if (!Data || Size <= 0) throw std::out_of_range("Array is empty");
            if (index >= Size || index < 0) throw std::out_of_range("Index out of range");
            Data[correctLeft + index] = value;
        }
        void Set(int index, const T&& value) override {
            if (!Data || Size <= 0) throw std::out_of_range("Array is empty");
            if (index >= Size || index < 0) throw std::out_of_range("Index out of range");
            Data[correctLeft + index] = std::move(value);
        }

        void InsertAt(int index, const T& value) override {
            if (index < 0 || index > Size) throw std::out_of_range("Index out of range");
            if (correctRight == 0 && correctLeft == 0) Resize(Size);
            if (correctLeft >= correctRight) {
                for (int i = 0; i < index; i++) {
                    Data[correctLeft - 1 + i] = Data[correctLeft + i];
                }
                Data[correctLeft - 1 + index] = value;
                correctLeft--;
            }
            else {
                for (int i = Size; i > index; i--) {
                    Data[correctLeft + i] = Data[correctLeft + i - 1];
                }
                Data[correctLeft + index] = value;
                correctRight--;
            }
            Size++;
        }
        void InsertAt(int index, const T&& value) override {
            if (index < 0 || index > Size) throw std::out_of_range("Index out of range");
            if (correctRight == 0 && correctLeft == 0) Resize(Size);
            if (correctLeft >= correctRight) {
                for (int i = 0; i < index; i++) {
                    Data[correctLeft - 1 + i] = Data[correctLeft + i];
                }
                Data[correctLeft - 1 + index] = std::move(value);
                correctLeft--;
            }
            else {
                for (int i = Size; i > index; i--) {
                    Data[correctLeft + i] = Data[correctLeft + i - 1];
                }
                Data[correctLeft + index] = std::move(value);
                correctRight--;
            }
            Size++;
        }

        void Resize(int size) override {
            if (size < 0) throw std::invalid_argument("Size cannot be negative");
            else if (size == 0) {
                delete [] Data;
                Size = 0;
                correctLeft = 0;
                correctRight = 1;
                Data = new T[correctRight]{};
            }
            else if (Size == size) {
                T* newData = new T[Size * 2]{};
                int new_correctLeft = Size / 2;
                int new_correctRight = Size / 2 + 1;
                if (Size % 2 == 0) new_correctRight = Size / 2;
                for (int i = 0; i < Size; i++) {
                    newData[new_correctLeft + i] = Data[correctLeft + i];
                }
                delete [] Data;
                Data = newData;
                correctLeft = new_correctLeft;
                correctRight = new_correctRight;
            }
            else {
                T* newData = new T[size * 2]{};
                int new_correctLeft = size / 2;
                int new_correctRight = size / 2 + 1;
                if (size % 2 == 0) new_correctRight = size / 2;
                for (int i = 0; i < std::min(Size, size); i++) {
                    newData[new_correctLeft + i] = Data[correctLeft + i];
                }
                delete [] Data;
                Data = newData;
                Size = size;
                correctLeft = new_correctLeft;
                correctRight = new_correctRight;
            }
        }

        void RemoveAt(int index) override {
            if (index < 0 || index >= Size) throw std::out_of_range("Index out of range");
            if (Size == 0) throw std::invalid_argument("Array is empty");
            if (correctRight > correctLeft) {
                for (int i = index; i > 0; i--) {
                    Data[correctLeft + i] = Data[correctLeft + i - 1];
                }
                Data[correctLeft] = T{};
                correctLeft++;
            }
            else {
                for (int i = index; i < Size - 1; i++) {
                    Data[correctLeft + i] = Data[correctLeft + i + 1];
                }
                Data[correctLeft + Size - 1] = T{};
                correctRight++;
            }
            Size--;
        }
        
        std::string toString(bool flag) const {
            std::ostringstream oss;
            oss << "[";
            if (Size > 0 && Data) {
                if (flag) {
                    oss << Get(0);
                    for (int i = 1; i < Size; i++) {
                        oss << ", " << Get(i);
                    }
                }
                else {
                    if (correctLeft > 0) {
                        oss << Data[0];
                        for (int i = 1; i < correctLeft; i++) oss << ", " << Data[i];
                        for (int i = 0; i < Size; i++) {
                            oss << ", " << Get(i);
                        }
                    }
                    else {
                        oss << Get(0);
                        for (int i = 1; i < Size; i++) {
                            oss << ", " << Get(i);
                        }
                    }
                    for (int i = 0; i < correctRight; i++) {
                        oss << ", " << Data[correctLeft + Size + i];
                    }
                }
            }
            else if ((correctLeft > 0 || correctRight > 0) && !flag) {
                oss << Data[0];
                for (int i = 1; i < correctLeft; i++) oss << ", " << Data[i];
                for (int i = 0; i < correctRight; i++) {
                    if (correctLeft == 0 && correctRight == 1) break;
                    oss << ", " << Data[correctLeft + Size + i];
                }
            }
            oss << "]";
            return oss.str();
        }

        AdaptiveSequence<T>* GetSubContainer(int startIndex, int endIndex) const override {
            if (startIndex < 0 || startIndex >= Size || endIndex > Size || startIndex > endIndex) throw std::out_of_range("Index out of range");
            AdaptiveSequence<T>* result = new AdaptiveSequence<T>(endIndex - startIndex);
            for (int i = startIndex; i < endIndex; i++) {
                result->Data[result->correctLeft + i - startIndex] = Get(i);
            }
            return result;
        }

        AdaptiveSequence<T>* Concat(Container<T>* other) const override {
            AdaptiveSequence<T>* result = new AdaptiveSequence<T>(this->Size + (dynamic_cast<AdaptiveSequence<T>*>(other))->Size);
            for (int i = 0; i < this->Size; i++) {
                result->Data[result->correctLeft + i] = this->Get(i);
            }
            for (int i = 0; i < (dynamic_cast<AdaptiveSequence<T>*>(other))->Size; i++) {
                result->Data[result->correctLeft + this->Size + i] = (dynamic_cast<AdaptiveSequence<T>*>(other))->Get(i);
            }
            return result;
        }   

        AdaptiveSequence<T>* Clutch(Container<T>* other) override {
            if (!dynamic_cast<AdaptiveSequence<T>*>(other) || !(dynamic_cast<AdaptiveSequence<T>*>(other))->Data || (dynamic_cast<AdaptiveSequence<T>*>(other))->Size <= 0) return this;
            for (int i = 0; i < (dynamic_cast<AdaptiveSequence<T>*>(other))->Size; i++) {
                this->Append(dynamic_cast<AdaptiveSequence<T>*>(other)->Get(i));
            }
            return this;
        } 

        template <typename Container>
        AdaptiveSequence<T>* From(const Container& container) {
            if (Data) delete [] Data;
            Size = 0;
            for (auto it = container.begin(); it != container.end(); ++it) Size++;
            Data = new T[Size * 2]{};
            correctLeft = Size / 2;
            correctRight = Size / 2 + 1;
            if (Size % 2 == 0) correctRight = Size / 2;
            for (auto it = container.begin(), i = 0; it != container.end(); ++it, i++) {
                Data[correctLeft + i] = *it;
            }
            return this;
        }

        template <typename U>
        AdaptiveSequence<U>* Map(std::function<U(T)> f) const {
            AdaptiveSequence<U>* result = new AdaptiveSequence<U>(Size);
            if (!Data || Size <= 0) return result;
            for (int i = 0; i < result->Size; i++) {
                result->Data[result->correctLeft + i] = f(Data[correctLeft + i]);
            }
            return result;
        }

        template <typename U>
        AdaptiveSequence<T>* FlatMap(std::function<AdaptiveSequence<T>*(U)> f) const {
            AdaptiveSequence<T>* result = new AdaptiveSequence<T>();
            for (auto it = begin(); it != end(); ++it) {
                AdaptiveSequence<T>* temp = f(*it);
                for (auto tempIt = temp->begin(); tempIt != temp->end(); ++tempIt) {
                    result->Append(*tempIt);
                }
                if (temp) delete temp;
            }
            result->Resize(result->Size);
            return result;
        }

        AdaptiveSequence<T>* Where(std::function<bool(T)> f) const {
            AdaptiveSequence<T>* result = new AdaptiveSequence<T>();
            if (!Data || Size <= 0) return result;
            for (int i = 0; i < Size; i++) {
                if (f(Data[correctLeft + i])) {
                    result->Append(Data[correctLeft + i]);
                }
            }
            result->Resize(result->Size);
            return result;
        }

        T Reduce(std::function<T(T, T)> f, const T& c) const {
            if (!Data || Size <= 0) return c;
            T answer = f(Data[correctLeft], c);
            for (int i = 1; i < Size; i++) {
                answer = f(Data[correctLeft + i], answer);
            }
            return answer;
        }

        template <typename... Arrays>
        AdaptiveSequence<std::tuple<T, typename Arrays::value_type...>>* Zip(const AdaptiveSequence<T>* first, const Arrays*... arrays) const {
            AdaptiveSequence<std::tuple<T, typename Arrays::value_type...>>* result = new AdaptiveSequence<std::tuple<T, typename Arrays::value_type...>>();

            auto it_first = first->begin();
            auto iters = std::make_tuple(arrays->begin()...);

            auto all_valid = [&](const auto& iters) {
                bool valid = it_first != first->end();
                if (!valid) return false;

                auto check = [&]<size_t... Is>(std::index_sequence<Is...>) {
                    return ((std::get<Is>(iters) != arrays->end()) && ...);
                };
                return valid && check(std::index_sequence_for<Arrays...>{});
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
            result->Resize(result->Size);
            return result;
        }

        template <typename... Tuples>
        std::tuple<AdaptiveSequence<Tuples>...>* UnZip() const {
            std::tuple<AdaptiveSequence<Tuples>...>* result = new std::tuple<AdaptiveSequence<Tuples>...>();
            for (auto it = begin(); it != end(); ++it) {
                auto unzip = [&]<size_t... Is>(std::index_sequence<Is...>) {
                    ((std::get<Is>(*result).Append(std::get<Is>(*it))), ...);
                };
                unzip(std::index_sequence_for<Tuples...>{});
            }
            return result;
        }

        T& operator[](int index) {
            if (index < 0 || index >= Size) throw std::out_of_range("Index out of range");
            return Data[correctLeft + index];
        }
        const T& operator[](int index) const {
            if (index < 0 || index >= Size) throw std::out_of_range("Index out of range");
            return Data[correctLeft + index];
        }
        AdaptiveSequence& operator=(const AdaptiveSequence<T>& other) {
            if (this == &other) return *this;
            if (Data) delete [] Data;
            Size = other.Size;
            Data = new T[Size * 2]{};
            correctLeft = other.correctLeft;
            correctRight = other.correctRight;
            for (int i = 0; i < Size; i++) {
                Data[correctLeft + i] = other.Data[other.correctLeft + i];
            }
            return *this;
        }
        AdaptiveSequence& operator=(AdaptiveSequence<T>&& other) noexcept {
            if (this == &other) return *this;
            if (Data) delete [] Data;
            Data = other.Data;
            Size = other.Size;
            correctLeft = other.correctLeft;
            correctRight = other.correctRight;
            other.Data = nullptr;
            other.Size = 0;
            other.correctLeft = 0;
            other.correctRight = 0;
            return *this;
        }

        ~AdaptiveSequence() {
            if (Data) delete [] Data;
        }
    
    private:
        T* Data = nullptr;
        int Size = 0;
        int correctLeft = 0;
        int correctRight = 0;

        template <typename U>
        friend class AdaptiveSequence;
};

#endif // ADAPTIVESEQUENCE_HPP