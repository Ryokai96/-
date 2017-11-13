#include "mainwindow.h"
#include <QApplication>
#include "common/csvoperate.h"
#include <opencv2/face.hpp>
#include <opencv2/face/facerec.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include "common/inioperate.h"

using namespace face;

int main(int argc, char *argv[])
{
//    QMap<QString, QMap<QString, QString>> inimap;
//    INIOperate::read_ini("/home/ryoukai/Qt_project/Face_Recognition/resources/train_filepath.ini", inimap);

//    string filename = inimap.value("train_photo").value("trainCSV").toStdString();
//    vector<Mat> images;
//    vector<int> labels;

//    //读取csv文件，将图片地址及对应标签存入images和labels
//    CSVOperate::read_csv(filename, images, labels);

//    Ptr<FaceRecognizer> model = createEigenFaceRecognizer();

//    model->load(inimap.value("train_result").value("trainResult").toStdString());

//    //加载人脸分类器
//    CascadeClassifier cas("/home/ryoukai/下载/opencv-3.2.0/data/haarcascades/haarcascade_frontalface_default.xml");

//    VideoCapture cap;
//    //开启摄像头
//    cap.open(0);

//    Mat image;

//    //用于保存被检测物体的矩形框向量组
//    vector<Rect> recs;

//    Mat test(320, 243, CV_8UC1);
//    Mat gray;
//    int x = 0, y = 0;

//    while(true) {
//        cap >> image;
//        if(image.empty()) {
//            break;
//        }

//        //检测人脸，参数说明:
//        //image: 待检测图片
//        //objects: 被检测物体的矩形框向量组
//        //scaleFactor: 每次搜索窗口扩大比例，1.1即每次搜索窗口依次扩大10%
//        //minNeighbors: 表示构成检测目标的相邻矩形的最小个数(默认为3个)，如果组成检测目标的小矩形的个数和小于min_neighbors-1都会被排除
//        //flags: 要么使用默认值，要么使用CV_HAAR_DO_CANNY_PRUNING，如果设置为CV_HAAR_DO_CANNY_PRUNING，那么函数将会使用Canny边缘检测来排除边缘过多或过少的区域，因此这些区域通常不会是人脸所在区域
//        //minSize和maxSize用来限制得到的目标区域的范围，这里限制了范围大小只能为50
//        cas.detectMultiScale(image, recs, 1.1, 6, 0, Size(50, 50));

//        for(int i = 0; i < recs.size(); i++) {
//            //参数为 要画矩形的所在图像，矩形位置，Scalar表示RGB三色
//            rectangle(image, recs[i], Scalar(0, 0, 255));
//            x = recs[i].x + recs[i].width / 2;
//            y = recs[i].y + recs[i].height / 2;

//            Mat roi = image(recs[i]);
//            //将矩形内的图片(人脸)roi转换为灰度图片，保存到gray
//            cvtColor(roi, gray, CV_BGR2GRAY);
//            //将gray图片大小转换为训练样本的大小，保存到test
//            resize(gray, test, Size(320, 243));

//            //识别(预测)人脸
//            int result = model->predict(test);

//            //根据识别结果输出到图片上
//            switch (result) {
//            case 0:
//                //参数说明: 输出到的图片，要绘制的文字，文本框的左下角坐标，字体，文字尺寸，线条的颜色(RGB)，线条宽度
//                putText(image, "a", Point(recs[i].x, recs[i].y), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);
//                break;
//            case 1:
//                putText(image, "b", Point(recs[i].x, recs[i].y), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);
//                break;
//            case 2:
//                putText(image, "c", Point(recs[i].x, recs[i].y), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);
//                break;
//            case 3:
//                putText(image, "d", Point(recs[i].x, recs[i].y), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);
//                break;
//            case 4:
//                putText(image, "e", Point(recs[i].x, recs[i].y), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);
//                break;
//            case 5:
//                putText(image, "f", Point(recs[i].x, recs[i].y), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);
//                break;
//            case 6:
//                putText(image, "g", Point(recs[i].x, recs[i].y), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);
//                break;
//            case 7:
//                putText(image, "h", Point(recs[i].x, recs[i].y), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);
//                break;
//            default:
//                putText(image, "not", Point(recs[i].x, recs[i].y), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);
//            }
//        }

//        imshow("Sample", image);
//        if(waitKey(10) == 27)
//            break;
//    }

//    return 0;

    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();

}
