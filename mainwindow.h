#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QKeyEvent>
#include <QScrollArea>
#include <QUndoGroup>
#include <QProcess>
#include "controller.h"
#include "rtmidi.h"
#include "rterror.h"
#include "pianokeybd.h"
#include "keyboardmap.h"
#include "octavekeybd.h"
#include "renderpartitura.h"
#include "staff/staff.h"
#include "staff/chordanalyst.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void noteOn(const int midiNote);
    void noteOff(const int midiNote);
    void pauseActive(int flag);

    void setChannelChanged(int channel);
    void setVelocityChanged(int velocity);
    void setBase_octaveChanged(int base_octave);
    void setTransposeChanged(int transpose);
    void setEditEnable(bool run);

    void editChord(QPoint p);

protected:
    void changeEvent(QEvent* e);

private:
    Ui::MainWindow *ui;
    OctaveKeybd *keybd;
    Controller *midiRef;
    RenderPartitura *rpStaff;
    QScrollArea *widget_staff;
    QPoint currentSel;

    int keybdChannel;
    int keybdVelocity;
    int keybdBase_octave;
    int keybdTranspose;

    RtMidiIn *midiIn;
    RtMidiOut *midiOut;
    KeyboardMap defaultMap;

    QUndoGroup *undoGroup;
    QProcess *newProcess;

    Partitura *partitura;
    QString *sharp;
    QString *flat;
    Compas *compasSharp;
    Compas *compasFlat;
    Nota *nota;
    CurrentStatus *currentStatus;
    Staff *staff;
    bool staffEditable;
    ChordAnalyst *cAnalyst;

    int loadKey;
    Meter loadMeter;

    void initKeybd();
    void initMidiController();
    void initStaff();
    void applyPreferences();
    Qt::Key switchKeys(int key);
    void messageWrapper(std::vector<unsigned char> *message) const;

private slots:
    void on_actionOpenMidi_triggered();
    void on_actionOpen_triggered();
    void on_actionPlayMidi_triggered();
    void on_btn_9_clicked();
    void on_btn_8_clicked();
    void on_btn_7_clicked();
    void on_btn_6_clicked();
    void on_btn_5_clicked();
    void on_btn_4_clicked();
    void on_btn_3_clicked();
    void on_btn_2_clicked();
    void on_btn_1_clicked();
    void on_btn_0_clicked();
    void on_chordAnalyse_triggered();
    void on_redoAction_triggered();
    void on_undoAction_triggered();
    void on_actionSave_triggered();
    void on_actionMIDI_controller_triggered(bool checked);
    void saveStaff();
    void loadStaff(QString fileName);
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif // MAINWINDOW_H
