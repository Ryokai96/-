#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include "pic_operate/picoperate.h"
#include "entity/person.h"

namespace Ui {
class RightTabWidget;
}

class RightTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit RightTabWidget(QWidget *parent = 0);
    ~RightTabWidget();

signals:
    /**
     * @brief enterFaceInfo 录入人脸的信息
     * @param person 人脸信息
     */
    void enterFaceInfo(Person person);
    /**
     * @brief faceInfoReput 重新输入人脸信息
     */
    void faceInfoReput();
    /**
     * @brief enterFace 录入人脸
     */
    void enterFace();
    /**
     * @brief completeEnterFace 完成录入
     */
    void completeEnterFace();
    /**
     * @brief transferTabFromEnterToOther Tab页从enterTab切换到其他页
     */
    void transferTabFromEnterToOther();
    /**
     * @brief recognitionStart 开始识别
     */
    void recognitionStart();
    /**
     * @brief autoRecognition 开始自动识别
     */
    void autoRecognition();
    /**
     * @brief stopAutoRecognition 停止自动识别
     */
    void stopAutoRecognition();
    /**
     * @brief drawUnitPic 显示部件图片
     * @param unitPic 部件图片编号
     */
    void drawUnitPic(int unitPic);
    /**
     * @brief takePhoto 拍照
     */
    void takePhoto();

private slots:
    void on_enter_confirmPushButton_clicked();

    void on_enter_reputPushButton_clicked();

    void on_enter_enterPushButton_clicked();

    void on_enter_completePushButton_clicked();

    void on_RightTabWidget_tabBarClicked(int index);

    void canCompleteEnter();

    void enterComplete();

    void on_rec_recognitionPushButton_clicked();

    void faceRecognitionEnd(QString person_name);

    void on_photo_takePushButton_clicked();

    void photo_unitPicPushButton_clicked();

    void on_rec_autoRecognitionPushButton_clicked();

    void on_rec_stopAutoRecognitionPushButton_clicked();

private:
    Ui::RightTabWidget *ui;

    /**
     * @brief picOperate 对图片进行操作的实例
     */
    PicOperate *picOperate;

    //录入信息
    Person person;
};

#endif // TABWIDGET_H
