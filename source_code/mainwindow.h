#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/face/facerec.hpp>
#include "widget/righttabwidget.h"
#include "pic_operate/picoperate.h"
#include "face_detection/face_detection.h"
#include "entity/person.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateImage();

    void getEnterInfo(Person person);
    void refreshPersonAndFacePic();
    void enterFace();
    void completeEnter();
    void recognitionStart();
    void startAutoRecognition();
    void autoRecognition();
    void stopAutoRecognition();
    void drawUnitPic(int unitPic);
    void takePhoto();

signals:
    /**
     * @brief faceDetect 人脸检测
     */
    void faceDetect();

    /**
     * @brief canCompleteEnter 可以完成录入了
     */
    void canCompleteEnter();

    /**
     * @brief enterComplete 已完成人脸录入
     */
    void enterComplete();

    /**
     * @brief faceRecognitionEnd 人脸识别结束
     * @param person_name 人脸识别的结果(姓名)
     */
    void faceRecognitionEnd(QString person_name);

    /**
     * @brief doAutoRecognition 进行自动识别
     */
    void doAutoRecognition();

private:
    Ui::MainWindow *ui;

    /**
     * @brief srcImage 从摄像头中获取的原本的图片
     */
    Mat srcImage;
    /**
     * @brief objImage 操作后的图片
     */
    Mat objImage;
    /**
     * @brief videoCap 从摄像头捕获的视频
     */
    VideoCapture videoCap;
    /**
     * @brief recs 检测出的内容所在矩形
     */
    vector<Rect> recs;
    /**
     * @brief person 人脸信息
     */
    Person person;
    /**
     * @brief facePic 要录入的图片
     */
    vector<Mat> facePic;
    /**
     * @brief model 人脸识别器
     */
    Ptr<face::FaceRecognizer> model;
    /**
     * @brief isAutoRecognition 是否自动识别人脸
     */
    bool isAutoRecognition;
    /**
     * @brief person_names 自动识别出的多张人脸的姓名
     */
    vector<string> person_names;

    /**
     * @brief theTimer 定时器
     */
    QTimer theTimer;

    /**
     * @brief rightTabWidget 右边的TabWidget控件
     */
    RightTabWidget *rightTabWidget;
    /**
     * @brief picOperate 对图片进行操作的实例
     */
    PicOperate *picOperate;
    /**
     * @brief faceDetection 用于人脸检测的实例
     */
    Face_Detection *faceDetection;

    void setFaceRect();
    void setEyeRect();

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
