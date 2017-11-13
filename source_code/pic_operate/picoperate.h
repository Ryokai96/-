#ifndef PICOPERATE_H
#define PICOPERATE_H

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "face_detection/face_detection.h"

using namespace std;
using namespace cv;

class PicOperate
{
public:
    PicOperate();

    static PicOperate* getPicOperate();

    Mat getImage(Mat srcImage);

    void setDrawRec(bool value);

    bool getDrawRec() const;

    void setRecs(const vector<Rect> &value);

    static void toGrayAndResize(Mat &srcImage, Mat &objImage, int weight = 320, int height = 243);

    void setUnitPic(const Mat &value);

    void setDrawUnitPic(bool value);

    bool getDrawUnitPic() const;

    bool getDrawPersonName() const;
    void setDrawPersonName(bool value);

    void setPerson_names(const vector<string> &value);

private:
    /**
     * @brief picOperate 用于操作图片的实例(本身)
     */
    static PicOperate* picOperate;

    /**
     * @brief recs 需要在图片上进行修改的矩形区域们
     */
    vector<Rect> recs;
    /**
     * @brief drawRec 是否在图片上画出矩形
     */
    bool drawRec;
    /**
     * @brief drawUnitPic 是否在图片上画出部件图片
     */
    bool drawUnitPic;
    /**
     * @brief unitPic 需要在图片上添加的部件图片
     */
    Mat unitPic;
    /**
     * @brief drawPersonName 是否画出姓名
     */
    bool drawPersonName;
    /**
     * @brief person_names 人物对应姓名
     */
    vector<string> person_names;
    /**
     * @brief image 操作后的图片
     */
    Mat image;

    void operateImage();
};

#endif // PICOPERATE_H
