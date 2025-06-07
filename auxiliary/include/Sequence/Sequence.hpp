#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <string>
#include <functional>

template <typename T>
class Sequence {
    public:
        virtual T GetFirst() const = 0;
        virtual T GetLast() const = 0;
        virtual T Get(int index) const = 0;
        virtual int GetSize() const = 0;
        
        virtual ~Sequence()  = default;
};

#endif // SEQUENCE_HPP