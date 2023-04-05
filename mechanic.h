#ifndef MECHANIC_H
#define MECHANIC_H

#include "person.h"

class Mechanic : public Person
{
    int carsFixed;
public:
    /**
     * @brief Defualt Mechanic constructor
    */
    Mechanic();
    /**
     * @brief Mechanic constructor
     * @param Name of the object
     * @param Age of the object
     * @param Type of the object
    */
    Mechanic(QString pName, int pAge, int pType = 1);
    /**
     * @brief Function sets value of variable carsFixed
     * @param Value of carsFixed to set
    */
    void setExperience(int pExperience);
    /**
     * @brief Function returns carsFixed variable
     * @return CarsFixed variable
    */
    int experience();
    /**
     * @brief Function increase variable carsFixed by 1
    */
    void work();
};

#endif // MECHANIC_H
