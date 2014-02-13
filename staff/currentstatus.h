#ifndef CURRENTSTATUS_H
#define CURRENTSTATUS_H

#include <vector>

#include "music_element.h"

enum ChordLevelAndKind {MAJORTRIAD1, MINORTRIAD2, MINORTRIAD3, MAJORTRIAD4, MAJORTRIAD5, MINORTRIAD6,
                        MINORSEVENTHS2, MINORSEVENTHS3, ADDSEVENTHS4, MAJORSEVENTHS5};

class CurrentStatus
{
private:
    CurrentStatus();
    virtual ~CurrentStatus();
    static CurrentStatus* instance;
public:
    static CurrentStatus* Instance();

private:
    int key;
    Meter meter;
    int speed;
    int tone;
    int volume;

public:

    std::vector<int> getChordButton(ChordLevelAndKind lak);

    bool setKey(int skey);
    int getKey();

    bool setMeter(Meter smeter);
    Meter getMeter();

    bool setSpeed(int sspeed);
    int getSpeed();

    bool setTone(int stone);
    int getTone();

    bool setVolume(int svolume);
    int getVolume();
};

#endif // CURRENTSTATUS_H
