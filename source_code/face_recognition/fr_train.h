#ifndef FR_TRAIN_H
#define FR_TRAIN_H

#include <iostream>
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/face/facerec.hpp>

using namespace std;
using namespace cv;
using namespace face;

class Fr_Train
{
public:
    Fr_Train();

    static void face_eigen_train_save(Ptr<FaceRecognizer> &model);
    static void face_eigen_train_load(Ptr<FaceRecognizer> &model);
};

#endif // FR_TRAIN_H
