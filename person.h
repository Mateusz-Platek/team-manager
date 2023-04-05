#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person
{
protected:
    QString name;
    int age;
    int type;
public:
    /**
     * @brief Defualt Person constructor
    */
    Person();
    /**
     * @brief Person constructor
     * @param Name of the object
     * @param Age of the object
     * @param Type of the object
    */
    Person(QString pName, int pAge, int pType);
    virtual ~Person() = default;
    /**
     * @brief Function sets name
     * @param Name to set
    */
    void setName(QString pName);
    /**
     * @brief Function returns name variable
     * @return Name variable
    */
    QString getName();
    /**
     * @brief Function sets age
     * @param Age to set
    */
    void setAge(int pAge);
    /**
     * @brief Function returns age variable
     * @return Age variable
    */
    int getAge();
    /**
     * @brief Function returns type variable
     * @return Type variable
    */
    int getType();
    /**
     * @brief Vritual function
     * @param Experience to set
    */
    virtual void setExperience(int pExperience) = 0;
    /**
     * @brief Vritual function
     * @return Experience of object
    */
    virtual int experience() = 0;
    /**
     * @brief Vritual function
    */
    virtual void work() = 0;
    /**
     * @brief Function divides age by number
     * @param Value of number
     * @return Age divided by number
    */
    double divideAge(int number);
    /**
     * @brief Function divides age by number
     * @param Value of number
     * @return Age divided by number
    */
    double divideAge(double number);
    /**
     * @brief Function multiplays age by number
     * @param Value of number
     * @return Age multiplayed by number
    */
    template <typename T>
    T multiplayAge(T number);
};
/**
 * @brief Overload of + operator
 * @param Integer variable
 * @param Person object
 * @return Sum of integer variable and experience of person object
*/
int operator+(int lhs, Person &rhs);
/**
 * @brief Overload of + operator
 * @param Double variable
 * @param Person object
 * @return Sum of double variable and experience of person object
*/
double operator+(double lhs, Person &rhs);

#endif // PERSON_H
