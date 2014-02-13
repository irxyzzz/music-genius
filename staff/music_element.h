#ifndef MUSIC_ELEMENT_H
#define MUSIC_ELEMENT_H

#include <vector>
#include <list>
#include <string>

enum Meter {FOUR2, FOUR3, FOUR4, EIGHT6};

/**
 * �����ṹ
 * pitch ����
 * duration ʱֵ 32��������3��ʾ
 * position ����С�ڿ�ʼ��λ��
 * tone ��ɫ
 * volume ����
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
 * С�ڽṹ
 * key ��ʽ��C���Ϊ0�� B���Ϊ11��
 * meter ����
 * speed �ٶȣ�һ���Ӷ��ٸ��ķ�����
 * notes ����������
 */
struct Bar
{
    int key;
    Meter meter;
    int speed;
    std::list<Note> notes;
};

#endif // MUSIC_ELEMENT_H
