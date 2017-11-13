#include "righttabwidget.h"
#include "ui_righttabwidget.h"
#include <QMessageBox>
#include <QRegExp>
#include <QDebug>

RightTabWidget::RightTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::RightTabWidget)
{
    ui->setupUi(this);

    this->picOperate = PicOperate::getPicOperate();

    ui->enter_enterPushButton->setEnabled(false);
    ui->enter_completePushButton->setEnabled(false);

    //点击部件图片按钮
    connect(ui->photo_sunglassesPushButton, SIGNAL(clicked()), this, SLOT(photo_unitPicPushButton_clicked()));
    connect(ui->photo_suneyePushButton, SIGNAL(clicked()), this, SLOT(photo_unitPicPushButton_clicked()));
}

RightTabWidget::~RightTabWidget()
{
    delete ui;
}

/**
 * @brief RightTabWidget::on_enter_confirmPushButton_clicked enterTab页确定按钮槽函数
 */
void RightTabWidget::on_enter_confirmPushButton_clicked()
{
    QString name = ui->enter_nameLineEdit->text().trimmed();
    QString age = ui->enter_ageLineEdit->text().trimmed();
    QString sex;
    if(ui->enter_sexComboBox->currentIndex() == 0) {
        sex = "man";
    } else if (ui->enter_sexComboBox->currentIndex() == 1) {
        sex = "woman";
    }

    QString namePattern = "\\S+";
    QRegExp nameameRx(namePattern);

    if(!nameameRx.exactMatch(name)) {
        QMessageBox::information(this, "提示", "必须输入姓名", QMessageBox::Ok);
        return ;
    }

    this->person.setPerson_name(name);
    this->person.setPerson_age(age);
    this->person.setPerson_sex(sex);

    ui->enter_confirmPushButton->setEnabled(false);

    ui->enter_enterPushButton->setEnabled(true);

    emit enterFaceInfo(person);
}

/**
 * @brief RightTabWidget::on_enter_reputPushButton_clicked enterTab页重新输入按钮槽函数
 */
void RightTabWidget::on_enter_reputPushButton_clicked()
{
    //清空enterTab页数据，并通知MainWindow刷新person和facePic
    ui->enter_confirmPushButton->setEnabled(true);
    ui->enter_enterPushButton->setEnabled(false);
    ui->enter_completePushButton->setEnabled(false);
    emit faceInfoReput();
}

/**
 * @brief RightTabWidget::on_enter_enterPushButton_clicked enterTab页录入人脸按钮槽函数
 */
void RightTabWidget::on_enter_enterPushButton_clicked()
{
//    //点击录入人脸后enterTab页重新输入按钮不可用
//    ui->enter_reputPushButton->setEnabled(false);
    emit enterFace();
}

/**
 * @brief RightTabWidget::on_enter_completePushButton_clicked enterTab页完成录入按钮槽函数
 */
void RightTabWidget::on_enter_completePushButton_clicked()
{
    emit completeEnterFace();
}

/**
 * @brief RightTabWidget::on_RightTabWidget_tabBarClicked TabBar点击槽函数
 * @param index
 */
void RightTabWidget::on_RightTabWidget_tabBarClicked(int index)
{
    ui->rec_recognitionPushButton->setEnabled(true);

    if(index == 0 || index == 1) {
        picOperate->setDrawRec(true);
        picOperate->setDrawUnitPic(false);
    }

    //切换到拍照页
    if(index == 2) {
        picOperate->setDrawRec(false);
    }

    //从enterTab页切换到其他页，清空enterTab页的数据，并通知MainWindow刷新person和facePic数据
    if(this->currentIndex() == 0) {
        ui->enter_nameLineEdit->clear();
        ui->enter_ageLineEdit->clear();
        ui->enter_confirmPushButton->setEnabled(true);
        ui->enter_enterPushButton->setEnabled(false);
        ui->enter_completePushButton->setEnabled(false);
        ui->enter_sexComboBox->setCurrentIndex(0);

        emit transferTabFromEnterToOther();
    }

    if(this->currentIndex() == 1) {
        ui->rec_nameLineEdit->clear();
        emit stopAutoRecognition();
    }
}

/**
 * @brief RightTabWidget::canCompleteEnter 可以完成录入了
 */
void RightTabWidget::canCompleteEnter()
{
    //完成录入按钮可点击
    ui->enter_completePushButton->setEnabled(true);
}

/**
 * @brief RightTabWidget::enterComplete 人脸录入完成
 */
void RightTabWidget::enterComplete()
{
    QMessageBox::information(this, "提示", "人脸录入成功", QMessageBox::Ok);

    ui->enter_nameLineEdit->clear();
    ui->enter_ageLineEdit->clear();
    ui->enter_confirmPushButton->setEnabled(true);
    ui->enter_enterPushButton->setEnabled(false);
    ui->enter_completePushButton->setEnabled(false);
    ui->enter_sexComboBox->setCurrentIndex(0);
}

/**
 * @brief RightTabWidget::on_rec_recognitionPushButton_clicked recTab页开始识别槽函数
 */
void RightTabWidget::on_rec_recognitionPushButton_clicked()
{
    ui->rec_recognitionPushButton->setEnabled(false);
    //停止自动识别
    emit stopAutoRecognition();

    //开始识别
    emit recognitionStart();
}

/**
 * @brief RightTabWidget::faceRecognitionEnd 人脸识别结束
 * @param person_name 识别出来的姓名
 */
void RightTabWidget::faceRecognitionEnd(QString person_name)
{
    ui->rec_nameLineEdit->setText(person_name);
    ui->rec_recognitionPushButton->setEnabled(true);
}

/**
 * @brief RightTabWidget::on_photo_takePushButton_clicked photoTab页拍照按钮槽函数
 */
void RightTabWidget::on_photo_takePushButton_clicked()
{
    emit takePhoto();
}

/**
 * @brief RightTabWidget::on_photo_unitPicPushButton_clicked photoTab页部件图片按钮槽函数
 */
void RightTabWidget::photo_unitPicPushButton_clicked()
{
    QString buttonName = sender()->objectName();
    qDebug() << buttonName;
    if(buttonName.compare("photo_sunglassesPushButton") == 0) {
        emit drawUnitPic(1);
    } else if(buttonName.compare("photo_suneyePushButton") == 0) {
        emit drawUnitPic(2);
    }
}

/**
 * @brief RightTabWidget::on_rec_autoRecognitionPushButton_clicked recTab页自动识别槽函数
 */
void RightTabWidget::on_rec_autoRecognitionPushButton_clicked()
{
    emit autoRecognition();
}

/**
 * @brief RightTabWidget::on_rec_stopAutoRecognitionPushButton_clicked recTab页停止自动识别槽函数
 */

void RightTabWidget::on_rec_stopAutoRecognitionPushButton_clicked()
{
    emit stopAutoRecognition();
}
