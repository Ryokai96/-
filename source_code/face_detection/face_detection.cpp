#include "face_detection.h"
#include "init/varinit.h"

Face_Detection::Face_Detection()
{
    VarInit* varInit = VarInit::getVarInit();
    faceCas.load(QString(varInit->getClassifierPath() + "haarcascade_frontalface_alt2.xml").toStdString());
    eyeCas.load(QString(varInit->getClassifierPath() + "haarcascade_eye_tree_eyeglasses.xml").toStdString());
}

/**
 * @brief Face_Detection::faceDetection 检测人脸所在矩形
 * @param image 要检测的图片
 * @param recs 人脸所在的矩形们
 */
void Face_Detection::faceDetection(Mat &image, vector<Rect> &recs)
{
    faceCas.detectMultiScale(image, recs, 1.1, 6, 0, Size(50, 50));
}

/**
 * @brief Face_Detection::eyeDetection 检测眼睛所在矩形
 * @param image 要检测的图片
 * @param recs  眼睛所在的矩形们
 */
void Face_Detection::eyeDetection(Mat &image, vector<Rect> &recs)
{
    eyeCas.detectMultiScale(image, recs, 1.1, 6, 0, Size(50, 50));
}
