#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "midiref.h"
#include "staff/staffdao.h"
#include <QtDebug>
#include <QtTest>
#include <QFileDialog>
#include <staff/MidiMaker.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentStatus = CurrentStatus::Instance();

    keybd = new OctaveKeybd(this);
    midiRef = new Controller(this);
    rpStaff = new RenderPartitura(this);
    widget_staff = new QScrollArea(this);
    undoGroup = new QUndoGroup();
    sharp = new QString("sharp");
    flat = new QString("flat");
    newProcess = new QProcess(this);

    ui->gridLayout->addWidget(widget_staff, 0, 1, 1, 1);
    currentSel.setX(-1);
    currentSel.setY(-1);
    widget_staff->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    widget_staff->setWidget(rpStaff);

    connect(keybd, SIGNAL(noteOn(int)), this, SLOT(noteOn(int)));
    connect(keybd, SIGNAL(noteOff(int)), this, SLOT(noteOff(int)));
    connect(keybd, SIGNAL(changeOctave(int)), midiRef, SLOT(setCurrentBase_octave(int)));
    connect(keybd, SIGNAL(changePause(int)), midiRef, SLOT(pauseCheck(int)));

    connect(midiRef, SIGNAL(channelChanged(int)), this, SLOT(setChannelChanged(int)));
    connect(midiRef, SIGNAL(velocityChanged(int)), this, SLOT(setVelocityChanged(int)));
    connect(midiRef, SIGNAL(base_octaveChanged(int)), this, SLOT(setBase_octaveChanged(int)));
    connect(midiRef, SIGNAL(transposeChanged(int)), this, SLOT(setTransposeChanged(int)));
    connect(midiRef, SIGNAL(enableEdit(bool)), this, SLOT(setEditEnable(bool)));
    connect(midiRef, SIGNAL(pauseFlag(int)), this, SLOT(pauseActive(int)));

    connect(newProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus)));

    initKeybd();
    initMidiController();
}
void MainWindow::initKeybd()
{
    defaultMap.insert(Qt::Key_A, 5);
    defaultMap.insert(Qt::Key_W, 6);
    defaultMap.insert(Qt::Key_S, 7);
    defaultMap.insert(Qt::Key_E, 8);
    defaultMap.insert(Qt::Key_D, 9);
    defaultMap.insert(Qt::Key_R, 10);
    defaultMap.insert(Qt::Key_F, 11);
    defaultMap.insert(Qt::Key_G, 12);
    defaultMap.insert(Qt::Key_Y, 13);
    defaultMap.insert(Qt::Key_H, 14);
    defaultMap.insert(Qt::Key_U, 15);
    defaultMap.insert(Qt::Key_J, 16);
    defaultMap.insert(Qt::Key_K, 17);
    defaultMap.insert(Qt::Key_O, 18);
    defaultMap.insert(Qt::Key_L, 19);
    defaultMap.insert(Qt::Key_P, 20);
    defaultMap.insert(Qt::Key_Semicolon, 21);
    defaultMap.insert(Qt::Key_BracketLeft, 22);
    defaultMap.insert(Qt::Key_Apostrophe, 23);
    keybd->setKeyboardMap(&defaultMap);
    keybd->grabKeyboard();
    keybd->setNumOctaves(3);
    keybd->setShowLabels(true);
    ui->gridLayout_keybd->addWidget(keybd);
    ui->widget_keybd->setEnabled(false);
    ui->widget_chord->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->chordAnalyse->setEnabled(false);
}
void MainWindow::initMidiController()
{
    this->midiRef->initController(1, 127, 3, 0, 90);
    ui->gridLayout_toolbox->addWidget(this->midiRef);
    widget_staff->setEnabled(false);

    midiIn = new RtMidiIn("Piano Input");
    midiOut = new RtMidiOut("Piano Output");
    midiOut->openPort(0);
}
void MainWindow::initStaff()
{
    // par1: 15px
    // par2: 145px
    widget_staff->setWidget(NULL);
    rpStaff->~QObject();

    partitura = new Partitura(sharp, 1);
    partitura->setAuxPent(new Partitura(flat, 2));
    undoGroup->addStack(partitura->getUndoStack());

    rpStaff = new RenderPartitura(midiRef->getCurrentKey(), currentStatus->getMeter(), partitura, this);
    widget_staff->setWidget(rpStaff);
    connect(midiRef, SIGNAL(durationChanged(QAction*)), rpStaff, SLOT(changeCursor(QAction*)));
    connect(midiRef, SIGNAL(dotEnable(bool)), rpStaff, SLOT(setPuntillo(bool)));
    connect(rpStaff, SIGNAL(addChord(QPoint)), this, SLOT(editChord(QPoint)));

    partitura->addCompas(new Compas());
    partitura->addCompas(new Compas());
    partitura->getAuxPent()->addCompas(new Compas());
    partitura->getAuxPent()->addCompas(new Compas());

    midiRef->setDefaultDuration();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::setChannelChanged(int channel)
{
    this->keybdChannel = channel;

}
void MainWindow::setVelocityChanged(int velocity)
{
    this->keybdVelocity = velocity;
    this->keybd->setVelocity(velocity);
}
void MainWindow::setBase_octaveChanged(int base_octave)
{
    this->keybdBase_octave = base_octave;
    this->keybd->setBaseOctave(base_octave);
}
void MainWindow::setTransposeChanged(int transpose)
{
    this->keybdTranspose = transpose;
    this->keybd->setTranspose(transpose);
}
void MainWindow::setEditEnable(bool run)
{
    initStaff();
    ui->widget_keybd->setEnabled(run);
    ui->widget_chord->setEnabled(run);
    ui->actionSave->setEnabled(run);
    ui->chordAnalyse->setEnabled(run);
    widget_staff->setEnabled(run);
}

void MainWindow::noteOn(const int midiNote)
{
    int lastNote = this->widget_staff->widget()->width()-10;
    this->widget_staff->ensureVisible(lastNote, 0);
    std::vector<unsigned char> message;
    if((midiNote & MASK_SAFETY) == midiNote) {
        unsigned char chan = static_cast<unsigned char>(keybdChannel);
        unsigned char vel = static_cast<unsigned char>(keybdVelocity);
        message.push_back(STATUS_NOTEON + (chan & MASK_CHANNEL));
        message.push_back(midiNote & MASK_SAFETY);
        message.push_back(vel & MASK_SAFETY);
        messageWrapper( &message );
    }
    if(!this->staffEditable)
        return;
    if(currentSel == QPoint(-1, -1)) {
        if(midiNote>47) {
            if(rpStaff->isCompasCompleto(partitura)) {
                partitura->addCompas(new Compas());
                partitura->getAuxPent()->addCompas(new Compas());
                this->rpStaff->addNota(midiNote, PARTITURA1, COMPLETO);
            } else {
                this->rpStaff->addNota(midiNote, PARTITURA1, INCOMPLETO);
            }
        } else if(midiNote<48 && midiNote>-1){
            if(rpStaff->isCompasCompleto(partitura->getAuxPent())) {
                partitura->addCompas(new Compas());
                partitura->getAuxPent()->addCompas(new Compas());
                this->rpStaff->addNota(midiNote, PARTITURA2, COMPLETO);
            } else {
                this->rpStaff->addNota(midiNote, PARTITURA2, INCOMPLETO);
            }
        } else if(midiNote == -1){
            if(rpStaff->isCompasCompleto(partitura)) {
                partitura->addCompas(new Compas());
                partitura->getAuxPent()->addCompas(new Compas());
                this->rpStaff->addPause(PARTITURA1, COMPLETO);
            } else {
                this->rpStaff->addPause(PARTITURA1, INCOMPLETO);
            }
        } else if(midiNote == -2){
            if(rpStaff->isCompasCompleto(partitura->getAuxPent())) {
                partitura->addCompas(new Compas());
                partitura->getAuxPent()->addCompas(new Compas());
                this->rpStaff->addPause(PARTITURA2, COMPLETO);
            } else {
                this->rpStaff->addPause(PARTITURA2, INCOMPLETO);
            }
        }
    } else {
        if(midiNote>47) {
            this->rpStaff->addNota(midiNote, PARTITURA1, currentSel);
        } else if(midiNote<48 && midiNote>-1){
            this->rpStaff->addNota(midiNote, PARTITURA2, currentSel);
        }
    }
}
void MainWindow::noteOff(const int midiNote)
{
    std::vector<unsigned char> message;
    if((midiNote & MASK_SAFETY) == midiNote) {
        unsigned char chan = static_cast<unsigned char>(keybdChannel);
        unsigned char vel = static_cast<unsigned char>(keybdVelocity);
        message.push_back(STATUS_NOTEOFF + (chan & MASK_CHANNEL));
        message.push_back(midiNote & MASK_SAFETY);
        message.push_back(vel & MASK_SAFETY);
        messageWrapper( &message );
    }
}
void MainWindow::pauseActive(int flag)
{
    noteOn(flag);
}
void MainWindow::editChord(QPoint p)
{
    currentSel = p;
}
void MainWindow::messageWrapper(std::vector<unsigned char> *message) const
{
    try {
        midiOut->sendMessage( message );
    } catch (RtError& err) {
        ui->statusBar->showMessage(QString::fromStdString(err.getMessage()));
    }
}
void MainWindow::on_actionMIDI_controller_triggered(bool checked)
{
    if(checked) {
        ui->widget_toolbox->show();
    } else {
        ui->widget_toolbox->hide();
    }
}
void MainWindow::on_actionSave_triggered()
{
    this->saveStaff();
    QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf8("保存"),
                                "./",
                                QString::fromUtf8("XML 文件 (*.xml)"));
    if(!fileName.isEmpty()) {
        staff->save(fileName.toStdString().c_str());
        delete staff;
    }
}
void MainWindow::on_undoAction_triggered()
{
    undoGroup->undo();
}
void MainWindow::on_redoAction_triggered()
{
    undoGroup->redo();
}
void MainWindow::on_chordAnalyse_triggered()
{
    widget_staff->setEnabled(false);
    ui->widget_keybd->setEnabled(false);
    this->saveStaff();

    cAnalyst = new ChordAnalyst();
    std::vector<std::vector<std::string> > result = cAnalyst->machingStaveChords(*staff);

    rpStaff->setChordText(result);
    widget_staff->setEnabled(true);
    ui->widget_keybd->setEnabled(true);
    delete staff;
}
void MainWindow::saveStaff()
{
    staff = new Staff();
    currentStatus->setSpeed(midiRef->getCurrentSpeed());
    for(int c=0; c<this->partitura->getCompases()->size(); c++) {
        Compas *cTemp1 = this->partitura->getCompases()->at(c);
        int position = 0;
        for(int n=0; n<cTemp1->getNotas()->size(); n++) {
            Nota *nTemp = cTemp1->getNotas()->at(n);
            int duration = 96/nTemp->getDuracion();
            int rTono = nTemp->getRTono();
            if(rTono != -1) {
                staff->addNote(nTemp->getRTono(), duration, position, c);
                for(int ch=0; ch<nTemp->getChord()->size(); ch++) {
                    staff->addNote(nTemp->getChord()->at(ch)->getRTono(), duration, position, c);
                }
            }
            position += duration;
        }

        Compas *cTemp2 = this->partitura->getAuxPent()->getCompases()->at(c);
        position = 0;
        for(int n=0; n<cTemp2->getNotas()->size(); n++) {
            Nota *nTemp = cTemp2->getNotas()->at(n);
            int duration = 96/nTemp->getDuracion();
            int rTono = nTemp->getRTono();
            if(rTono != -1) {
                staff->addNote(nTemp->getRTono(), duration, position, c);
                for(int ch=0; ch<nTemp->getChord()->size(); ch++) {
                    staff->addNote(nTemp->getChord()->at(ch)->getRTono(), duration, position, c);
                }
            }
            position += duration;
        }
    }
}

