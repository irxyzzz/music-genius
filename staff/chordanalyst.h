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

    //匹配单个和弦，值-结果参数，powers成员表示该匹配部分每个音符的个数，匹配结束后，将结果添入level和kind成员。
    int machingSingleChord(ChordPower& result) const;

public:
    //匹配整个乐谱的所有和弦
    std::vector<std::vector<std::string> > machingStaveChords(Staff & staff) const;
};

#endif // CHORDANALYST_H
