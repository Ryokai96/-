#ifndef VARINIT_H
#define VARINIT_H

#include <QString>

class VarInit
{
public:
    VarInit();
    static VarInit* getVarInit();

    QString getProjectPath() const;

    QString getDatabaseFilePath() const;

    QString getBasePicCsvPath() const;

    QString getPersonPicPath() const;

    QString getClassifierPath() const;

    QString getPCATrainResult() const;

    QString getCameraPath() const;

private:
    static VarInit *varInit;

    /**
     * @brief projectInPath 程序所在路径
     */
    QString projectInPath;
    /**
     * @brief programPath 程序根路径
     */
    QString projectPath;
    /**
     * @brief databaseFilePath 数据库文件路径
     */
    QString databaseFilePath;
    /**
     * @brief basePicCsvPath 基础图库csv文件路径
     */
    QString basePicCsvPath;
    /**
     * @brief personPicPath 录入人脸库根路径
     */
    QString personPicPath;
    /**
     * @brief classifierPath 人脸分类器根路径
     */
    QString classifierPath;
    /**
     * @brief PCATrainResult PCA方式(特征脸)识别训练结果文件路径
     */
    QString PCATrainResult;
    /**
     * @brief cameraPath 照片库路径
     */
    QString cameraPath;
};

#endif // VARINIT_H
