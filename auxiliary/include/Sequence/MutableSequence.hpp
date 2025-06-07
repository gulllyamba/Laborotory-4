#ifndef MUTABLESEQUENCE_HPP
#define MUTABLESEQUENCE_HPP

#include "Sequence.hpp"

template <typename T>
class MutableSequence : public Sequence<T>{
    public:
        virtual MutableSequence<T>* Set(int index, const T& value) = 0;
        virtual MutableSequence<T>* Append(const T& value) = 0;
        virtual MutableSequence<T>* Prepend(const T& value) = 0;
        virtual MutableSequence<T>* InsertAt(int index, const T&value) = 0;
        virtual MutableSequence<T>* Resize(int size) = 0;
        virtual MutableSequence<T>* RemoveAt(int index) = 0;

        virtual MutableSequence<T>* GetSubSequence(int startIndex, int endIndex) const = 0;
        virtual MutableSequence<T>* Concat(MutableSequence<T>* other) const = 0;

        virtual ~MutableSequence() = default;
};

#endif // MUTABLESEQUENCE_HPP 