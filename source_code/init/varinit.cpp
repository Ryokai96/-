#include "varinit.h"

VarInit* VarInit::varInit = NULL;

VarInit::VarInit()
{
    projectPath = "/home/ryoukai/Ryoukai_FaceRecognition/";
    databaseFilePath = projectPath + "database/Ryoukai_FaceRecognition.db";
    basePicCsvPath = projectPath + "picture/basepic/at.csv";
    personPicPath = projectPath + "picture/person_face/";
    classifierPath = projectPath + "haarcascades/";
    PCATrainResult = projectPath + "trainfile/PCATrainResult.xml";
    cameraPath = projectPath + "camera/";
}

/**
 * @brief VarInit::getVarInit 获取程序运行所需的初始化变量使用实例
 */
VarInit *VarInit::getVarInit()
{
    if(varInit == NULL) {
        varInit = new VarInit();
    }
    return varInit;
}

QString VarInit::getProjectPath() const
{
    return projectPath;
}

QString VarInit::getDatabaseFilePath() const
{
    return databaseFilePath;
}

QString VarInit::getBasePicCsvPath() const
{
    return basePicCsvPath;
}

QString VarInit::getPersonPicPath() const
{
    return personPicPath;
}

QString VarInit::getClassifierPath() const
{
    return classifierPath;
}

QString VarInit::getPCATrainResult() const
{
    return PCATrainResult;
}

QString VarInit::getCameraPath() const
{
    return cameraPath;
}
