#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "face_recognition/fr_train.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <QMessageBox>
#include "database/facepicoperate.h"
#include "database/personoperate.h"
#include "face_recognition/face_predict.h"
#include "init/varinit.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //添加的窗体控件
    this->rightTabWidget = new RightTabWidget;
    ui->rightGridLayout->addWidget(rightTabWidget);

    this->model = createEigenFaceRecognizer();
//    Fr_Train::face_eigen_train_save(model);
    //读取训练文件
    Fr_Train::face_eigen_train_load(model);

    //定时器，刷新videoLabel
    connect(&theTimer, &QTimer::timeout, this, &MainWindow::updateImage);

    //获取录入人脸信息
    connect(this->rightTabWidget, SIGNAL(enterFaceInfo(Person)), this, SLOT(getEnterInfo(Person)));
    //需要重新输入人脸信息，刷新person和facePic
    connect(this->rightTabWidget, SIGNAL(faceInfoReput()), this, SLOT(refreshPersonAndFacePic()));
    //录入人脸
    connect(this->rightTabWidget, SIGNAL(enterFace()), this, SLOT(enterFace()));
    //可完成录入人脸了
    connect(this, SIGNAL(canCompleteEnter()), this->rightTabWidget, SLOT(canCompleteEnter()));
    //完成录入人脸
    connect(this->rightTabWidget, SIGNAL(completeEnterFace()), this, SLOT(completeEnter()));
    //rightTanWidget从enterTab页切换到其他页，刷新person和facePic
    connect(this->rightTabWidget, SIGNAL(transferTabFromEnterToOther()), this, SLOT(refreshPersonAndFacePic()));
    //已完成一次人脸录入
    connect(this, SIGNAL(enterComplete()), this->rightTabWidget, SLOT(enterComplete()));

    //开始识别人脸
    connect(this->rightTabWidget, SIGNAL(recognitionStart()), SLOT(recognitionStart()));
    //人脸识别结束
    connect(this, SIGNAL(faceRecognitionEnd(QString)), this->rightTabWidget, SLOT(faceRecognitionEnd(QString)));
    //自动识别开始
    connect(this->rightTabWidget, SIGNAL(autoRecognition()), this, SLOT(startAutoRecognition()));
    connect(this, SIGNAL(doAutoRecognition()), this, SLOT(autoRecognition()));
    //停止自动识别
    connect(this->rightTabWidget, SIGNAL(stopAutoRecognition()), this, SLOT(stopAutoRecognition()));

    //显示部件图片
    connect(this->rightTabWidget, SIGNAL(drawUnitPic(int)), this, SLOT(drawUnitPic(int)));
    //拍照
    connect(this->rightTabWidget, SIGNAL(takePhoto()), this, SLOT(takePhoto()));

    //获取对图片操作的实例
    this->picOperate = PicOperate::getPicOperate();
    //用于人脸检测的实例
    this->faceDetection = new Face_Detection();

    if(videoCap.open(0)) {
        videoCap.read(srcImage);
        theTimer.start(20); //每20毫秒发送一次timeout信号
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::updateImage 刷新用于显示摄像头视频的videoLabel
 */
void MainWindow::updateImage()
{
    videoCap >> srcImage;
    if(srcImage.data) {
        if(picOperate->getDrawRec() == true) {
            setFaceRect();
        }
        if(picOperate->getDrawUnitPic() == true) {
            setEyeRect();
        }

        //对图片进行操作
        objImage = picOperate->getImage(srcImage);

        if(picOperate->getDrawPersonName() == true) {
            person_names.clear();
        }


        //opencv使用的是BGR，Qt是RGB，需要进行转换
        cvtColor(objImage, objImage, CV_BGR2RGB);

        ui->videoLabel->update();
    }
}

/**
 * @brief MainWindow::setFaceRect 检测人脸，设置人脸所在矩形
 */
void MainWindow::setFaceRect()
{
    this->faceDetection->faceDetection(srcImage, this->recs);

    //用于画出人脸所在矩形
    this->picOperate->setRecs(this->recs);
}

/**
 * @brief MainWindow::setEyeRect 检测眼睛，设置眼睛所在矩形
 */
void MainWindow::setEyeRect()
{
    this->faceDetection->eyeDetection(srcImage, this->recs);
    this->picOperate->setRecs(this->recs);
}

/**
 * @brief MainWindow::autoRecognition 自动识别人脸
 */
void MainWindow::autoRecognition()
{
//    vector<vector<Mat>> persons;

//    PersonOperate personOperate;

//    uint i = 0;

//    for(i = 0; i < recs.size(); i++) {
//        vector<Mat> images;
//        persons.push_back(images);
//    }

//    for(i = 0; i < 20; i++) {
//        for(uint j = 0; j < recs.size(); j++) {
//            Mat image;
//            Mat roi = srcImage(recs[j]);
//            //将矩形内的图片(人脸)roi转换为灰度图片，并转换为训练样本的大小，保存到image
//            PicOperate::toGrayAndResize(roi, image);
//            persons[j].push_back(image);
//        }
//        waitKey(20);
//    }

//    int recResult;
//    string person_name;
//    for(i = 0; i < recs.size(); i++) {
//        recResult = Face_Predict::face_predict(model, persons[i]);
//        if(recResult == -1) {
//            person_name  = "未识别成功";
//        } else {
//            person_name = personOperate.selectPerson_nameById(recResult).toStdString();
//        }
//        this->person_names.push_back(person_name);
//    }

    Mat test(320, 243, CV_8UC1);
    String person_name;
    PersonOperate personOperate;
    for(uint i = 0; i < recs.size(); i++) {

        Mat roi = srcImage(recs[i]);
        //将矩形内的图片(人脸)roi转换为灰度图片，并转换为训练样本的大小，保存到test
        PicOperate::toGrayAndResize(roi, test);

        //识别(预测)人脸
        int predictedLabel = -1;
        double confidence = 0.0;
        model->predict(test, predictedLabel, confidence);

        if(confidence > 5000 && predictedLabel == -1) {
            person_name = "未识别成功";
        }
        else {
            person_name = personOperate.selectPerson_nameById(predictedLabel).toStdString();
        }
        person_names.push_back(person_name);
    }


    if(isAutoRecognition == false) {
        picOperate->setDrawPersonName(false);
    }
    else {
        picOperate->setDrawPersonName(true);
        picOperate->setPerson_names(person_names);
        waitKey(20);
        emit doAutoRecognition();
    }
}

/**
 * @brief MainWindow::stopAutoRecognition 停止自动识别
 */
void MainWindow::stopAutoRecognition()
{
    this->isAutoRecognition = false;
}

/**
 * @brief MainWindow::getEnterInfo 获取RightTabwidget中发送的要录入的人脸信息
 * @param person 人脸信息
 */
void MainWindow::getEnterInfo(Person person)
{
    this->person = person;
}

/**
 * @brief MainWindow::refreshPersonAndFacePic 刷新person和facePic
 */
void MainWindow::refreshPersonAndFacePic()
{
    //刷新person和facePic
    this->person.setPerson_id(0);
    this->person.setPerson_name(NULL);
    this->person.setPerson_age(NULL);
    this->person.setPerson_sex(NULL);
    this->facePic.clear();
}

/**
 * @brief MainWindow::enterFace 录入人脸
 */
void MainWindow::enterFace()
{
    if(this->recs.size() == 0) {
        QMessageBox::information(this, "提示", "请对准人脸", QMessageBox::Ok);
        return ;
    }
    else if(this->recs.size() > 1) {
        QMessageBox::information(this, "提示", "识别出多张人脸，录入失败", QMessageBox::Ok);
        return ;
    }

    Mat image;
    Mat roi = srcImage(recs[0]);
    //将矩形内的图片(人脸)roi转换为灰度图片，并转换为训练样本的大小，保存到image
    PicOperate::toGrayAndResize(roi, image);

    facePic.push_back(image);

    //录入超过两张，可以完成录入
    if(facePic.size() >= 2) {
        emit canCompleteEnter();
    }
}

/**
 * @brief MainWindow::completeEnter 完成一次人脸录入
 */
void MainWindow::completeEnter()
{
    //插入数据到person表
    PersonOperate personOperate;
    int person_id = personOperate.addPerson(person);
    if(person_id == -1) {
        QMessageBox::information(this, "提示", "人脸录入失败", QMessageBox::Ok);
        return ;
    } else if(person_id > 0) {
        person.setPerson_id(person_id);
    }

    FacepicOperate facepicOperate;

    //创建对应的facepic表
    facepicOperate.createFacepicTabel(person.getPerson_id());

    //用于训练的label
    vector<int> labels;

    VarInit *varInit = VarInit::getVarInit();
    //保存图片文件的文件夹
    QString picRootPath = varInit->getPersonPicPath() + QString::number(person.getPerson_id());

    for(uint i = 0; i < facePic.size(); i++) {
        //创建person对应的图片文件夹
        QDir *dir = new QDir(varInit->getPersonPicPath());
        if(!dir->exists(picRootPath)) {
            if(!dir->mkdir(picRootPath)) {
                QMessageBox::information(this, "提示", "人脸录入失败", QMessageBox::Ok);
                qDebug() << "mkdir error";
                return ;
            }
        }

        //图片路径
        QString picPath = picRootPath + "/" + QString::number(i + 1) + ".pgm";

        //写入facepic表
        if(facepicOperate.insertFacepic(person.getPerson_id(), picPath) == -1) {
            QMessageBox::information(this, "提示", "人脸录入失败", QMessageBox::Ok);
            return ;
        }

        vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PXM_BINARY);
        compression_params.push_back(1);
        //保存图片
        if(!imwrite(picPath.toStdString(), facePic[i], compression_params)) {
            QMessageBox::information(this, "提示", "人脸录入失败", QMessageBox::Ok);
            return ;
        }
        labels.push_back(person.getPerson_id());
    }

    //训练并保存训练文件
    Fr_Train::face_eigen_train_save(model);

    //已完成人脸录入
    emit enterComplete();

    //刷新person和facePic
    this->refreshPersonAndFacePic();
}

