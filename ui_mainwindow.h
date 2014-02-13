/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Mar 12 11:54:53 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMIDI_controller;
    QAction *actionSave;
    QAction *undoAction;
    QAction *redoAction;
    QAction *chordAnalyse;
    QAction *actionPlayMidi;
    QAction *actionOpen;
    QAction *actionOpenMidi;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *widget_toolbox;
    QGridLayout *gridLayout_toolbox;
    QWidget *widget_keybd;
    QGridLayout *gridLayout_keybd;
    QWidget *widget_chord;
    QGridLayout *gridLayout_2;
    QPushButton *btn_0;
    QPushButton *btn_1;
    QPushButton *btn_2;
    QPushButton *btn_3;
    QPushButton *btn_4;
    QPushButton *btn_5;
    QPushButton *btn_6;
    QPushButton *btn_7;
    QPushButton *btn_8;
    QPushButton *btn_9;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/iconpent.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionMIDI_controller = new QAction(MainWindow);
        actionMIDI_controller->setObjectName(QString::fromUtf8("actionMIDI_controller"));
        actionMIDI_controller->setCheckable(true);
        actionMIDI_controller->setChecked(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/piano.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMIDI_controller->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        undoAction = new QAction(MainWindow);
        undoAction->setObjectName(QString::fromUtf8("undoAction"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        undoAction->setIcon(icon3);
        redoAction = new QAction(MainWindow);
        redoAction->setObjectName(QString::fromUtf8("redoAction"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        redoAction->setIcon(icon4);
        chordAnalyse = new QAction(MainWindow);
        chordAnalyse->setObjectName(QString::fromUtf8("chordAnalyse"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/wave.png"), QSize(), QIcon::Normal, QIcon::Off);
        chordAnalyse->setIcon(icon5);
        actionPlayMidi = new QAction(MainWindow);
        actionPlayMidi->setObjectName(QString::fromUtf8("actionPlayMidi"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPlayMidi->setIcon(icon6);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon7);
        actionOpenMidi = new QAction(MainWindow);
        actionOpenMidi->setObjectName(QString::fromUtf8("actionOpenMidi"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/iconproject.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenMidi->setIcon(icon8);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget_toolbox = new QWidget(centralWidget);
        widget_toolbox->setObjectName(QString::fromUtf8("widget_toolbox"));
        gridLayout_toolbox = new QGridLayout(widget_toolbox);
        gridLayout_toolbox->setSpacing(0);
        gridLayout_toolbox->setContentsMargins(0, 0, 0, 0);
        gridLayout_toolbox->setObjectName(QString::fromUtf8("gridLayout_toolbox"));

        gridLayout->addWidget(widget_toolbox, 0, 0, 2, 1);

        widget_keybd = new QWidget(centralWidget);
        widget_keybd->setObjectName(QString::fromUtf8("widget_keybd"));
        gridLayout_keybd = new QGridLayout(widget_keybd);
        gridLayout_keybd->setSpacing(0);
        gridLayout_keybd->setContentsMargins(0, 0, 0, 0);
        gridLayout_keybd->setObjectName(QString::fromUtf8("gridLayout_keybd"));

        gridLayout->addWidget(widget_keybd, 1, 1, 1, 1);

        widget_chord = new QWidget(centralWidget);
        widget_chord->setObjectName(QString::fromUtf8("widget_chord"));
        widget_chord->setMaximumSize(QSize(16777215, 30));
        gridLayout_2 = new QGridLayout(widget_chord);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        btn_0 = new QPushButton(widget_chord);
        btn_0->setObjectName(QString::fromUtf8("btn_0"));

        gridLayout_2->addWidget(btn_0, 0, 0, 1, 1);

        btn_1 = new QPushButton(widget_chord);
        btn_1->setObjectName(QString::fromUtf8("btn_1"));

        gridLayout_2->addWidget(btn_1, 0, 1, 1, 1);

        btn_2 = new QPushButton(widget_chord);
        btn_2->setObjectName(QString::fromUtf8("btn_2"));

        gridLayout_2->addWidget(btn_2, 0, 2, 1, 1);

        btn_3 = new QPushButton(widget_chord);
        btn_3->setObjectName(QString::fromUtf8("btn_3"));

        gridLayout_2->addWidget(btn_3, 0, 3, 1, 1);

        btn_4 = new QPushButton(widget_chord);
        btn_4->setObjectName(QString::fromUtf8("btn_4"));

        gridLayout_2->addWidget(btn_4, 0, 4, 1, 1);

        btn_5 = new QPushButton(widget_chord);
        btn_5->setObjectName(QString::fromUtf8("btn_5"));

        gridLayout_2->addWidget(btn_5, 0, 5, 1, 1);

        btn_6 = new QPushButton(widget_chord);
        btn_6->setObjectName(QString::fromUtf8("btn_6"));

        gridLayout_2->addWidget(btn_6, 0, 6, 1, 1);

        btn_7 = new QPushButton(widget_chord);
        btn_7->setObjectName(QString::fromUtf8("btn_7"));

        gridLayout_2->addWidget(btn_7, 0, 7, 1, 1);

        btn_8 = new QPushButton(widget_chord);
        btn_8->setObjectName(QString::fromUtf8("btn_8"));

        gridLayout_2->addWidget(btn_8, 0, 8, 1, 1);

        btn_9 = new QPushButton(widget_chord);
        btn_9->setObjectName(QString::fromUtf8("btn_9"));

        gridLayout_2->addWidget(btn_9, 0, 9, 1, 1);


        gridLayout->addWidget(widget_chord, 2, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 20));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(actionOpen);
        menu->addAction(actionSave);
        menu->addAction(actionOpenMidi);
        menu_2->addAction(actionMIDI_controller);
        menu_2->addSeparator();
        menu_2->addAction(undoAction);
        menu_2->addAction(redoAction);
        menu_2->addSeparator();
        menu_2->addAction(chordAnalyse);
        menu_2->addAction(actionPlayMidi);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionOpenMidi);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(chordAnalyse);
        mainToolBar->addAction(actionPlayMidi);
        mainToolBar->addAction(actionMIDI_controller);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\344\271\220\347\220\206\347\262\276\347\201\265", 0, QApplication::UnicodeUTF8));
        actionMIDI_controller->setText(QApplication::translate("MainWindow", "MIDI\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionMIDI_controller->setToolTip(QApplication::translate("MainWindow", "MIDI\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\344\271\220\350\260\261", 0, QApplication::UnicodeUTF8));
        undoAction->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200", 0, QApplication::UnicodeUTF8));
        undoAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
        redoAction->setText(QApplication::translate("MainWindow", "\351\207\215\345\244\215", 0, QApplication::UnicodeUTF8));
        redoAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", 0, QApplication::UnicodeUTF8));
        chordAnalyse->setText(QApplication::translate("MainWindow", "\345\222\214\345\274\246\345\210\206\346\236\220", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        chordAnalyse->setToolTip(QApplication::translate("MainWindow", "\345\222\214\345\274\246\345\210\206\346\236\220", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPlayMidi->setText(QApplication::translate("MainWindow", "\346\222\255\346\224\276MIDI", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\344\271\220\350\260\261", 0, QApplication::UnicodeUTF8));
        actionOpenMidi->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275MIDI", 0, QApplication::UnicodeUTF8));
        btn_0->setText(QApplication::translate("MainWindow", "\345\244\247\350\260\203\344\270\273\344\270\211", 0, QApplication::UnicodeUTF8));
        btn_1->setText(QApplication::translate("MainWindow", "\345\260\217\350\260\203\344\270\213\345\261\236\344\270\211", 0, QApplication::UnicodeUTF8));
        btn_2->setText(QApplication::translate("MainWindow", "\345\260\217\350\260\203\345\261\236\344\270\211", 0, QApplication::UnicodeUTF8));
        btn_3->setText(QApplication::translate("MainWindow", "\345\244\247\350\260\203\344\270\213\345\261\236\344\270\211", 0, QApplication::UnicodeUTF8));
        btn_4->setText(QApplication::translate("MainWindow", "\345\244\247\350\260\203\345\261\236\344\270\211", 0, QApplication::UnicodeUTF8));
        btn_5->setText(QApplication::translate("MainWindow", "\345\260\217\350\260\203\344\270\273\344\270\211", 0, QApplication::UnicodeUTF8));
        btn_6->setText(QApplication::translate("MainWindow", "\345\260\217\350\260\203\344\270\213\345\261\236\344\270\203", 0, QApplication::UnicodeUTF8));
        btn_7->setText(QApplication::translate("MainWindow", "\345\260\217\350\260\203\345\261\236\344\270\203", 0, QApplication::UnicodeUTF8));
        btn_8->setText(QApplication::translate("MainWindow", "\345\244\247\350\260\203\344\270\213\345\261\236\345\242\236\344\270\203", 0, QApplication::UnicodeUTF8));
        btn_9->setText(QApplication::translate("MainWindow", "\345\244\247\350\260\203\345\261\236\344\270\203", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("MainWindow", "\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
