#ifndef IMMUTABLEARRAYSEQUENCE
#define IMMUTABLEARRAYSEQUENCE

#include "ArraySequence.hpp"
#include "../Sequence/ImmutableSequence.hpp"

template <typename T>
class ImmutableArraySequence : virtual public ArraySequence<T>, virtual public ImmutableSequence<T> {
    public:
        using value_type = T;

        ImmutableArraySequence(const T* items, int size) : ArraySequence<T>(items, size) {}
        ImmutableArraySequence() : ImmutableArraySequence<T>(nullptr, 0) {}
        ImmutableArraySequence(int size) : ImmutableArraySequence<T>(nullptr, size) {}
        ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequence<T>(other) {}
        ImmutableArraySequence(const DynamicArray<T>& other) : ArraySequence<T>(other) {}

        ImmutableArraySequence<T>& operator=(const ImmutableArraySequence<T>& other) {
            if (this == &other) return *this;
            delete this->array;
            this->array = new DynamicArray<T>(*other.array);
            return *this;
        }

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

        ImmutableArraySequence<T>* Reserve(int newCapacity) const {
            return dynamic_cast<ImmutableArraySequence<T>*>((const_cast<ImmutableArraySequence<T>*>(this))->Instance()->ReserveInternal(newCapacity));
        }
        ImmutableArraySequence<T>* Set(int index, const T& value) const override {
            return dynamic_cast<ImmutableArraySequence<T>*>((const_cast<ImmutableArraySequence<T>*>(this))->Instance()->SetInternal(index, value));
        }
        ImmutableArraySequence<T>* Append(const T& value) const override {
            return dynamic_cast<ImmutableArraySequence<T>*>((const_cast<ImmutableArraySequence<T>*>(this))->Instance()->AppendInternal(value));
        }
        ImmutableArraySequence<T>* Prepend(const T& value) const override {
            return dynamic_cast<ImmutableArraySequence<T>*>((const_cast<ImmutableArraySequence<T>*>(this))->Instance()->PrependInternal(value));
        }
        ImmutableArraySequence<T>* InsertAt(int index, const T& value) const override {
            return dynamic_cast<ImmutableArraySequence<T>*>((const_cast<ImmutableArraySequence<T>*>(this))->Instance()->InsertAtInternal(index, value));
        }
        ImmutableArraySequence<T>* Resize(int size) const override {
            return dynamic_cast<ImmutableArraySequence<T>*>((const_cast<ImmutableArraySequence<T>*>(this))->Instance()->ResizeInternal(size));
        }
        ImmutableArraySequence<T>* RemoveAt(int index) const override {
            return dynamic_cast<ImmutableArraySequence<T>*>((const_cast<ImmutableArraySequence<T>*>(this))->Instance()->RemoveAtInternal(index));
        }

        ImmutableArraySequence<T>* GetSubSequence(int startIndex, int endIndex) const override {
            DynamicArray<T>* temp_arr = this->array->GetSubContainer(startIndex, endIndex);
            ImmutableArraySequence<T>* temp = (const_cast<ImmutableArraySequence<T>*>(this))->Instance();
            temp->array = temp_arr;
            return temp;
        }
        ImmutableArraySequence<T>* Concat(ImmutableSequence <T>* other) const override {
            DynamicArray<T>* temp_arr = this->array->Concat(dynamic_cast<ImmutableArraySequence<T>*>(other)->array);
            ImmutableArraySequence<T>* temp = (const_cast<ImmutableArraySequence<T>*>(this))->Instance();
            temp->array = temp_arr;
            return temp;
        }

        template <typename Container>
        ImmutableArraySequence<T>* From(const Container& container) const {
            DynamicArray<T>* temp_arr = this->array->From(container);
            ImmutableArraySequence<T>* temp = (const_cast<ImmutableArraySequence<T>*>(this))->Instance();
            temp->array = temp_arr;
            return temp;
        }
        template <typename U>
        ImmutableArraySequence<U>* Map(std::function<U(T)> f) const {
            DynamicArray<U>* temp_arr = this->array->Map(f);
            ImmutableArraySequence<U>* temp = new ImmutableArraySequence<U>(*temp_arr);
            return temp;
        }
        template <typename U>
        ImmutableArraySequence<T>* FlatMap(std::function<DynamicArray<T>*(U)> f) const {
            DynamicArray<T>* temp_arr = this->array->FlatMap(f);
            ImmutableArraySequence<T>* temp = (const_cast<ImmutableArraySequence<T>*>(this))->Instance();
            temp->array = temp_arr;
            return temp;
        }
        ImmutableArraySequence<T>* Where(std::function<bool(T)> f) const {
            DynamicArray<T>* temp_arr = this->array->Where(f);
            ImmutableArraySequence<T>* temp = (const_cast<ImmutableArraySequence<T>*>(this))->Instance();
            temp->array = temp_arr;
            return temp;
        }
        T Reduce(std::function<T(T, T)> f, const T& c) const {
            return (const_cast<ImmutableArraySequence<T>*>(this))->array->Reduce(f, c);
        }
        template <typename... Sequences>
        ImmutableArraySequence<std::tuple<T, typename Sequences::value_type...>>* Zip(ImmutableSequence<T>* first, Sequences*... sequences) const {
            ImmutableArraySequence<std::tuple<T, typename Sequences::value_type...>>* result = new ImmutableArraySequence<std::tuple<T, typename Sequences::value_type...>>(*((const_cast<ImmutableArraySequence<T>*>(this))->array->Zip(dynamic_cast<ImmutableArraySequence<T>*>(first)->array, (dynamic_cast<ImmutableArraySequence<T>*>(sequences)->array)...)));
            return result;
        }
        template <typename... Tuples>
        std::tuple<ImmutableArraySequence<Tuples>...>* UnZip() const {
            std::tuple<ImmutableArraySequence<Tuples>...>* result = new std::tuple<ImmutableArraySequence<Tuples>...>();
            for (auto it = this->cbegin(); it != this->cend(); ++it) {
                auto unzip = [&]<size_t... Is>(std::index_sequence<Is...>) {
                    ((std::get<Is>(*result).App(std::get<Is>(*it))), ...);
                };
                unzip(std::index_sequence_for<Tuples...>{});
            }
            return result;
        }

        ImmutableArraySequence<T>* App(const T& value) {
            return dynamic_cast<ImmutableArraySequence<T>*>(this->AppendInternal(value));
        }

        ~ImmutableArraySequence() override {
            if (this->array) delete this->array;
        }

    private:
        ImmutableArraySequence<T>* Instance() override {
            return new ImmutableArraySequence<T>(*this);
        }
};

#endif // IMMUTABLEARRAYSEQUENCE