/**
 * @brief MainWindow::recognitionStart 开始识别人脸
 */
void MainWindow::recognitionStart()
{
    vector<Mat> images;
    int i = 1;
    while(i < 20) {
        //每20ms录一张
        waitKey(20);
        if(this->recs.size() == 1) {
            Mat image;
            Mat roi = srcImage(recs[0]);
            //将矩形内的图片(人脸)roi转换为灰度图片，并转换为训练样本的大小，保存到image
            PicOperate::toGrayAndResize(roi, image);
            images.push_back(image);
            i++;
        }
    }

    int recResult = Face_Predict::face_predict(model, images);
    QString person_name;
    if(recResult == -1) {
        QMessageBox::information(this, "提示", "识别失败", QMessageBox::Ok);
        person_name = "";
    }
    else {
        QMessageBox::information(this, "提示", "识别成功", QMessageBox::Ok);
        PersonOperate personOperate;
        person_name = personOperate.selectPerson_nameById(recResult);
    }
    emit faceRecognitionEnd(person_name);
}

/**
 * @brief MainWindow::autoRecognition 开始自动识别
 */
void MainWindow::startAutoRecognition()
{
    this->isAutoRecognition = true;
    emit doAutoRecognition();
}

/**
 * @brief MainWindow::drawUnitPic 设置画出部件图片
 * @param unitPic 部件图片
 */
