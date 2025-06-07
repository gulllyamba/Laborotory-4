#ifndef IMMUTABLESEQUENCE_HPP
#define IMMUTABLESEQUENCE_HPP

#include "Sequence.hpp"

template <typename T>
class ImmutableSequence : public Sequence<T>{
    public:
        virtual ImmutableSequence<T>* Set(int index, const T& value) const = 0;
        virtual ImmutableSequence<T>* Append(const T& value) const = 0;
        virtual ImmutableSequence<T>* Prepend(const T& value) const = 0;
        virtual ImmutableSequence<T>* InsertAt(int index, const T&value) const = 0;
        virtual ImmutableSequence<T>* Resize(int size) const = 0;
        virtual ImmutableSequence<T>* RemoveAt(int index) const = 0;

        virtual ImmutableSequence<T>* GetSubSequence(int startIndex, int endIndex) const = 0;
        virtual ImmutableSequence<T>* Concat(ImmutableSequence <T>* other) const = 0;
        
        virtual ~ImmutableSequence() = default;
};

#endif // IMMUTABLESEQUENCE_HPP