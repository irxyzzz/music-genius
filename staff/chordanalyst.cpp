#include "chordanalyst.h"
#include <QtDebug>

const char *ChordAnalyst::alphabet[] = {"C", "bD", "D", "bE", "E", "F", "bG", "G", "bA", "A", "bB", "B"};

using namespace std;

ChordAnalyst::ChordAnalyst()
{
    ChordPower temp;
    int i = 0;

    //和弦权值初始化

    //一级大三和弦
    temp.kind = MAJORTRIAD;
    temp.level = 0;
    for (i =0; i < 12; ++i)
        temp.powers[i] = 0;
    temp.powers[0] = 1;
    temp.powers[4] = 1;
    temp.powers[7] = 1;
    chord_powers.push_back(temp);

    //五级大三和弦
    temp.kind = MAJORTRIAD;
    temp.level = 7;
    for (i =0; i < 12; ++i)
        temp.powers[i] = 0;
    temp.powers[2] = 1;
    temp.powers[7] = 1;
    temp.powers[11] = 1;
    chord_powers.push_back(temp);

    //四级大三和弦
    temp.kind = MAJORTRIAD;
    temp.level = 5;
    for (i =0; i < 12; ++i)
        temp.powers[i] = 0;
    temp.powers[0] = 1;
    temp.powers[5] = 1;
    temp.powers[9] = 1;
    chord_powers.push_back(temp);

    //六级小三和弦
    temp.kind = MINORTRIAD;
    temp.level = 9;
    for (i =0; i < 12; ++i)
        temp.powers[i] = 0;
    temp.powers[0] = 1;
    temp.powers[4] = 1;
    temp.powers[9] = 1;
    chord_powers.push_back(temp);

    //三级小三和弦
    temp.kind = MINORTRIAD;
    temp.level = 4;
    for (i =0; i < 12; ++i)
        temp.powers[i] = 0;
    temp.powers[4] = 1;
    temp.powers[7] = 1;
    temp.powers[11] = 1;
    chord_powers.push_back(temp);

    //二级小三和弦
    temp.kind = MINORTRIAD;
    temp.level = 2;
    for (i =0; i < 12; ++i)
        temp.powers[i] = 0;
    temp.powers[2] = 1;
    temp.powers[5] = 1;
    temp.powers[9] = 1;
    chord_powers.push_back(temp);

    //五级大小七和弦
    temp.kind = MAJORSEVENTHS;
    temp.level = 7;
    for (i =0; i < 12; ++i)
        temp.powers[i] = 0;
    temp.powers[2] = 1;
    temp.powers[5] = 1;
    temp.powers[7] = 1;
    temp.powers[11] = 1;
    chord_powers.push_back(temp);

    //四级增七和弦
    temp.kind = ADDSEVENTHS;
    temp.level = 5;
    for (i =0; i < 12; ++i)
        temp.powers[i] = 0;
    temp.powers[0] = 1;
    temp.powers[4] = 1;
    temp.powers[5] = 1;
    temp.powers[9] = 1;
    chord_powers.push_back(temp);

    //三级小小七和弦
    temp.kind = MINORSEVENTHS;
    temp.level = 4;
    for (i =0; i < 12; ++i)
        temp.powers[i] = 0;
    temp.powers[2] = 1;
    temp.powers[4] = 1;
    temp.powers[7] = 1;
    temp.powers[11] = 1;
    chord_powers.push_back(temp);

    //二级小小七和弦
    temp.kind = MINORSEVENTHS;
    temp.level = 2;
    for (i =0; i < 12; ++i)
        temp.powers[i] = 0;
    temp.powers[0] = 1;
    temp.powers[2] = 1;
    temp.powers[5] = 1;
    temp.powers[9] = 1;
    chord_powers.push_back(temp);
}

//匹配单个和弦，值-结果参数，powers成员表示该匹配部分每个音符的个数，匹配结束后，将结果添入level和kind成员。
int ChordAnalyst::machingSingleChord(ChordPower& result) const
{
    float sum = 0;
    for (int i = 0; i < 12; ++i)
    {
        sum += result.powers[i];
    }
    if (sum < 3)
    {
        result.kind = NOCHORD;
        return 0;
    }

    float scores[CHORDNUMBER] = {0.0};
    for (int i = 0; i < chord_powers.size(); ++i)
    {
        float vector_distance = 0;
        for (int j = 0; j < 12; ++j)
        {
            vector_distance += chord_powers[i].powers[j] * result.powers[j];
        }

        float a_norm = 0.0;
        float b_norm = 0.0;
        for (int j = 0; j < 12; ++j)
        {
            a_norm += chord_powers[i].powers[j] * chord_powers[i].powers[j];
            b_norm += result.powers[j] * result.powers[j];
        }

        a_norm = sqrt(a_norm);
        b_norm = sqrt(b_norm);
        scores[i] = vector_distance / (a_norm * b_norm);
    }

    int top_score_item = 0;
    for (int i = 0; i < CHORDNUMBER; ++i)
    {
        if (scores[top_score_item] < scores[i])
            top_score_item = i;
    }

    result.kind = chord_powers[top_score_item].kind;
    result.level = chord_powers[top_score_item].level;

    return 0;
}