void MainWindow::drawUnitPic(int unitPic)
{
    if(unitPic == 1) {
        picOperate->setUnitPic(imread("/home/ryoukai/Ryoukai_FaceRecognition/picture/unitpic/sunglasses.png", IMREAD_UNCHANGED));
        picOperate->setDrawUnitPic(true);
    }
    if(unitPic == 2) {
        picOperate->setUnitPic(imread("/home/ryoukai/Ryoukai_FaceRecognition/picture/unitpic/sun.png", IMREAD_UNCHANGED));
        picOperate->setDrawUnitPic(true);
    }
}

/**
 * @brief MainWindow::takePhoto 拍照
 */
void MainWindow::takePhoto()
{
    VarInit* varInit = VarInit::getVarInit();
    QString filename = varInit->getCameraPath() + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz") + ".jpeg";
    cvtColor(objImage, objImage, CV_BGR2RGB);
    imwrite(filename.toStdString(), objImage);
}

/**
 * @brief MainWindow::paintEvent 处理重绘事件(只要有窗体部件被重绘就会被调用)，用于将Mat转换为QImage并在videoLabel中显示
 * @param e 重绘事件
 */
void MainWindow::paintEvent(QPaintEvent *e)
{
    QImage image = QImage((uchar*)(objImage.data), objImage.cols, objImage.rows, QImage::Format_RGB888);
    ui->videoLabel->setPixmap(QPixmap::fromImage(image));
    ui->videoLabel->resize(image.size());
    Q_UNUSED(e);
}
