#include "personoperate.h"

PersonOperate::PersonOperate()
{
    this->dbUtil = DbUtil::getDbUtil();
}

/**
 * @brief PersonOperate::addPerson 往person表中添加一行数据
 * @param Person person数据
 * @return 添加结果，操作失败返回-1，操作成功返回person_id
 */
int PersonOperate::addPerson(Person person)
{
    QSqlQuery query;

    query.prepare("insert into person(person_name, person_age, person_sex) values(:name, :age, :sex)");
    query.bindValue(":name", QVariant(person.getPerson_name()));
    query.bindValue(":age", QVariant(person.getPerson_age()));
    query.bindValue(":sex", QVariant(person.getPerson_sex()));

    if(!query.exec()) {
        qDebug() << "添加person信息失败";
        qDebug() << query.lastError().text();
        return -1;
    }

    query.clear();
    query.exec("commit");
    query.clear();

    //返回新添加的person_id
    query.prepare("select last_insert_rowid() from person");
    query.exec();
    query.next();
    QSqlRecord record = query.record();
    int person_id = record.value("last_insert_rowid()").toInt();

    return person_id;
}

/**
 * @brief PersonOperate::isPerson_nameExist 查找姓名是否存在
 * @param name 姓名
 * @return 查找结果，查找错误返回-1，未找到返回0，找到返回person_id
 */
int PersonOperate::isPerson_nameExist(QString name)
{
    QSqlQuery query;
    query.prepare("select person_id from person where name = :name");
    query.bindValue(":name", QVariant(name));

    if(!query.exec()) {
        qDebug() << "查找person_name失败";
        qDebug() << query.lastError().text();
        return -1;
    }

    //未找到
    if(!query.next()) {
        return 0;
    }

    QSqlRecord record = query.record();
    int person_id = record.value("person_id").toInt();

    return person_id;
}

/**
 * @brief PersonOperate::selectPerson_nameById 通过person_id查找person_name
 * @param person_id person_id
 * @return 查找结果，查找错误或未找到返回NULL，找到返回person_name
 */
QString PersonOperate::selectPerson_nameById(int person_id)
{
    QSqlQuery query;
    query.prepare("select person_name from person where person_id = :person_id");
    query.bindValue(":person_id", QVariant(person_id));

    if(!query.exec()) {
        qDebug() << "通过person_id查找person_name失败";
        qDebug() << query.lastError().text();
        return NULL;
    }

    //未找到
    if(!query.next()) {
        return NULL;
    }

    QSqlRecord record = query.record();
    QString person_name = record.value("person_name").toString();

    return person_name;
}

/**
 * @brief PersonOperate::selectAllPerson_id 查找所有的person_id
 * @return 查找结果，查找成功返回所有的person_id，查找失败返回NULL
 */
vector<int> PersonOperate::selectAllPerson_id()
{
    QSqlQuery query;
    query.prepare("select person_id from person");

    vector<int> person_ids;

    if(!query.exec()) {
        qDebug() << "查找所有的person_id失败";
        qDebug() << query.lastError().text();
        return person_ids;
    }

    while(query.next()) {
        QSqlRecord record = query.record();
        int person_id = record.value("person_id").toInt();
        person_ids.push_back(person_id);
    }

    return person_ids;
}
