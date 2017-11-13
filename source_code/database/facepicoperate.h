#ifndef FACEPICOPERATE_H
#define FACEPICOPERATE_H

#include "common/dbutil.h"
#include "entity/facepic.h"

class FacepicOperate
{
public:
    FacepicOperate();

    int createFacepicTabel(int person_id);
    int insertFacepic(int person_id, QString facepic_path);
    int selectFacepicNumber(int person_id);
    QList<Facepic> selectByPerson_id(int person_id);

private:
    DbUtil *dbUtil;
};

#endif // FACEPICOPERATE_H
