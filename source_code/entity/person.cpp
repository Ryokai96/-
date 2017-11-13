#include "person.h"

Person::Person()
{

}

int Person::getPerson_id() const
{
    return person_id;
}

void Person::setPerson_id(int value)
{
    person_id = value;
}

QString Person::getPerson_name() const
{
    return person_name;
}

void Person::setPerson_name(const QString &value)
{
    person_name = value;
}

QString Person::getPerson_age() const
{
    return person_age;
}

void Person::setPerson_age(const QString &value)
{
    person_age = value;
}

QString Person::getPerson_sex() const
{
    return person_sex;
}

void Person::setPerson_sex(const QString &value)
{
    person_sex = value;
}
