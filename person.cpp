#include "person.h"

Person::Person() : name(""), age(0)
{

}

Person::Person(QString pName, int pAge, int pType) : name(pName), age(pAge), type(pType)
{

}

void Person::setName(QString pName)
{
    name = pName;
}

QString Person::getName()
{
    return name;
}

void Person::setAge(int pAge)
{
    age = pAge;
}

int Person::getAge()
{
    return age;
}

int Person::getType()
{
    return type;
}

double Person::divideAge(int number)
{
    return (double)age / number;
}

double Person::divideAge(double number)
{
    return age / number;
}

int operator+(int lhs, Person &rhs) {
    return lhs + rhs.experience();
}

double operator+(double lhs, Person &rhs) {
    return lhs + rhs.experience();
}

template<typename T>
T Person::multiplayAge(T number)
{
    return age * number;
}
