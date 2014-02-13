#include "currentstatus.h"

using namespace std;

CurrentStatus* CurrentStatus::instance = NULL;

CurrentStatus::CurrentStatus()
{
}

CurrentStatus::~CurrentStatus()
{
    if (NULL != instance)
    {
        delete instance;
    }
}

CurrentStatus* CurrentStatus::Instance()
{
    if (NULL == instance)
    {
        instance = new CurrentStatus();
    }
    return instance;
}

bool CurrentStatus::setKey(int skey)
{
    key = skey;
    return true;
}

int CurrentStatus::getKey()
{
    return key;
}

bool CurrentStatus::setMeter(Meter smeter)
{
    meter = smeter;
    return true;
}

Meter CurrentStatus::getMeter()
{
    return meter;
}

bool CurrentStatus::setSpeed(int sspeed)
{
    if (sspeed < 0)
        return false;

    speed = sspeed;
    return true;
}

int CurrentStatus::getSpeed()
{
    return speed;
}

bool CurrentStatus::setTone(int stone)
{
    tone = stone;
    return true;
}

int CurrentStatus::getTone()
{
    return tone;
}

bool CurrentStatus::setVolume(int svolume)
{
    if ((svolume < 1) || svolume > 127)
        return false;

    volume = svolume;
    return true;
}

int CurrentStatus::getVolume()
{
    return volume;
}

vector<int> CurrentStatus::getChordButton(ChordLevelAndKind lak)
{
    vector<int> buttons;
    if (MAJORTRIAD1 == lak)
    {
        buttons.push_back((0 + key) % 12);
        buttons.push_back((4 + key) % 12);
        buttons.push_back((7 + key) % 12);
    }
    else if (MINORTRIAD2 == lak)
    {
        buttons.push_back((2 + key) % 12);
        buttons.push_back((5 + key) % 12);
        buttons.push_back((9 + key) % 12);
    }
    else if (MINORTRIAD3 == lak)
    {
        buttons.push_back((4 + key) % 12);
        buttons.push_back((7 + key) % 12);
        buttons.push_back((11 + key) % 12);
    }
    else if (MAJORTRIAD4 == lak)
    {
        buttons.push_back((0 + key) % 12);
        buttons.push_back((5 + key) % 12);
        buttons.push_back((9 + key) % 12);
    }
    else if (MAJORTRIAD5 == lak)
    {
        buttons.push_back((2 + key) % 12);
        buttons.push_back((7 + key) % 12);
        buttons.push_back((11 + key) % 12);
    }
    else if (MINORTRIAD6 == lak)
    {
        buttons.push_back((0 + key) % 12);
        buttons.push_back((4 + key) % 12);
        buttons.push_back((9 + key) % 12);
    }
    else if (MINORSEVENTHS2 == lak)
    {
        buttons.push_back((0 + key) % 12);
        buttons.push_back((2 + key) % 12);
        buttons.push_back((5 + key) % 12);
        buttons.push_back((9 + key) % 12);
    }
    else if (MINORSEVENTHS3 == lak)
    {
        buttons.push_back((2 + key) % 12);
        buttons.push_back((4 + key) % 12);
        buttons.push_back((7 + key) % 12);
        buttons.push_back((11 + key) % 12);
    }
    else if (ADDSEVENTHS4 == lak)
    {
        buttons.push_back((0 + key) % 12);
        buttons.push_back((4 + key) % 12);
        buttons.push_back((5 + key) % 12);
        buttons.push_back((9 + key) % 12);
    }
    else if (MAJORSEVENTHS5 == lak)
    {
        buttons.push_back((2 + key) % 12);
        buttons.push_back((5 + key) % 12);
        buttons.push_back((7 + key) % 12);
        buttons.push_back((11 + key) % 12);
    }
    else
    {
    }

    return buttons;
}
