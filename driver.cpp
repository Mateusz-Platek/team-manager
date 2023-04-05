#include "driver.h"

Driver::Driver() : daysDriven(0)
{

}

Driver::Driver(QString pName, int pAge , int pType) : Person(pName, pAge, pType), daysDriven(0)
{

}

void Driver::setExperience(int pExperience)
{
    daysDriven = pExperience;
}

int Driver::experience()
{
    return daysDriven;
}

void Driver::work()
{
    daysDriven += 1;
}
