#include "controller.h"
#include "ui_controller.h"

Controller::Controller(QWidget *parent) :
    QToolBox(parent),
    ui(new Ui::Controller)
{
    ui->setupUi(this);

    durationGroup = new QButtonGroup(this);
    durationGroup->addButton(ui->btn_select, -8);
    durationGroup->addButton(ui->btn_note_96, -2);
    durationGroup->addButton(ui->btn_note_48, -3);
    durationGroup->addButton(ui->btn_note_24, -4);
    durationGroup->addButton(ui->btn_note_12, -5);
    durationGroup->addButton(ui->btn_note_6, -6);
    durationGroup->addButton(ui->btn_note_3, -7);

    currentStatus = CurrentStatus::Instance();
    connect(durationGroup, SIGNAL(buttonClicked(int)), this, SLOT(durationCheck(int)));
}

Controller::~Controller()
{
    delete ui;
}

void Controller::initController(int channel, int velocity, int base_octave, int transpose, int speed)
{
    setCurrentChannel(channel);
    setCurrentVelocity(velocity);
    setCurrentBase_octave(base_octave);
    setCurrentTranspose(transpose);
    setCurrentSpeed(speed);

    ui->label_dp_key_pic->setPixmap(QPixmap(":/images/C Major_A Minor.jpg"));
    ui->label_dp_key->setText("C Major | A Minor");
    ui->btn_note_24->setChecked(true);
    ui->label_dp_meter_pic->setPixmap(QPixmap(":/images/4_4.png"));
    ui->label_dp_meter->setText(QString::fromUtf8("4/4拍"));

    currentStatus->setKey(0);
    currentStatus->setMeter(FOUR4);
    currentStatus->setSpeed(speed);
    currentStatus->setTone(1);
    currentStatus->setVolume(velocity);
}
void Controller::setDefaultDuration()
{
    ui->btn_note_24->click();
}
void Controller::changeEvent(QEvent *e)
{
    QToolBox::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Controller::on_slider_channel_valueChanged(int value)
{
    ui->label_dp_channel->setNum(value);
    emit this->channelChanged(value);
}
void Controller::on_slider_velocity_valueChanged(int value)
{
    ui->label_dp_velocity->setNum(value);
    currentStatus->setVolume(value);
    emit this->velocityChanged(value);
}
void Controller::on_slider_base_octave_valueChanged(int value)
{
    ui->label_dp_base_octave->setNum(value);
    emit this->base_octaveChanged(value);
}
void Controller::on_slider_transpose_valueChanged(int value)
{
    ui->label_dp_transpose->setNum(value);
    emit this->transposeChanged(value);
}
void Controller::on_slider_speed_valueChanged(int value)
{
    ui->label_dp_speed->setNum(value);
    currentStatus->setSpeed(value);
}

int Controller::getCurrentChannel()
{
    return ui->slider_channel->value();
}
int Controller::getCurrentVelocity()
{
    return ui->slider_velocity->value();
}
int Controller::getCurrentBase_octave()
{
    return ui->slider_base_octave->value();
}
int Controller::getCurrentTranspose()
{
    return ui->slider_transpose->value();
}
int Controller::getCurrentSpeed()
{
    return ui->slider_speed->value();
}
int Controller::getCurrentKey()
{
    return ui->slider_key->value();
}

void Controller::setCurrentChannel(int channel)
{
    ui->slider_channel->setValue(channel);
    ui->label_dp_channel->setNum(channel);
    emit this->channelChanged(channel);
}
void Controller::setCurrentVelocity(int velocity)
{
    ui->slider_velocity->setValue(velocity);
    ui->label_dp_velocity->setNum(velocity);
    emit this->velocityChanged(velocity);
}
void Controller::setCurrentBase_octave(int base_octave)
{
    ui->slider_base_octave->setValue(base_octave);
    ui->label_dp_base_octave->setNum(base_octave);
    emit this->base_octaveChanged(base_octave);
}
void Controller::setCurrentTranspose(int transpose)
{
    ui->slider_transpose->setValue(transpose);
    ui->label_dp_transpose->setNum(transpose);
    emit this->transposeChanged(transpose);
}
void Controller::setCurrentSpeed(int speed)
{
    ui->slider_speed->setValue(speed);
    ui->label_dp_speed->setNum(speed);
    currentStatus->setSpeed(speed);
}
void Controller::setCurrentMeter(Meter meter)
{
    ui->slider_meter->setValue(meter+1);
}
void Controller::setCurrentKey(int key)
{
    switch(key) {
    case 0:
        ui->slider_key->setValue(0);
        break;
    case 1:
        ui->slider_key->setValue(-5);
        break;
    case 2:
        ui->slider_key->setValue(2);
        break;
    case 3:
        ui->slider_key->setValue(-3);
        break;
    case 4:
        ui->slider_key->setValue(4);
        break;
    case 5:
        ui->slider_key->setValue(-1);
        break;
    case 6:
        ui->slider_key->setValue(6);
        break;
    case 7:
        ui->slider_key->setValue(1);
        break;
    case 8:
        ui->slider_key->setValue(-4);
        break;
    case 9:
        ui->slider_key->setValue(3);
        break;
    case 10:
        ui->slider_key->setValue(-2);
        break;
    case 11:
        ui->slider_key->setValue(5);
        break;
    }
}
void Controller::on_slider_key_valueChanged(int value)
{
    switch(value) {
    case -7:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/Cb Major_Ab.jpg"));
        ui->label_dp_key->setText("Cb Major | Ab");
        currentStatus->setKey(11);
        break;
    case -6:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/Gb Major_Eb.jpg"));
        ui->label_dp_key->setText("Gb Major | Eb");
        currentStatus->setKey(6);
        break;
    case -5:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/Db Major_Bb.jpg"));
        ui->label_dp_key->setText("Db Major | Bb");
        currentStatus->setKey(1);
        break;
    case -4:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/Ab Major_F.jpg"));
        ui->label_dp_key->setText("Ab Major | F");
        currentStatus->setKey(8);
        break;
    case -3:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/Eb Major_C.jpg"));
        ui->label_dp_key->setText("Eb Major | C");
        currentStatus->setKey(3);
        break;
    case -2:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/Bb Major_G.jpg"));
        ui->label_dp_key->setText("Bb Major | Gb");
        currentStatus->setKey(10);
        break;
    case -1:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/F Major_D Minor.jpg"));
        ui->label_dp_key->setText("F Major | D Minor");
        currentStatus->setKey(5);
        break;
    case 0:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/C Major_A Minor.jpg"));
        ui->label_dp_key->setText("C Major | A Minor");
        currentStatus->setKey(0);
        break;
    case  1:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/G Major_E Minor.jpg"));
        ui->label_dp_key->setText("G Major | E Minor");
        currentStatus->setKey(7);
        break;
    case  2:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/D Major_B Minor.jpg"));
        ui->label_dp_key->setText("D Major | B Minor");
        currentStatus->setKey(2);
        break;
    case  3:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/A Major_F#.jpg"));
        ui->label_dp_key->setText("A Major | F#");
        currentStatus->setKey(9);
        break;
    case  4:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/E Major_C#.jpg"));
        ui->label_dp_key->setText("E Major | C#");
        currentStatus->setKey(4);
        break;
    case  5:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/B Major_G#.jpg"));
        ui->label_dp_key->setText("B Major | G#");
        currentStatus->setKey(11);
        break;
    case  6:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/F# Major_D#.jpg"));
        ui->label_dp_key->setText("F# Major | D#");
        currentStatus->setKey(6);
        break;
    case  7:
        ui->label_dp_key_pic->setPixmap(QPixmap(":/images/C# Major_A#.jpg"));
        ui->label_dp_key->setText("C# Major | A#");
        currentStatus->setKey(1);
        break;
    }
}

void Controller::durationCheck(int btnID)
{
    duration = new QAction(this);
    switch(btnID) {
    case -8:
        duration->setData(select);
        break;
    case -2:
        duration->setData(redonda);
        break;
    case -3:
        duration->setData(blanca);
        break;
    case -4:
        duration->setData(negra);
        break;
    case -5:
        duration->setData(corchea);
        break;
    case -6:
        duration->setData(semicorchea);
        break;
    case -7:
        duration->setData(fusa);
        break;
    }
    emit this->durationChanged(duration);
}
void Controller::pauseCheck(int flag)
{
    duration = new QAction(this);
    switch(durationGroup->checkedId()) {
    case -8:
        duration->setData(select);
        break;
    case -2:
        duration->setData(s1);
        break;
    case -3:
        duration->setData(s2);
        break;
    case -4:
        duration->setData(s4);
        break;
    case -5:
        duration->setData(s8);
        break;
    case -6:
        duration->setData(s16);
        break;
    case -7:
        duration->setData(s32);
        break;
    }
    emit this->durationChanged(duration);
    emit this->pauseFlag(flag);
}

void Controller::on_slider_meter_valueChanged(int value)
{
    switch(value) {
    case 1:
        ui->label_dp_meter_pic->setPixmap(QPixmap(":images/2_4.png"));
        ui->label_dp_meter->setText(QString::fromUtf8("2/4拍"));
        currentStatus->setMeter(FOUR2);
        break;
    case 2:
        ui->label_dp_meter_pic->setPixmap(QPixmap(":images/3_4.png"));
        ui->label_dp_meter->setText(QString::fromUtf8("3/4拍"));
        currentStatus->setMeter(FOUR3);
        break;
    case 3:
        ui->label_dp_meter_pic->setPixmap(QPixmap(":images/4_4.png"));
        ui->label_dp_meter->setText(QString::fromUtf8("4/4拍"));
        currentStatus->setMeter(FOUR4);
        break;
    case 4:
        ui->label_dp_meter_pic->setPixmap(QPixmap(":images/6_8.png"));
        ui->label_dp_meter->setText(QString::fromUtf8("6/8拍"));
        currentStatus->setMeter(EIGHT6);
        break;
    }
}


void Controller::on_btn_run_clicked()
{
    this->currentWidget()->setEnabled(false);
    this->setCurrentIndex(1);
    emit this->enableEdit(true);
}

void Controller::on_btn_note_dot_clicked(bool checked)
{
    emit this->dotEnable(checked);
}
