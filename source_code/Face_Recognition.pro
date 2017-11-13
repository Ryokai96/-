#-------------------------------------------------
#
# Project created by QtCreator 2017-10-26T16:39:52
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Face_Recognition
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/local/include\
               /usr/local/include/opencv\
               /usr/local/include/opencv2\
               /usr/include/freetype2

LIBS += -L/usr/local/lib\
        -lopencv_core\
        -lopencv_imgcodecs\
        -lopencv_highgui\
        -lopencv_imgproc\
        -lopencv_shape\
        -lopencv_videoio\
        -lopencv_ml\
        -lopencv_face\
        -lopencv_photo\
        -lopencv_plot\
        -lopencv_surface_matching\
        -lopencv_objdetect\
        -L/usr/lib/x86_64-linux-gnu\
        -lfreetype

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    face_recognition/fr_train.cpp \
    face_recognition/face_predict.cpp \
    widget/righttabwidget.cpp \
    init/varinit.cpp \
    pic_operate/picoperate.cpp \
    face_detection/face_detection.cpp \
    database/personoperate.cpp \
    common/csvoperate.cpp \
    common/dbutil.cpp \
    common/inioperate.cpp \
    database/facepicoperate.cpp \
    entity/person.cpp \
    entity/facepic.cpp \
    common/cvxtext.cpp

HEADERS += \
        mainwindow.h \
    face_recognition/fr_train.h \
    face_recognition/face_predict.h \
    widget/righttabwidget.h \
    init/varinit.h \
    pic_operate/picoperate.h \
    face_detection/face_detection.h \
    database/personoperate.h \
    common/csvoperate.h \
    common/dbutil.h \
    common/inioperate.h \
    database/facepicoperate.h \
    entity/person.h \
    entity/facepic.h \
    common/cvxtext.h

FORMS += \
        mainwindow.ui \
    widget/righttabwidget.ui

DISTFILES += \
    resources/train_filepath.ini
