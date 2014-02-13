#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QToolBox>
#include <QVector>
#include <QButtonGroup>
#include "staff/staff.h"
#include "renderpartitura.h"

namespace Ui {
    class Controller;
}

class Controller : public QToolBox {
    Q_OBJECT
public:
    Controller(QWidget *parent = 0);
    ~Controller();

    int getCurrentChannel();
    int getCurrentVelocity();
    int getCurrentBase_octave();
    int getCurrentTranspose();
    int getCurrentSpeed();
    int getCurrentKey();
    void initController(int channel, int velocity, int base_octave, int transpose, int speed);
    void setDefaultDuration();

public slots:
    void setCurrentChannel(int channel);
    void setCurrentVelocity(int velocity);
    void setCurrentBase_octave(int base_octave);
    void setCurrentTranspose(int transpose);
    void setCurrentSpeed(int speed);
    void setCurrentMeter(Meter meter);
    void setCurrentKey(int key);

signals:
    void channelChanged(int channel);
    void velocityChanged(int velocity);
    void base_octaveChanged(int base_octave);
    void transposeChanged(int transpose);
    void enableEdit(bool run);
    void durationChanged(QAction *duration);
    void pauseFlag(int flag);
    void dotEnable(bool isDot);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Controller *ui;

    QAction *duration;
    QButtonGroup *durationGroup;
    CurrentStatus *currentStatus;

private slots:
    void on_btn_note_dot_clicked(bool checked);
    void on_btn_run_clicked();
    void on_slider_speed_valueChanged(int value);
    void on_slider_meter_valueChanged(int value);
    void on_slider_key_valueChanged(int value);
    void on_slider_transpose_valueChanged(int value);
    void on_slider_base_octave_valueChanged(int value);
    void on_slider_channel_valueChanged(int value);
    void on_slider_velocity_valueChanged(int value);

    void durationCheck(int btnID);
    void pauseCheck(int flag);
};

#endif // CONTROLLER_H
