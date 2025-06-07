#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stdexcept>
#include <memory>

template <typename T, bool IsConst>
class IIterator {
    public:
        using value_type = T;
        using pointer = std::conditional_t<IsConst, const T*, T*>;
        using reference = std::conditional_t<IsConst, const T&, T&>;
        using difference_type = std::ptrdiff_t;

        virtual void MoveNext() = 0;
        virtual reference Current() = 0;
        virtual bool HasNext() const = 0;
        virtual ~IIterator() = default;
};

template <typename T>
class IEnumerable {
    public:
        virtual std::unique_ptr<IIterator<T, false>> GetIterator() = 0;
        virtual std::unique_ptr<IIterator<T, true>> GetConstIterator() const = 0;
        virtual ~IEnumerable() = default;
};

#endif // ITERATOR_HPP