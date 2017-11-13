#include "picoperate.h"
#include <QDebug>
#include "common/cvxtext.h"
#include <cxcore.hpp>

PicOperate::PicOperate()
{
    this->drawRec = true;
}

PicOperate* PicOperate::picOperate = new PicOperate();

/**
 * @brief PicOperate::getPicOperate 获得操作对象的实例
 * @return 用于操作对象的实例
 */
PicOperate *PicOperate::getPicOperate()
{
    return picOperate;
}

/**
 * @brief PicOperate::getImage 获取进行操作后的图片
 * @return 进行操作后的图片
 */
Mat PicOperate::getImage(Mat srcImage)
{
    this->image = srcImage;
    operateImage();
    return this->image;
}

void PicOperate::setDrawRec(bool value)
{
    drawRec = value;
}

bool PicOperate::getDrawRec() const
{
    return drawRec;
}

void PicOperate::setRecs(const vector<Rect> &value)
{
    recs = value;
}

/**
 * @brief PicOperate::toGrayAndResize 将图片转换成灰度图片并重置大小
 * @param srcImage 原图片
 * @param objImage 转换成的图片
 * @param weight 图片宽，默认为320
 * @param height 图片高，默认为243
 */
void PicOperate::toGrayAndResize(Mat &srcImage, Mat &objImage, int weight, int height)
{
    Mat gray;
    //将srcImage转换为灰度图片，保存到gray
    cvtColor(srcImage, gray, CV_BGR2GRAY);
    //将gray图片大小转换为指定大小，保存到objImage
    cv::resize(gray, objImage, Size(weight, height));
}

void PicOperate::setUnitPic(const Mat &value)
{
    unitPic = value;
}

void PicOperate::setDrawUnitPic(bool value)
{
    drawUnitPic = value;
}

bool PicOperate::getDrawUnitPic() const
{
    return drawUnitPic;
}

bool PicOperate::getDrawPersonName() const
{
    return drawPersonName;
}

void PicOperate::setDrawPersonName(bool value)
{
    drawPersonName = value;
}

void PicOperate::setPerson_names(const vector<string> &value)
{
    person_names = value;
}

/**
 * @brief PicOperate::operateImage 对图片的操作
 */
void PicOperate::operateImage()
{
    if(this->drawRec == true) {
        for(uint i = 0; i < this->recs.size(); i++) {
            rectangle(this->image, recs[i], Scalar(0, 0, 255));
        }
    }

    if(this->drawUnitPic == true) {
        for(uint i = 0; i < this->recs.size(); i++) {
            //改变unitPic大小为需要在图片上进行修改的矩形区域的大小
            Mat tempUnitPic;
            resize(this->unitPic, tempUnitPic, this->recs[i].size());

            cvtColor(tempUnitPic, tempUnitPic, CV_RGBA2BGRA);
            //原图转换为4通道的BGRA
            cvtColor(this->image, this->image, CV_BGR2BGRA);


            vector<int> compression_params;
            compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
            compression_params.push_back(9);
            if(i == 0) {
                imwrite("/home/ryoukai/Ryoukai_FaceRecognition/picture/unitpic/1.png", unitPic, compression_params);
            }

            vector<Mat> imgChannels;
            vector<Mat> unitChannels;

            //将原图片转换成四个单通道图像
            split(this->image, imgChannels);

            //将部件图片转换成四个单通道图像
            split(tempUnitPic, unitChannels);

            //分别将每个单通道图像中的矩形区域和unitPic进行图像叠加
            addWeighted(imgChannels[0](this->recs[i]), 1.0, unitChannels[0], 0.5, 0, imgChannels[0](this->recs[i]));
            addWeighted(imgChannels[1](this->recs[i]), 1.0, unitChannels[1], 0.5, 0, imgChannels[1](this->recs[i]));
            addWeighted(imgChannels[2](this->recs[i]), 1.0, unitChannels[2], 0.5, 0, imgChannels[2](this->recs[i]));
            addWeighted(imgChannels[3](this->recs[i]), 1.0, unitChannels[3], 0.5, 0, imgChannels[3](this->recs[i]));
            //将三个单通道重新合并成一个三通道图像
            merge(imgChannels, this->image);

            cvtColor(this->image, this->image, CV_BGRA2BGR);
        }
    }

    if(this->drawPersonName == true) {
        CvxText text("/home/ryoukai/Ryoukai_FaceRecognition/fontstyle/wqy-zenhei.ttc");
        float p = 0.5;
        text.setFont(NULL, NULL, NULL, &p);   // 透明处理
        IplImage *iplImage = new IplImage(image);
        for(uint i = 0; i < recs.size(); i++) {
            text.putText(iplImage, person_names[i].c_str(), CvPoint(recs[i].x, recs[i].y), CvScalar(0, 0, 255));
//            putText(image, person_names[i], Point(recs[i].x, recs[i].y), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);
        }
        image = cvarrToMat(iplImage);
    }
}