void MainWindow::loadStaff(QString fileName)
{
    if(!fileName.isEmpty()) {
        staff = new Staff();
        staff->load(fileName.toStdString().c_str());
    }
//    delete partitura->getAuxPent();
//    delete partitura;
    this->partitura = new Partitura(&QString("sharp"), 1);
    this->partitura->setAuxPent(new Partitura(&QString("flat"), 2));
    std::vector<Bar> bars = staff->getBars();
    for(int i=0; i<bars.size(); i++) {
        Bar bTemp = bars[i];
        QVector<Note> bTemp1;
        QVector<Note> bTemp2;
        std::list<Note>::iterator iNote = bTemp.notes.begin();
        while(iNote!=bTemp.notes.end()) {
            if(iNote->pitch < 48) {
                bTemp2.push_back(*iNote);
            } else {
                bTemp1.push_back(*iNote);
            }
            iNote++;
        }        
        int barDuration = 0;
        if (bTemp.meter == FOUR2) {
            midiRef->setCurrentMeter(FOUR2);
            barDuration = 48;
        } else if (bTemp.meter == FOUR3) {
            midiRef->setCurrentMeter(FOUR3);
            barDuration = 72;
        } else if (bTemp.meter == FOUR4) {
            midiRef->setCurrentMeter(FOUR4);
            barDuration = 96;
        } else if (bTemp.meter == EIGHT6) {
            midiRef->setCurrentMeter(EIGHT6);
            barDuration = 72;
        }
        midiRef->setCurrentKey(bTemp.key);

        Compas *cTemp1 = new Compas();
        Compas *cTemp2 = new Compas();
        this->partitura->addCompas(cTemp1);
        this->partitura->getAuxPent()->addCompas(cTemp2);
        Note preNote;
        preNote.duration = 0;
        preNote.pitch = 0;
        preNote.position = 0;
        preNote.tone = 0;
        preNote.volume = -1;
        int waitDuration = 0;
        for(int bt1 = 0; bt1<bTemp1.size(); bt1++) {
            Nota *aTemp = new Nota(cTemp1);

            waitDuration = bTemp1[bt1].position - (preNote.position + preNote.duration);
            if (waitDuration > 0)
            {
                aTemp->setRTono(-1);
                aTemp->setSilencio(true);
                aTemp->setDuracion(StaffDao::durationDao(waitDuration));
                cTemp1->addNota(aTemp);
            }

            if ((bTemp1[bt1].position == preNote.position) &&(preNote.volume != -1))
            {
                QList<Note> noteList;
                noteList.append(bTemp1[bt1]);
                bt1++;
                while((bTemp1[bt1].position == preNote.position) && (bt1<bTemp1.size()))
                {
                    noteList.append(bTemp1[bt1]);
                    bt1++;
                }
                bt1--;

                QList<Nota*> notaList;
                foreach(Note note, noteList) {
                    Nota *chordNota = new Nota(cTemp1);
                    chordNota->setDuracion(StaffDao::durationDao(note.duration));
                    chordNota->setRTono(note.pitch);
                    chordNota->setTono(StaffDao::pitchDao(note.pitch));
                    notaList.append(chordNota);
                }
                cTemp1->getNotas()->last()->setChord(&notaList);

            } else {
                aTemp = new Nota(cTemp1);
                aTemp->setSilencio(false);
                aTemp->setRTono(bTemp1[bt1].pitch);
                aTemp->setDuracion(StaffDao::durationDao(bTemp1[bt1].duration));
                aTemp->setTono(StaffDao::pitchDao(bTemp1[bt1].pitch));
                cTemp1->addNota(aTemp);
            }
            preNote = (bTemp1[bt1]);
        }
        waitDuration = barDuration - (preNote.position + preNote.duration);
        if (waitDuration > 0)
        {
            Nota *sNota = new Nota(cTemp1);
            sNota->setDuracion(StaffDao::durationDao(waitDuration));
            sNota->setRTono(-1);
            cTemp1->addNota(sNota);
        }

        preNote.duration = 0;
        preNote.pitch = 0;
        preNote.position = 0;
        preNote.tone = 0;
        preNote.volume = -1;
        waitDuration = 0;
        for(int bt2 = 0; bt2<bTemp2.size(); bt2++) {
            Nota *aTemp = new Nota(cTemp2);

            waitDuration = bTemp2[bt2].position - (preNote.position + preNote.duration);
            if (waitDuration > 0)
            {
                aTemp->setRTono(-1);
                aTemp->setSilencio(true);
                aTemp->setDuracion(StaffDao::durationDao(waitDuration));
                cTemp2->addNota(aTemp);
            }

            if ((bTemp2[bt2].position == preNote.position) &&(preNote.volume != -1))
            {
                QList<Note> noteList;
                noteList.append(bTemp2[bt2]);
                bt2++;
                while((bTemp2[bt2].position == preNote.position) && (bt2<bTemp2.size()))
                {
                    noteList.append(bTemp2[bt2]);
                    bt2++;
                }
                bt2--;

                QList<Nota*> notaList;
                foreach(Note note, noteList) {
                    Nota *chordNota = new Nota(cTemp2);
                    chordNota->setDuracion(StaffDao::durationDao(note.duration));
                    chordNota->setRTono(note.pitch);
                    chordNota->setTono(StaffDao::pitchDao(note.pitch));
                    notaList.append(chordNota);
                }
                cTemp2->getNotas()->last()->setChord(&notaList);


            } else {
                aTemp = new Nota(cTemp2);
                aTemp->setSilencio(false);
                aTemp->setRTono(bTemp2[bt2].pitch);
                aTemp->setDuracion(StaffDao::durationDao(bTemp2[bt2].duration));
                aTemp->setTono(StaffDao::pitchDao(bTemp2[bt2].pitch));
                cTemp2->addNota(aTemp);
            }
            preNote = (bTemp2[bt2]);
        }
        waitDuration = barDuration - (preNote.position + preNote.duration);
        if (waitDuration > 0)
        {
            Nota *sNota = new Nota(cTemp2);
            sNota->setDuracion(StaffDao::durationDao(waitDuration));
            sNota->setRTono(-1);
            cTemp2->addNota(sNota);
        }
    }
}
void MainWindow::on_btn_0_clicked()
{
    this->staffEditable = false;
    std::vector<int> keys = currentStatus->getChordButton(MAJORTRIAD1);
    for(int i=0; i<keys.size(); i++) {
        QTest::keyPress(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    QTest::keyRelease(keybd, this->switchKeys(keys[0]), Qt::NoModifier, 1000);
    for(int i=1; i<keys.size(); i++) {
        QTest::keyRelease(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    this->staffEditable = true;
}

void MainWindow::on_btn_1_clicked()
{
    this->staffEditable = false;
    std::vector<int> keys = currentStatus->getChordButton(MINORTRIAD2);
    for(int i=0; i<keys.size(); i++) {
        QTest::keyPress(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    QTest::keyRelease(keybd, this->switchKeys(keys[0]), Qt::NoModifier, 1000);
    for(int i=1; i<keys.size(); i++) {
        QTest::keyRelease(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    this->staffEditable = true;
}

void MainWindow::on_btn_2_clicked()
{
    this->staffEditable = false;
    std::vector<int> keys = currentStatus->getChordButton(MINORTRIAD3);
    for(int i=0; i<keys.size(); i++) {
        QTest::keyPress(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    QTest::keyRelease(keybd, this->switchKeys(keys[0]), Qt::NoModifier, 1000);
    for(int i=1; i<keys.size(); i++) {
        QTest::keyRelease(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    this->staffEditable = true;
}

void MainWindow::on_btn_3_clicked()
{
    this->staffEditable = false;
    std::vector<int> keys = currentStatus->getChordButton(MAJORTRIAD4);
    for(int i=0; i<keys.size(); i++) {
        QTest::keyPress(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    QTest::keyRelease(keybd, this->switchKeys(keys[0]), Qt::NoModifier, 1000);
    for(int i=1; i<keys.size(); i++) {
        QTest::keyRelease(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    this->staffEditable = true;
}

void MainWindow::on_btn_4_clicked()
{
    this->staffEditable = false;
    std::vector<int> keys = currentStatus->getChordButton(MAJORTRIAD5);
    for(int i=0; i<keys.size(); i++) {
        QTest::keyPress(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    QTest::keyRelease(keybd, this->switchKeys(keys[0]), Qt::NoModifier, 1000);
    for(int i=1; i<keys.size(); i++) {
        QTest::keyRelease(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    this->staffEditable = true;
}

void MainWindow::on_btn_5_clicked()
{
    this->staffEditable = false;
    std::vector<int> keys = currentStatus->getChordButton(MINORTRIAD6);
    for(int i=0; i<keys.size(); i++) {
        QTest::keyPress(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    QTest::keyRelease(keybd, this->switchKeys(keys[0]), Qt::NoModifier, 1000);
    for(int i=1; i<keys.size(); i++) {
        QTest::keyRelease(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    this->staffEditable = true;
}

void MainWindow::on_btn_6_clicked()
{
    this->staffEditable = false;
    std::vector<int> keys = currentStatus->getChordButton(MINORSEVENTHS2);
    for(int i=0; i<keys.size(); i++) {
        QTest::keyPress(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    QTest::keyRelease(keybd, this->switchKeys(keys[0]), Qt::NoModifier, 1000);
    for(int i=1; i<keys.size(); i++) {
        QTest::keyRelease(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    this->staffEditable = true;
}

void MainWindow::on_btn_7_clicked()
{
    this->staffEditable = false;
    std::vector<int> keys = currentStatus->getChordButton(MINORSEVENTHS3);
    for(int i=0; i<keys.size(); i++) {
        QTest::keyPress(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    QTest::keyRelease(keybd, this->switchKeys(keys[0]), Qt::NoModifier, 1000);
    for(int i=1; i<keys.size(); i++) {
        QTest::keyRelease(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    this->staffEditable = true;
}

void MainWindow::on_btn_8_clicked()
{
    this->staffEditable = false;
    std::vector<int> keys = currentStatus->getChordButton(ADDSEVENTHS4);
    for(int i=0; i<keys.size(); i++) {
        QTest::keyPress(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    QTest::keyRelease(keybd, this->switchKeys(keys[0]), Qt::NoModifier, 1000);
    for(int i=1; i<keys.size(); i++) {
        QTest::keyRelease(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    this->staffEditable = true;
}

void MainWindow::on_btn_9_clicked()
{
    this->staffEditable = false;
    std::vector<int> keys = currentStatus->getChordButton(MAJORSEVENTHS5);
    for(int i=0; i<keys.size(); i++) {
        QTest::keyPress(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    QTest::keyRelease(keybd, this->switchKeys(keys[0]), Qt::NoModifier, 1000);
    for(int i=1; i<keys.size(); i++) {
        QTest::keyRelease(keybd, this->switchKeys(keys[i]), Qt::NoModifier, 0);
    }
    this->staffEditable = true;
}

Qt::Key MainWindow::switchKeys(int key)
{
    switch(key) {
    case 0: return Qt::Key_G;
    case 1: return Qt::Key_Y;
    case 2: return Qt::Key_H;
    case 3: return Qt::Key_U;
    case 4: return Qt::Key_J;
    case 5: return Qt::Key_K;
    case 6: return Qt::Key_O;
    case 7: return Qt::Key_L;
    case 8: return Qt::Key_P;
    case 9: return Qt::Key_Semicolon;
    case 10: return Qt::Key_BracketLeft;
    case 11: return Qt::Key_Apostrophe;
    }
}

void MainWindow::on_actionPlayMidi_triggered()
{
    this->saveStaff();
    CMidiMaker maker;
    maker.makeMidi(*staff,"ourMid.mid");
    newProcess->start("./MIDIPlay.exe");
    this->setEnabled(false);
}

void MainWindow::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    this->setEnabled(true);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf8("打开文件"),
                                                    "./",
                                                    QString::fromUtf8("XML文件 (*.xml)"));
    if(!fileName.isEmpty()) {
        this->loadStaff(fileName);
        widget_staff->setWidget(NULL);
        rpStaff->~QObject();

        undoGroup->addStack(partitura->getUndoStack());

        rpStaff = new RenderPartitura(StaffDao::keyDao(currentStatus->getKey()), currentStatus->getMeter(), partitura, this);
        widget_staff->setWidget(rpStaff);
        connect(midiRef, SIGNAL(durationChanged(QAction*)), rpStaff, SLOT(changeCursor(QAction*)));
        connect(midiRef, SIGNAL(dotEnable(bool)), rpStaff, SLOT(setPuntillo(bool)));
        connect(rpStaff, SIGNAL(addChord(QPoint)), this, SLOT(editChord(QPoint)));

        partitura->addCompas(new Compas());
        partitura->getAuxPent()->addCompas(new Compas());

        midiRef->setDefaultDuration();
        ui->widget_keybd->setEnabled(true);
        ui->widget_chord->setEnabled(true);
        ui->actionSave->setEnabled(true);
        ui->chordAnalyse->setEnabled(true);
        widget_staff->setEnabled(true);
    }
}

void MainWindow::on_actionOpenMidi_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf8("打开文件"),
                                                    "./",
                                                    QString::fromUtf8("MIDI文件 (*.mid)"));
    if(!fileName.isEmpty()) {
        CMidiMaker maker;
        this->staff = maker.makeStaff(fileName.toStdString());
        this->loadStaff("");

        widget_staff->setWidget(NULL);
        rpStaff->~QObject();

        undoGroup->addStack(partitura->getUndoStack());

        rpStaff = new RenderPartitura(StaffDao::keyDao(currentStatus->getKey()), currentStatus->getMeter(), partitura, this);
        widget_staff->setWidget(rpStaff);
        connect(midiRef, SIGNAL(durationChanged(QAction*)), rpStaff, SLOT(changeCursor(QAction*)));
        connect(midiRef, SIGNAL(dotEnable(bool)), rpStaff, SLOT(setPuntillo(bool)));
        connect(rpStaff, SIGNAL(addChord(QPoint)), this, SLOT(editChord(QPoint)));

        partitura->addCompas(new Compas());
        partitura->getAuxPent()->addCompas(new Compas());

        midiRef->setDefaultDuration();
        ui->widget_keybd->setEnabled(true);
        ui->widget_chord->setEnabled(true);
        ui->actionSave->setEnabled(true);
        ui->chordAnalyse->setEnabled(true);
        widget_staff->setEnabled(true);
    }
}
