#ifndef FACE_PREDICT_H
#define FACE_PREDICT_H

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/face.hpp>

using namespace std;
using namespace cv;
using namespace face;

class Face_Predict
{
public:
    Face_Predict();

    static int face_predict(Ptr<FaceRecognizer> &model, vector<Mat> &images);

private:
    /**
     * @brief model 人脸识别器
     */
    Ptr<FaceRecognizer> model;
};

#endif // FACE_PREDICT_H
