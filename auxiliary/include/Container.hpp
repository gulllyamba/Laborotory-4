#ifndef CONTAINER_HPP
#define CONTAINER_HPP

template <typename T>
class Container {
    public:
        virtual T GetFirst() const = 0;
        virtual T GetLast() const = 0;
        virtual T Get(int index) const = 0;
        virtual int GetSize() const = 0;

        virtual void Append(const T& value) = 0;
        virtual void Append(const T&& value) = 0;
        virtual void Prepend(const T& value) = 0;
        virtual void Prepend(const T&& value) = 0;
        virtual void Set(int index, const T& value) = 0;
        virtual void Set(int index, const T&& value) = 0;
        virtual void InsertAt(int index, const T& value) = 0;
        virtual void InsertAt(int index, const T&& value) = 0;
        virtual void Resize(int size) = 0;
        virtual void RemoveAt(int index) = 0;

        virtual Container<T>* GetSubContainer(int startIndex, int endIndex) const = 0;
        virtual Container<T>* Concat(Container<T>* other) const = 0;
        virtual Container<T>* Clutch(Container<T>* other) = 0;

        virtual ~Container() = default;
};

#endif // CONTAINER_HPP