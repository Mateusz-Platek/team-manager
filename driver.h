#ifndef DRIVER_H
#define DRIVER_H

#include "person.h"

class Driver : public Person
{
    int daysDriven;
public:
    /**
     * @brief Default Driver constructor
    */
    Driver();
    /**
     * @brief Driver constructor
     * @param Name of the object
     * @param Age of the object
     * @param Type of the object
    */
    Driver(QString pName, int pAge, int pType = 0);
    /**
     * @brief Function sets value of variable daysDriven
     * @param Value of daysDriven to set
    */
    void setExperience(int pExperience);
    /**
     * @brief Function returns daysDriven variable
     * @return DaysDriven variable
    */
    int experience();
    /**
     * @brief Function increase variable daysDriven by 1
    */
    void work();
};

#endif // DRIVER_H
