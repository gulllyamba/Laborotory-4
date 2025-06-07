#ifndef MUTABLELISTSEQUENCE_HPP
#define MUTABLELISTSEQUENCE_HPP

#include "ListSequence.hpp"
#include "../Sequence/MutableSequence.hpp"

template <typename T>
class MutableListSequence : virtual public ListSequence<T>, virtual public MutableSequence<T> {
    public:
        using value_type = T;

        MutableListSequence(const T* items, int size) : ListSequence<T>(items, size) {}
        MutableListSequence() : MutableListSequence<T>(nullptr, 0) {}
        MutableListSequence(int size) : MutableListSequence<T>(nullptr, size) {}
        MutableListSequence(const MutableListSequence<T>& other) : ListSequence<T>(other) {}
        MutableListSequence(const LinkedList<T>& other) : ListSequence<T>(other) {}

        MutableListSequence<T>& operator=(const MutableListSequence<T>& other) {
            if (this == &other) return *this;
            if (this->list) delete this->list;
            this->list = new LinkedList<T>(*other.list);
            return *this;
        }

        T Get(int index) const override {
            return this->list->Get(index);
        }
        T GetFirst() const override {
            return this->list->GetFirst();
        }
        T GetLast() const override {
            return this->list->GetLast();
        }
        int GetSize() const override {
            return this->list->GetSize();
        }

        MutableListSequence<T>* Set(int index, const T& value) override {
            return dynamic_cast<MutableListSequence<T>*>(Instance()->SetInternal(index, value));
        }
        MutableListSequence<T>* Append(const T& value) override {
            return dynamic_cast<MutableListSequence<T>*>(Instance()->AppendInternal(value));
        }
        MutableListSequence<T>* Prepend(const T& value) override {
            return dynamic_cast<MutableListSequence<T>*>(Instance()->PrependInternal(value));
        }
        MutableListSequence<T>* InsertAt(int index, const T&value) override {
            return dynamic_cast<MutableListSequence<T>*>(Instance()->InsertAtInternal(index, value));
        }
        MutableListSequence<T>* Resize(int size) override {
            return dynamic_cast<MutableListSequence<T>*>(Instance()->ResizeInternal(size));
        }
        MutableListSequence<T>* RemoveAt(int index) override {
            return dynamic_cast<MutableListSequence<T>*>(Instance()->RemoveAtInternal(index));
        }

        MutableListSequence<T>* GetSubSequence(int startIndex, int endIndex) const override {
            LinkedList<T>* temp_list = (const_cast<MutableListSequence<T>*>(this))->Instance()->list->GetSubContainer(startIndex, endIndex);
            MutableListSequence<T>* result = new MutableListSequence<T>(*temp_list);
            delete temp_list;
            return result;
        }
        MutableListSequence<T>* Concat(MutableSequence<T>* other) const override {
            LinkedList<T>* temp_list = (const_cast<MutableListSequence<T>*>(this))->Instance()->list->Concat(dynamic_cast<MutableListSequence<T>*>(other)->list);
            MutableListSequence<T>* result = new MutableListSequence<T>(*temp_list);
            delete temp_list;
            return result;
        }

        template <typename Container>
        MutableListSequence<T>* From(const Container& container) {
            Instance()->list->From(container);
            return this;
        }
        template <typename U>
        MutableListSequence<U>* Map(std::function<U(T)> f) const {
            LinkedList<U>* temp_list = (const_cast<MutableListSequence<T>*>(this))->Instance()->list->Map(f);
            MutableListSequence<U>* result = new MutableListSequence<U>(*temp_list);
            delete temp_list;
            return result;
        }
        template <typename U>
        MutableListSequence<T>* FlatMap(std::function<LinkedList<T>*(U)> f) const {
            LinkedList<U>* temp_list = (const_cast<MutableListSequence<T>*>(this))->Instance()->list->FlatMap(f);
            MutableListSequence<U>* result = new MutableListSequence<U>(*temp_list);
            delete temp_list;
            return result;
        }
        MutableListSequence<T>* Where(std::function<bool(T)> f) const {
            LinkedList<T>* temp_list = (const_cast<MutableListSequence<T>*>(this))->Instance()->list->Where(f);
            MutableListSequence<T>* result = new MutableListSequence<T>(*temp_list);
            delete temp_list;
            return result;
        }
        T Reduce(std::function<T(T, T)> f, const T& c) const {
            return (const_cast<MutableListSequence<T>*>(this))->Instance()->list->Reduce(f, c);
        }
        template <typename... Sequences>
        MutableListSequence<std::tuple<T, typename Sequences::value_type...>>* Zip(MutableSequence<T>* first, Sequences*... sequences) const {
            MutableListSequence<std::tuple<T, typename Sequences::value_type...>>* result = new MutableListSequence<std::tuple<T, typename Sequences::value_type...>>(*((const_cast<MutableListSequence<T>*>(this))->Instance()->list->Zip(dynamic_cast<MutableListSequence<T>*>(first)->list, (dynamic_cast<MutableListSequence<T>*>(sequences)->list)...)));
            return result;
        }
        template <typename... Tuples>
        std::tuple<MutableListSequence<Tuples>...>* UnZip() const {
            std::tuple<MutableListSequence<Tuples>...>* result = new std::tuple<MutableListSequence<Tuples>...>();
            for (auto it = (const_cast<MutableListSequence<T>*>(this))->begin(); it != (const_cast<MutableListSequence<T>*>(this))->end(); ++it) {
                auto unzip = [&]<size_t... Is>(std::index_sequence<Is...>) {
                    ((std::get<Is>(*result).Append(std::get<Is>(*it))), ...);
                };
                unzip(std::index_sequence_for<Tuples...>{});
            }
            return result;
        }

        virtual ~MutableListSequence() {
            if (this->list) delete this->list;
        }

    private:
        MutableListSequence<T>* Instance() override {
            return this;
        }
};

#endif // MUTABLELISTSEQUENCE_HPP