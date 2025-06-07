#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>

struct PersonID {
    PersonID(int series, int number) : series(series), number(number) {}
    PersonID() : PersonID(0, 0) {}
    int series;
    int number;
};

class Person {
    public:
        Person(std::string name, std::string surname, std::string lastname, int age, int series, int number) {
            Name = name;
            Surname = surname;
            Lastname = lastname;
            Age = age;
            id = PersonID(series, number);
        }
        Person() : Person("", "", "", 0, 0, 0) {}

        std::string GetName() const {
            return Name;
        }
        std::string GetSurname() const {
            return Surname;
        }
        std::string GetLastName() const {
            return Lastname;
        }
        int GetAge() const {
            return Age;
        }
        PersonID GetID() const {
            return id;
        }

        void SetName(std::string name) {
            Name = name;
        }
        void SetSurname(std::string surname) {
            Surname = surname;
        }
        void SetLastname(std::string lastname) {
            Lastname = lastname;
        }
        void SetAge(int age) {
            Age = age;
        }
        void SetID(int series, int number) {
            id = PersonID(series, number);
        }

        bool operator<(const Person& other) const {
            return this->Age < other.Age;
        }
        bool operator>(const Person& other) const {
            return other < *this;
        }
        bool operator<=(const Person& other) const {
            return !(*this > other);
        }
        bool operator>=(const Person& other) const {
            return !(*this < other);
        }

    private:
        std::string Name;
        std::string Surname;
        std::string Lastname;
        int Age;
        PersonID id;
};

#endif // PERSON_HPP