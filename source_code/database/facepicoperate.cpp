#include "facepicoperate.h"

FacepicOperate::FacepicOperate()
{
    this->dbUtil = DbUtil::getDbUtil();
}

/**
 * @brief FacepicOperate::createFacepicTabel 新建与person对应的facepic表
 * @param person_id person_id
 * @return 返回建表结果，-1代表建表错误，1代表建表成功
 */
int FacepicOperate::createFacepicTabel(int person_id)
{
    QSqlQuery query;

    QString tableName = "facepic" + QString::number(person_id);

    if(!query.exec("CREATE TABLE " + tableName + " ( \
                  `facepic_id`	 INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, \
                  `person_id`	 INTEGER NOT NULL, \
                  `facepic_path` TEXT NOT NULL,\
                  FOREIGN KEY(`person_id`) REFERENCES	person(`person_id`))")) {
        qDebug() << "facepic建表失败";
        qDebug() << query.lastError().text();
        return -1;
    }

    return 1;
}

/**
 * @brief FacepicOperate::insertFacepic 插入数据到facepic表
 * @param person_id person_id
 * @return 返回插入结果，插入错误返回-1，插入成功返回1
 */
int FacepicOperate::insertFacepic(int person_id, QString facepic_path)
{
    QSqlQuery query;
    QString tableName = "facepic" + QString::number(person_id);

    query.prepare("insert into " + tableName + "(person_id, facepic_path) values(:person_id, :facepic_path)");
    query.bindValue(":person_id", QVariant(person_id));
    query.bindValue(":facepic_path", QVariant(facepic_path));

    if(!query.exec()) {
        qDebug() << "facepic插入失败";
        qDebug() << query.lastError().text();
        return -1;
    }

    query.clear();
    query.exec("commit");

    return 1;
}

/**
 * @brief FacepicOperate::selectFacepicNumber 查找facepic总数
 * @param person_id person_id
 * @return 返回查找结果，查找错误返回-1，查找成功返回facepic总数
 */
int FacepicOperate::selectFacepicNumber(int person_id)
{
    QSqlQuery query;

    QString tableName = "facepic" + QString::number(person_id);

    query.prepare("select last_insert_rowid() from " + tableName);

    if(!query.exec()) {
        qDebug() << "查找facepic总数失败";
        qDebug() << query.lastError().text();
        return -1;
    }

    query.next();
    QSqlRecord record = query.record();

    int facepicNumber = record.value("last_insert_rowid()").toInt();

    return facepicNumber;
}

/**
* @brief FacepicOperate::selectByPerson_id 通过person_id查找facepic
* @param person_id
* @return 查找结果，查找失败返回NULL，查找成功返回查找到的所有facepic
*/
QList<Facepic> FacepicOperate::selectByPerson_id(int person_id)
{
    QSqlQuery query;

    QString tableName = "facepic" + QString::number(person_id);
    query.prepare("select facepic_id, person_id, facepic_path from " + tableName + " where person_id = :person_id");
    query.bindValue(":person_id", QVariant(person_id));

    QList<Facepic> facepics;

    if(!query.exec()) {
        qDebug() << "通过person_id查找facepic失败";
        qDebug() << query.lastError().text();
        return facepics;
    }

    while(query.next()) {
        Facepic facepic;
        QSqlRecord record = query.record();
        facepic.setFacepic_id(record.value("facepic_id").toInt());
        facepic.setPerson_id(record.value("person_id").toInt());
        facepic.setFacepic_path(record.value("facepic_path").toString());
        facepics.append(facepic);
    }

    return facepics;
}
