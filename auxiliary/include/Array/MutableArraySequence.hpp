#ifndef MUTABLEARRAYSEQUENCE
#define MUTABLEARRAYSEQUENCE

#include "ArraySequence.hpp"
#include "../Sequence/MutableSequence.hpp"

template <typename T>
class MutableArraySequence : virtual public ArraySequence<T>, virtual public MutableSequence<T> {
    public:
        using value_type = T;

        MutableArraySequence(const T* items, int size) : ArraySequence<T>(items, size) {}
        MutableArraySequence() : MutableArraySequence<T>(nullptr, 0) {}
        MutableArraySequence(int size) : MutableArraySequence<T>(nullptr, size) {}
        MutableArraySequence(const MutableArraySequence<T>& other) : ArraySequence<T>(other) {}
        MutableArraySequence(const DynamicArray<T>& other) : ArraySequence<T>(other) {}

        MutableArraySequence<T>& operator=(const MutableArraySequence<T>& other) {
            if (this == &other) return *this;
            if (this->array) delete this->array;
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

        MutableArraySequence<T>* Reserve(int newCapacity) {
            return dynamic_cast<MutableArraySequence<T>*>(Instance()->ReserveInternal(newCapacity));
        }
        MutableArraySequence<T>* Set(int index, const T& value) override {
            return dynamic_cast<MutableArraySequence<T>*>(Instance()->SetInternal(index, value));
        }
        MutableArraySequence<T>* Append(const T& value) override {
            return dynamic_cast<MutableArraySequence<T>*>(Instance()->AppendInternal(value));
        }
        MutableArraySequence<T>* Prepend(const T& value) override {
            return dynamic_cast<MutableArraySequence<T>*>(Instance()->PrependInternal(value));
        }
        MutableArraySequence<T>* InsertAt(int index, const T&value) override {
            return dynamic_cast<MutableArraySequence<T>*>(Instance()->InsertAtInternal(index, value));
        }
        MutableArraySequence<T>* Resize(int size) override {
            return dynamic_cast<MutableArraySequence<T>*>(Instance()->ResizeInternal(size));
        }
        MutableArraySequence<T>* RemoveAt(int index) override {
            return dynamic_cast<MutableArraySequence<T>*>(Instance()->RemoveAtInternal(index));
        }

        MutableArraySequence<T>* GetSubSequence(int startIndex, int endIndex) const override {
            DynamicArray<T>* temp_arr = (const_cast<MutableArraySequence<T>*>(this))->Instance()->array->GetSubContainer(startIndex, endIndex);
            MutableArraySequence<T>* temp = new MutableArraySequence<T>(*temp_arr);
            delete temp_arr;
            return temp;
        }
        MutableArraySequence<T>* Concat(MutableSequence <T>* other) const override {
            DynamicArray<T>* temp_arr = (const_cast<MutableArraySequence<T>*>(this))->Instance()->array->Concat(dynamic_cast<MutableArraySequence<T>*>(other)->array);
            MutableArraySequence<T>* temp = new MutableArraySequence<T>(*temp_arr);
            delete temp_arr;
            return temp;
        }

        template <typename Container>
        MutableArraySequence<T>* From(const Container& container) {
            Instance()->array->From(container);
            return this;
        }
        template <typename U>
        MutableArraySequence<U>* Map(std::function<U(T)> f) const {
            DynamicArray<U>* temp_arr = (const_cast<MutableArraySequence<T>*>(this))->Instance()->array->Map(f);
            MutableArraySequence<U>* temp = new MutableArraySequence<U>(*temp_arr);
            delete temp_arr;
            return temp;
        }
        template <typename U>
        MutableArraySequence<T>* FlatMap(std::function<DynamicArray<T>*(U)> f) const {
            DynamicArray<U>* temp_arr = (const_cast<MutableArraySequence<T>*>(this))->Instance()->array->FlatMap(f);
            MutableArraySequence<U>* temp = new MutableArraySequence<U>(*temp_arr);
            delete temp_arr;
            return temp;
        }
        MutableArraySequence<T>* Where(std::function<bool(T)> f) const {
            DynamicArray<T>* temp_arr = (const_cast<MutableArraySequence<T>*>(this))->Instance()->array->Where(f);
            MutableArraySequence<T>* temp = new MutableArraySequence<T>(*temp_arr);
            delete temp_arr;
            return temp;
        }
        T Reduce(std::function<T(T, T)> f, const T& c) const {
            return (const_cast<MutableArraySequence<T>*>(this))->Instance()->array->Reduce(f, c);
        }
        template <typename... Sequences>
        MutableArraySequence<std::tuple<T, typename Sequences::value_type...>>* Zip(MutableSequence<T>* first, Sequences*... sequences) const {
            MutableArraySequence<std::tuple<T, typename Sequences::value_type...>>* result = new MutableArraySequence<std::tuple<T, typename Sequences::value_type...>>(*((const_cast<MutableArraySequence<T>*>(this))->Instance()->array->Zip(dynamic_cast<MutableArraySequence<T>*>(first)->array, (dynamic_cast<MutableArraySequence<T>*>(sequences)->array)...)));
            return result;
        }
        template <typename... Tuples>
        std::tuple<MutableArraySequence<Tuples>...>* UnZip() const {
            std::tuple<MutableArraySequence<Tuples>...>* result = new std::tuple<MutableArraySequence<Tuples>...>();
            for (auto it = (const_cast<MutableArraySequence<T>*>(this))->begin(); it != (const_cast<MutableArraySequence<T>*>(this))->end(); ++it) {
                auto unzip = [&]<size_t... Is>(std::index_sequence<Is...>) {
                    ((std::get<Is>(*result).Append(std::get<Is>(*it))), ...);
                };
                unzip(std::index_sequence_for<Tuples...>{});
            }
            return result;
        }

        ~MutableArraySequence() override {
            if (this->array) delete this->array;
        }

    private:
        MutableArraySequence<T>* Instance() override {
            return this;
        }
};

#endif // MUTABLEARRAYSEQUENCE
