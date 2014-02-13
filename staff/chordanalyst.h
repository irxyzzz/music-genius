#ifndef CHORDANALYST_H
#define CHORDANALYST_H

#include "music_element.h"
#include "staff.h"

#include <vector>
#include <string>
#include <cmath>

#define CHORDNUMBER 10

enum ChordKind {MAJORTRIAD, MINORTRIAD, MAJORSEVENTHS, MINORSEVENTHS, ADDSEVENTHS, NOCHORD};

struct ChordPower
{
    int level;
    ChordKind kind;
    float powers[12];
};

class ChordAnalyst
{
public:
    ChordAnalyst();
private:
    const static char *alphabet[];
    int stat[12];
    std::vector<ChordPower> chord_powers;

    //ƥ�䵥�����ң�ֵ-���������powers��Ա��ʾ��ƥ�䲿��ÿ�������ĸ�����ƥ������󣬽��������level��kind��Ա��
    int machingSingleChord(ChordPower& result) const;

public:
    //ƥ���������׵����к���
    std::vector<std::vector<std::string> > machingStaveChords(Staff & staff) const;
};

#endif // CHORDANALYST_H
