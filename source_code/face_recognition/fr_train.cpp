#include "fr_train.h"
#include "database/personoperate.h"
#include "database/facepicoperate.h"
#include "init/varinit.h"
#include "common/csvoperate.h"
#include "entity/facepic.h"

Fr_Train::Fr_Train()
{

}

/**
 * @brief Fr_Train::face_eigen_train_save 使用特征脸方法，用多组图片进行训练，并保存训练结果
 * @param model 人脸识别器
 */
void Fr_Train::face_eigen_train_save(Ptr<FaceRecognizer> &model)
{
    PersonOperate personOperate;
    FacepicOperate facepicOperate;

    //查找所有person_id
    vector<int> persons = personOperate.selectAllPerson_id();

//    qDebug() << persons;

    vector<Mat> images;
    vector<int> labels;

    //先读取基础图库
//    CSVOperate::read_csv(images, labels);

    for(uint i = 0; i < persons.size(); i++) {
        //该person对应的所有图片
        QList<Facepic> facepics = facepicOperate.selectByPerson_id(persons[i]);
        for(int j = 0; j < facepics.size(); j++) {
            QString picPath = facepics[j].getFacepic_path();
            images.push_back(imread(picPath.toStdString(), IMREAD_GRAYSCALE));
            labels.push_back(facepics[j].getPerson_id());
        }
    }
    //开始训练
    model->train(images, labels);
    //保存训练结果
    VarInit *varInit = VarInit::getVarInit();
    string filename = varInit->getPCATrainResult().toStdString();
    model->save(filename);
}

/**
 * @brief Fr_Train::face_eigen_train_load 读取使用特征脸方法训练的训练结果文件
 * @param model 需要读取训练结果文件的人脸识别器
 */
void Fr_Train::face_eigen_train_load(Ptr<FaceRecognizer> &model)
{
    VarInit *varInit = VarInit::getVarInit();
    model->load(varInit->getPCATrainResult().toStdString());
}
