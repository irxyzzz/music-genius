/********************************************************************************
** Form generated from reading UI file 'controller.ui'
**
** Created: Sat Mar 12 15:27:50 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QToolBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Controller
{
public:
    QWidget *tb_staff;
    QGridLayout *gridLayout_3;
    QLabel *label_dp_key;
    QSlider *slider_key;
    QLabel *label_dp_key_pic;
    QLabel *label_key;
    QLabel *label_dp_meter;
    QSlider *slider_meter;
    QLabel *label_dp_meter_pic;
    QLabel *label_meter;
    QPushButton *btn_run;
    QWidget *tb_keybd;
    QGridLayout *gridLayout_2;
    QLabel *label_dp_channel;
    QLabel *label_dp_velocity;
    QLabel *label_dp_base_octave;
    QLabel *label_dp_transpose;
    QLabel *label_dp_speed;
    QSlider *slider_channel;
    QSlider *slider_velocity;
    QSlider *slider_base_octave;
    QSlider *slider_transpose;
    QSlider *slider_speed;
    QLabel *label_channel;
    QLabel *label_velocity;
    QLabel *label__base_octave;
    QLabel *label_transpose;
    QLabel *label_speed;
    QWidget *tb_duration;
    QGridLayout *gridLayout;
    QPushButton *btn_note_96;
    QPushButton *btn_note_48;
    QPushButton *btn_note_24;
    QPushButton *btn_note_12;
    QPushButton *btn_note_6;
    QPushButton *btn_note_3;
    QPushButton *btn_select;
    QPushButton *btn_note_dot;

    void setupUi(QToolBox *Controller)
    {
        if (Controller->objectName().isEmpty())
            Controller->setObjectName(QString::fromUtf8("Controller"));
        Controller->resize(200, 391);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Controller->sizePolicy().hasHeightForWidth());
        Controller->setSizePolicy(sizePolicy);
        Controller->setMinimumSize(QSize(200, 390));
        Controller->setMaximumSize(QSize(200, 16777215));
        tb_staff = new QWidget();
        tb_staff->setObjectName(QString::fromUtf8("tb_staff"));
        tb_staff->setGeometry(QRect(0, 0, 200, 316));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tb_staff->sizePolicy().hasHeightForWidth());
        tb_staff->setSizePolicy(sizePolicy1);
        tb_staff->setMinimumSize(QSize(0, 0));
        gridLayout_3 = new QGridLayout(tb_staff);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_dp_key = new QLabel(tb_staff);
        label_dp_key->setObjectName(QString::fromUtf8("label_dp_key"));

        gridLayout_3->addWidget(label_dp_key, 0, 0, 1, 2);

        slider_key = new QSlider(tb_staff);
        slider_key->setObjectName(QString::fromUtf8("slider_key"));
        slider_key->setMinimum(-7);
        slider_key->setMaximum(7);
        slider_key->setPageStep(1);
        slider_key->setOrientation(Qt::Vertical);
        slider_key->setTickPosition(QSlider::TicksBothSides);
        slider_key->setTickInterval(1);

        gridLayout_3->addWidget(slider_key, 1, 0, 1, 1);

        label_dp_key_pic = new QLabel(tb_staff);
        label_dp_key_pic->setObjectName(QString::fromUtf8("label_dp_key_pic"));

        gridLayout_3->addWidget(label_dp_key_pic, 1, 1, 1, 1);

        label_key = new QLabel(tb_staff);
        label_key->setObjectName(QString::fromUtf8("label_key"));

        gridLayout_3->addWidget(label_key, 2, 0, 1, 1);

        label_dp_meter = new QLabel(tb_staff);
        label_dp_meter->setObjectName(QString::fromUtf8("label_dp_meter"));

        gridLayout_3->addWidget(label_dp_meter, 3, 0, 1, 2);

        slider_meter = new QSlider(tb_staff);
        slider_meter->setObjectName(QString::fromUtf8("slider_meter"));
        slider_meter->setMinimum(1);
        slider_meter->setMaximum(4);
        slider_meter->setValue(3);
        slider_meter->setOrientation(Qt::Vertical);
        slider_meter->setTickPosition(QSlider::TicksBothSides);
        slider_meter->setTickInterval(1);

        gridLayout_3->addWidget(slider_meter, 4, 0, 1, 1);

        label_dp_meter_pic = new QLabel(tb_staff);
        label_dp_meter_pic->setObjectName(QString::fromUtf8("label_dp_meter_pic"));

        gridLayout_3->addWidget(label_dp_meter_pic, 4, 1, 1, 1);

        label_meter = new QLabel(tb_staff);
        label_meter->setObjectName(QString::fromUtf8("label_meter"));

        gridLayout_3->addWidget(label_meter, 5, 0, 1, 1);

        btn_run = new QPushButton(tb_staff);
        btn_run->setObjectName(QString::fromUtf8("btn_run"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btn_run->sizePolicy().hasHeightForWidth());
        btn_run->setSizePolicy(sizePolicy2);
        btn_run->setMinimumSize(QSize(0, 0));
        btn_run->setMaximumSize(QSize(16777215, 16777215));
        btn_run->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_run->setIcon(icon);
        btn_run->setIconSize(QSize(22, 22));

        gridLayout_3->addWidget(btn_run, 6, 0, 1, 2);

        Controller->addItem(tb_staff, QString::fromUtf8("\344\271\220\350\260\261\346\216\247\345\210\266"));
        tb_keybd = new QWidget();
        tb_keybd->setObjectName(QString::fromUtf8("tb_keybd"));
        tb_keybd->setGeometry(QRect(0, 0, 207, 300));
        sizePolicy1.setHeightForWidth(tb_keybd->sizePolicy().hasHeightForWidth());
        tb_keybd->setSizePolicy(sizePolicy1);
        tb_keybd->setMinimumSize(QSize(0, 0));
        gridLayout_2 = new QGridLayout(tb_keybd);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_dp_channel = new QLabel(tb_keybd);
        label_dp_channel->setObjectName(QString::fromUtf8("label_dp_channel"));
        label_dp_channel->setFrameShadow(QFrame::Plain);
        label_dp_channel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_dp_channel, 0, 0, 1, 1);

        label_dp_velocity = new QLabel(tb_keybd);
        label_dp_velocity->setObjectName(QString::fromUtf8("label_dp_velocity"));
        label_dp_velocity->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_dp_velocity, 0, 1, 1, 1);

        label_dp_base_octave = new QLabel(tb_keybd);
        label_dp_base_octave->setObjectName(QString::fromUtf8("label_dp_base_octave"));
        label_dp_base_octave->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_dp_base_octave, 0, 2, 1, 1);

        label_dp_transpose = new QLabel(tb_keybd);
        label_dp_transpose->setObjectName(QString::fromUtf8("label_dp_transpose"));
        label_dp_transpose->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_dp_transpose, 0, 3, 1, 1);

        label_dp_speed = new QLabel(tb_keybd);
        label_dp_speed->setObjectName(QString::fromUtf8("label_dp_speed"));

        gridLayout_2->addWidget(label_dp_speed, 0, 4, 1, 1);

        slider_channel = new QSlider(tb_keybd);
        slider_channel->setObjectName(QString::fromUtf8("slider_channel"));
        slider_channel->setMinimum(1);
        slider_channel->setMaximum(16);
        slider_channel->setValue(1);
        slider_channel->setTickPosition(QSlider::TicksBothSides);
        slider_channel->setTickInterval(1);

        gridLayout_2->addWidget(slider_channel, 1, 0, 1, 1);

        slider_velocity = new QSlider(tb_keybd);
        slider_velocity->setObjectName(QString::fromUtf8("slider_velocity"));
        slider_velocity->setMaximum(127);
        slider_velocity->setValue(127);
        slider_velocity->setOrientation(Qt::Vertical);
        slider_velocity->setTickPosition(QSlider::TicksBothSides);
        slider_velocity->setTickInterval(8);

        gridLayout_2->addWidget(slider_velocity, 1, 1, 1, 1);

        slider_base_octave = new QSlider(tb_keybd);
        slider_base_octave->setObjectName(QString::fromUtf8("slider_base_octave"));
        slider_base_octave->setMaximum(9);
        slider_base_octave->setOrientation(Qt::Vertical);
        slider_base_octave->setTickPosition(QSlider::TicksBothSides);
        slider_base_octave->setTickInterval(1);

        gridLayout_2->addWidget(slider_base_octave, 1, 2, 1, 1);

        slider_transpose = new QSlider(tb_keybd);
        slider_transpose->setObjectName(QString::fromUtf8("slider_transpose"));
        slider_transpose->setMinimum(-11);
        slider_transpose->setMaximum(11);
        slider_transpose->setOrientation(Qt::Vertical);
        slider_transpose->setTickPosition(QSlider::TicksBothSides);
        slider_transpose->setTickInterval(1);

        gridLayout_2->addWidget(slider_transpose, 1, 3, 1, 1);

        slider_speed = new QSlider(tb_keybd);
        slider_speed->setObjectName(QString::fromUtf8("slider_speed"));
        slider_speed->setMinimum(1);
        slider_speed->setMaximum(600);
        slider_speed->setSingleStep(10);
        slider_speed->setValue(100);
        slider_speed->setOrientation(Qt::Vertical);
        slider_speed->setTickPosition(QSlider::TicksBothSides);
        slider_speed->setTickInterval(10);

        gridLayout_2->addWidget(slider_speed, 1, 4, 1, 1);

        label_channel = new QLabel(tb_keybd);
        label_channel->setObjectName(QString::fromUtf8("label_channel"));

        gridLayout_2->addWidget(label_channel, 2, 0, 1, 1);

        label_velocity = new QLabel(tb_keybd);
        label_velocity->setObjectName(QString::fromUtf8("label_velocity"));

        gridLayout_2->addWidget(label_velocity, 2, 1, 1, 1);

        label__base_octave = new QLabel(tb_keybd);
        label__base_octave->setObjectName(QString::fromUtf8("label__base_octave"));

        gridLayout_2->addWidget(label__base_octave, 2, 2, 1, 1);

        label_transpose = new QLabel(tb_keybd);
        label_transpose->setObjectName(QString::fromUtf8("label_transpose"));

        gridLayout_2->addWidget(label_transpose, 2, 3, 1, 1);

        label_speed = new QLabel(tb_keybd);
        label_speed->setObjectName(QString::fromUtf8("label_speed"));

        gridLayout_2->addWidget(label_speed, 2, 4, 1, 1);

        Controller->addItem(tb_keybd, QString::fromUtf8("Midi\346\216\247\345\210\266\345\231\250"));
        tb_duration = new QWidget();
        tb_duration->setObjectName(QString::fromUtf8("tb_duration"));
        tb_duration->setGeometry(QRect(0, 0, 200, 316));
        gridLayout = new QGridLayout(tb_duration);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn_note_96 = new QPushButton(tb_duration);
        btn_note_96->setObjectName(QString::fromUtf8("btn_note_96"));
        btn_note_96->setMaximumSize(QSize(45, 45));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/cursorRedonda.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_note_96->setIcon(icon1);
        btn_note_96->setIconSize(QSize(30, 30));
        btn_note_96->setCheckable(true);

        gridLayout->addWidget(btn_note_96, 0, 0, 1, 1);

        btn_note_48 = new QPushButton(tb_duration);
        btn_note_48->setObjectName(QString::fromUtf8("btn_note_48"));
        btn_note_48->setMaximumSize(QSize(45, 45));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/iconoBlanca.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_note_48->setIcon(icon2);
        btn_note_48->setIconSize(QSize(30, 30));
        btn_note_48->setCheckable(true);

        gridLayout->addWidget(btn_note_48, 0, 1, 1, 1);

        btn_note_24 = new QPushButton(tb_duration);
        btn_note_24->setObjectName(QString::fromUtf8("btn_note_24"));
        btn_note_24->setMaximumSize(QSize(45, 45));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/cursorNegra.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_note_24->setIcon(icon3);
        btn_note_24->setIconSize(QSize(30, 30));
        btn_note_24->setCheckable(true);

        gridLayout->addWidget(btn_note_24, 1, 0, 1, 1);

        btn_note_12 = new QPushButton(tb_duration);
        btn_note_12->setObjectName(QString::fromUtf8("btn_note_12"));
        btn_note_12->setMaximumSize(QSize(45, 45));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/cursorCorchea.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_note_12->setIcon(icon4);
        btn_note_12->setIconSize(QSize(30, 30));
        btn_note_12->setCheckable(true);

        gridLayout->addWidget(btn_note_12, 1, 1, 1, 1);

        btn_note_6 = new QPushButton(tb_duration);
        btn_note_6->setObjectName(QString::fromUtf8("btn_note_6"));
        btn_note_6->setMaximumSize(QSize(45, 45));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/cursorSemicorchea.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_note_6->setIcon(icon5);
        btn_note_6->setIconSize(QSize(30, 30));
        btn_note_6->setCheckable(true);

        gridLayout->addWidget(btn_note_6, 2, 0, 1, 1);

        btn_note_3 = new QPushButton(tb_duration);
        btn_note_3->setObjectName(QString::fromUtf8("btn_note_3"));
        btn_note_3->setMaximumSize(QSize(45, 45));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/cursorFusa.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_note_3->setIcon(icon6);
        btn_note_3->setIconSize(QSize(30, 30));
        btn_note_3->setCheckable(true);

        gridLayout->addWidget(btn_note_3, 2, 1, 1, 1);

        btn_select = new QPushButton(tb_duration);
        btn_select->setObjectName(QString::fromUtf8("btn_select"));
        btn_select->setMaximumSize(QSize(45, 45));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_select->setIcon(icon7);
        btn_select->setIconSize(QSize(30, 30));
        btn_select->setCheckable(true);

        gridLayout->addWidget(btn_select, 3, 0, 1, 1);

        btn_note_dot = new QPushButton(tb_duration);
        btn_note_dot->setObjectName(QString::fromUtf8("btn_note_dot"));
        btn_note_dot->setMaximumSize(QSize(45, 45));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/punt.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_note_dot->setIcon(icon8);
        btn_note_dot->setIconSize(QSize(30, 30));
        btn_note_dot->setCheckable(true);

        gridLayout->addWidget(btn_note_dot, 3, 1, 1, 1);

        Controller->addItem(tb_duration, QString::fromUtf8("\346\227\266\345\200\274\346\216\247\345\210\266"));

        retranslateUi(Controller);

        Controller->setCurrentIndex(2);
        Controller->layout()->setSpacing(5);


        QMetaObject::connectSlotsByName(Controller);
    } // setupUi

    void retranslateUi(QToolBox *Controller)
    {
        Controller->setWindowTitle(QApplication::translate("Controller", "ToolBox", 0, QApplication::UnicodeUTF8));
        label_dp_key->setText(QString());
        label_dp_key_pic->setText(QString());
        label_key->setText(QApplication::translate("Controller", "\350\260\203\345\274\217", 0, QApplication::UnicodeUTF8));
        label_dp_meter->setText(QString());
        label_dp_meter_pic->setText(QString());
        label_meter->setText(QApplication::translate("Controller", "\350\212\202\346\213\215", 0, QApplication::UnicodeUTF8));
        btn_run->setText(QApplication::translate("Controller", "\345\274\200\345\247\213\347\274\226\350\276\221", 0, QApplication::UnicodeUTF8));
        Controller->setItemText(Controller->indexOf(tb_staff), QApplication::translate("Controller", "\344\271\220\350\260\261\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
        label_dp_channel->setText(QString());
        label_dp_velocity->setText(QString());
        label_dp_base_octave->setText(QString());
        label_dp_transpose->setText(QString());
        label_dp_speed->setText(QString());
        label_channel->setText(QApplication::translate("Controller", "\351\200\232\351\201\223", 0, QApplication::UnicodeUTF8));
        label_velocity->setText(QApplication::translate("Controller", "\345\212\233\345\272\246", 0, QApplication::UnicodeUTF8));
        label__base_octave->setText(QApplication::translate("Controller", "\345\237\272\345\207\206\n"
"\345\205\253\345\272\246", 0, QApplication::UnicodeUTF8));
        label_transpose->setText(QApplication::translate("Controller", "\345\217\230\350\260\203", 0, QApplication::UnicodeUTF8));
        label_speed->setText(QApplication::translate("Controller", "\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        Controller->setItemText(Controller->indexOf(tb_keybd), QApplication::translate("Controller", "Midi\346\216\247\345\210\266\345\231\250", 0, QApplication::UnicodeUTF8));
        btn_note_96->setText(QString());
        btn_note_48->setText(QString());
        btn_note_24->setText(QString());
        btn_note_12->setText(QString());
        btn_note_6->setText(QString());
        btn_note_3->setText(QString());
        btn_select->setText(QString());
        btn_note_dot->setText(QString());
        Controller->setItemText(Controller->indexOf(tb_duration), QApplication::translate("Controller", "\346\227\266\345\200\274\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Controller: public Ui_Controller {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLLER_H
