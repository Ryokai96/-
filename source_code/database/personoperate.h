#ifndef PERSONOPERATE_H
#define PERSONOPERATE_H

#include <iostream>
#include "common/dbutil.h"
#include "entity/person.h"

using namespace std;

class PersonOperate
{
public:
    PersonOperate();

    int addPerson(Person person);
    int isPerson_nameExist(QString name);
    QString selectPerson_nameById(int person_id);
    vector<int> selectAllPerson_id();

private:
    DbUtil *dbUtil;
};

#endif // PERSONOPERATE_H