//匹配整个乐谱的所有和弦
vector<vector<string> > ChordAnalyst::machingStaveChords(Staff& staff) const
{
    vector<vector<string> > chords;
    vector<Bar> bars = staff.getBars();
    for (vector<Bar>::const_iterator iter_bar = bars.begin(); iter_bar != bars.end(); ++iter_bar)
    {
        vector<string> one_bar_chords;
        int bar_key = iter_bar->key;
        ChordPower temp_chord;
        string chord_str;
        int level = 0;
        int temp_pitch = 0;

        qDebug() << "start analyse bar";

        list<Note>::const_iterator iter_note = iter_bar->notes.begin();
        if (iter_bar->meter == FOUR4)
        {

            for (int i = 0; i < 12; ++i)
                temp_chord.powers[i] = 0;
            for (;iter_note != iter_bar->notes.end(); ++iter_note)
            {
                if (iter_note->position >= 48)
                    break;
                temp_pitch = iter_note->pitch;
                temp_pitch = (temp_pitch + 12 - bar_key) % 12;
                temp_chord.powers[temp_pitch] += 1;
            }
            machingSingleChord(temp_chord);
            chord_str = "";
            level = (bar_key + temp_chord.level) % 12;
            if (temp_chord.kind == NOCHORD)
                one_bar_chords.push_back(chord_str);
            else
            {
                chord_str.append(alphabet[level]);
                if (temp_chord.kind == MINORTRIAD)
                    chord_str.append("m");
                else if (temp_chord.kind == MAJORSEVENTHS)
                    chord_str.append("7");
                else if (temp_chord.kind == MINORSEVENTHS)
                    chord_str.append("m7");
                else if (temp_chord.kind == ADDSEVENTHS)
                    chord_str.append("maj7");
                one_bar_chords.push_back(chord_str);
            }

            for (int i = 0; i < 12; ++i)
                temp_chord.powers[i] = 0;
            for (;iter_note != iter_bar->notes.end(); ++iter_note)
            {
                temp_pitch = iter_note->pitch;
                temp_pitch = (temp_pitch + 12 - bar_key) % 12;
                temp_chord.powers[temp_pitch] += 1;
            }
            machingSingleChord(temp_chord);
            chord_str = "";
            level = (bar_key + temp_chord.level) % 12;
            if (temp_chord.kind == NOCHORD)
                one_bar_chords.push_back(chord_str);
            else
            {
                chord_str.append(alphabet[level]);
                if (temp_chord.kind == MINORTRIAD)
                    chord_str.append("m");
                else if (temp_chord.kind == MAJORSEVENTHS)
                    chord_str.append("7");
                else if (temp_chord.kind == MINORSEVENTHS)
                    chord_str.append("m7");
                else if (temp_chord.kind == ADDSEVENTHS)
                    chord_str.append("maj7");
                one_bar_chords.push_back(chord_str);
            }
        }
        else if (iter_bar->meter == EIGHT6)
        {
            for (int i = 0; i < 12; ++i)
                temp_chord.powers[i] = 0;
            for (;iter_note != iter_bar->notes.end(); ++iter_note)
            {
                if (iter_note->position >= 36)
                    break;
                temp_pitch = iter_note->pitch;
                temp_pitch = (temp_pitch + 12 - bar_key) % 12;
                temp_chord.powers[temp_pitch] += 1;
            }
            machingSingleChord(temp_chord);
            chord_str = "";
            level = (bar_key + temp_chord.level) % 12;
            if (temp_chord.kind == NOCHORD)
                one_bar_chords.push_back(chord_str);
            else
            {
                chord_str.append(alphabet[level]);
                if (temp_chord.kind == MINORTRIAD)
                    chord_str.append("m");
                else if (temp_chord.kind == MAJORSEVENTHS)
                    chord_str.append("7");
                else if (temp_chord.kind == MINORSEVENTHS)
                    chord_str.append("m7");
                else if (temp_chord.kind == ADDSEVENTHS)
                    chord_str.append("maj7");
                one_bar_chords.push_back(chord_str);
            }

            for (int i = 0; i < 12; ++i)
                temp_chord.powers[i] = 0;
            for (;iter_note != iter_bar->notes.end(); ++iter_note)
            {
                temp_pitch = iter_note->pitch;
                temp_pitch = (temp_pitch + 12 - bar_key) % 12;
                temp_chord.powers[temp_pitch] += 1;
            }
            machingSingleChord(temp_chord);
            chord_str = "";
            level = (bar_key + temp_chord.level) % 12;
            if (temp_chord.kind == NOCHORD)
                one_bar_chords.push_back(chord_str);
            else
            {
                chord_str.append(alphabet[level]);
                if (temp_chord.kind == MINORTRIAD)
                    chord_str.append("m");
                else if (temp_chord.kind == MAJORSEVENTHS)
                    chord_str.append("7");
                else if (temp_chord.kind == MINORSEVENTHS)
                    chord_str.append("m7");
                else if (temp_chord.kind == ADDSEVENTHS)
                    chord_str.append("maj7");
                one_bar_chords.push_back(chord_str);
            }
        }
        else
        {
            for (int i = 0; i < 12; ++i)
                temp_chord.powers[i] = 0;
            for (;iter_note != iter_bar->notes.end(); ++iter_note)
            {
                temp_pitch = iter_note->pitch;
                temp_pitch = (temp_pitch + 12 - bar_key) % 12;
                temp_chord.powers[temp_pitch] += 1;
            }
            machingSingleChord(temp_chord);
            chord_str = "";
            level = (bar_key + temp_chord.level) % 12;
            if (temp_chord.kind == NOCHORD)
                one_bar_chords.push_back(chord_str);
            else
            {
                chord_str.append(alphabet[level]);
                if (temp_chord.kind == MINORTRIAD)
                    chord_str.append("m");
                else if (temp_chord.kind == MAJORSEVENTHS)
                    chord_str.append("7");
                else if (temp_chord.kind == MINORSEVENTHS)
                    chord_str.append("m7");
                else if (temp_chord.kind == ADDSEVENTHS)
                    chord_str.append("maj7");
                one_bar_chords.push_back(chord_str);
            }
        }

        chords.push_back(one_bar_chords);
    }

    return chords;
}
