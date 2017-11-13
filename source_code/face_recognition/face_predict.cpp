#include "face_predict.h"
#include <QDebug>
#include <opencv2/face/facerec.hpp>
#include <opencv2/ml/ml.hpp>

Face_Predict::Face_Predict()
{

}

/**
 * @brief Face_Predict::face_predict 识别人脸
 * @param model 人脸识别器
 * @param images 要识别的图片
 * @return 识别结果，识别失败返回-1，识别成功返回label
 */
int Face_Predict::face_predict(Ptr<FaceRecognizer> &model, vector<Mat> &images)
{
    int result;

    //用于计数第一次识别成功时的识别结果出现的次数
    int number = 0;
    //用于记录识别结果
    int predictResult = -2;

    for(uint i = 0; i < images.size(); i++) {
        //用于保存本次识别结果
        int predictedLabel = -1;

        double confidence = 0.0;

        model->predict(images[i], predictedLabel, confidence);
        qDebug() << "predictedLabel: " << predictedLabel;
        qDebug() << "confidence: " << confidence;

        //当confidence < 5000时代表此帧识别成功，number为0时代表第一次识别成功，predictedLabel若为1~15代表识别为基础图片库中的图片
        if(confidence < 5000 && number == 0 && predictedLabel > 15) {
            //记录第一次识别成功时的识别结果
            predictResult = predictedLabel;
            number ++;
        }

        //记录第一次识别成功时的识别结果出现的次数
        if(predictResult == predictedLabel && confidence < 5000) {
            number++;
        }
    }

    //若number大于等于12,代表识别成功
    if(number >= 12) {
        result = predictResult;
    } else {
        result = -1;
    }
    return result;
}
