#ifndef FACE_DETECTION_H
#define FACE_DETECTION_H

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace std;
using namespace cv;

class Face_Detection
{
public:
    Face_Detection();
    void faceDetection(Mat& image, vector<Rect>& recs);
    void eyeDetection(Mat& image, vector<Rect>& recs);

private:
    /**
     * @brief cas 人脸分类器
     */
    CascadeClassifier faceCas;
    /**
     * @brief eyeCas 眼睛分类器
     */
    CascadeClassifier eyeCas;
};

#endif // FACE_DETECTION_H
