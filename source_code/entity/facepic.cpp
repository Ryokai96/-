#include "facepic.h"

Facepic::Facepic()
{

}

int Facepic::getFacepic_id() const
{
    return facepic_id;
}

void Facepic::setFacepic_id(int value)
{
    facepic_id = value;
}

int Facepic::getPerson_id() const
{
    return person_id;
}

void Facepic::setPerson_id(int value)
{
    person_id = value;
}

QString Facepic::getFacepic_path() const
{
    return facepic_path;
}

void Facepic::setFacepic_path(const QString &value)
{
    facepic_path = value;
}
