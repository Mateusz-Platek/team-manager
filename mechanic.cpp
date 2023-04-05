#include "mechanic.h"

Mechanic::Mechanic() : carsFixed(0)
{

}

Mechanic::Mechanic(QString pName, int pAge, int pType) : Person(pName, pAge, pType), carsFixed(0)
{

}

void Mechanic::setExperience(int pExperience)
{
    carsFixed = pExperience;
}

int Mechanic::experience()
{
    return carsFixed;
}

void Mechanic::work()
{
    carsFixed += 1;
}
