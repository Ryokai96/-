#ifndef FACEPIC_H
#define FACEPIC_H

#include <QString>

class Facepic
{
public:
    Facepic();

    int getFacepic_id() const;
    void setFacepic_id(int value);

    int getPerson_id() const;
    void setPerson_id(int value);

    QString getFacepic_path() const;
    void setFacepic_path(const QString &value);

private:
    int facepic_id;
    int person_id;
    QString facepic_path;
};

#endif // FACEPIC_H
