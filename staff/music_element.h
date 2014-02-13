#ifndef MUSIC_ELEMENT_H
#define MUSIC_ELEMENT_H

#include <vector>
#include <list>
#include <string>

enum Meter {FOUR2, FOUR3, FOUR4, EIGHT6};

/**
 * 音符结构
 * pitch 音高
 * duration 时值 32分音符用3表示
 * position 距离小节开始的位置
 * tone 音色
 * volume 力度
 */
struct Note
{
    int pitch;
    int duration;
    int position;
    int tone;
    int volume;
};

/**
 * 小节结构
 * key 调式，C大调为0， B大调为11。
 * meter 节奏
 * speed 速度，一分钟多少个四分音符
 * notes 音符的链表
 */
struct Bar
{
    int key;
    Meter meter;
    int speed;
    std::list<Note> notes;
};

#endif // MUSIC_ELEMENT_H
