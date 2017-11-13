#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person
{
public:
    Person();

    int getPerson_id() const;
    void setPerson_id(int value);

    QString getPerson_name() const;
    void setPerson_name(const QString &value);

    QString getPerson_age() const;
    void setPerson_age(const QString &value);

    QString getPerson_sex() const;
    void setPerson_sex(const QString &value);

private:
    int person_id;
    QString person_name;
    QString person_age;
    QString person_sex;
};

#endif // PERSON_H
