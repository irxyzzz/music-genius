#include "staff.h"

using namespace std;

int Staff::addNote(int pitch, int duration, int position, int barNo)
{
    //如果还没有该小节，则先插入小节。
    while (bars.size() <= barNo)
    {
        Bar tempbar;
        tempbar.key = CurrentStatus::Instance()->getKey();
        tempbar.meter = CurrentStatus::Instance()->getMeter();
        tempbar.speed = CurrentStatus::Instance()->getSpeed();

        bars.push_back(tempbar);
    }

    //找位置，按照position从小到大顺序插入，如果该小节无音符，则插入到最后。
    list<Note>::iterator iter = bars[barNo].notes.begin();
    for (; iter != bars[barNo].notes.end(); ++iter)
    {
        if (iter->position > position)
        {
            break;
        }
    }

    //插入音符
    Note tempnote;
    tempnote.duration = duration;
    tempnote.pitch = pitch;
    tempnote.position = position;
    tempnote.tone = CurrentStatus::Instance()->getTone();
    tempnote.volume = CurrentStatus::Instance()->getVolume();
    bars[barNo].notes.insert(iter, tempnote);

    return 0;
}

int Staff::deleteNote(int noteNo, int barNo)
{
    if (barNo < 0)
        return -1;
    if (noteNo < 0)
        return -2;
    if (bars.size() < barNo)
        return -3;

    if (bars[barNo].notes.size() <= noteNo)
    {
        return -4;
    }

    //找要删除的音符的位置
    list<Note>::iterator iter = bars[barNo].notes.begin();
    for (int i = 0; iter != bars[barNo].notes.end(); ++iter, ++i)
    {
        if (i >= noteNo)
            break;
    }

    if (iter != bars[barNo].notes.end())
    {
        bars[barNo].notes.erase(iter);
    }
    else
    {
        return -5;
    }

    //把空的小节从后往前删除
    while (bars.back().notes.empty())
    {
        bars.pop_back();
    }

    return 0;
}

std::vector<Bar> Staff::getBars()
{
    return bars;
}

int Staff::save(const char *filename)
{
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        return -1;
    }
    QXmlStreamWriter writer;
    writer.setDevice(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("staff");
    writer.writeAttribute("title", title.c_str());

    vector<Bar>::const_iterator iter_bar = bars.begin();
    for (;iter_bar != bars.end();++ iter_bar)
    {
        //写入小节信息
        writer.writeStartElement("bar");
        writer.writeAttribute("key", itos(iter_bar->key).c_str());
        Meter tmp_meter = iter_bar->meter;
        if (tmp_meter == FOUR2)
            writer.writeAttribute("meter", "FOUR2");
        else if (tmp_meter == FOUR3)
            writer.writeAttribute("meter", "FOUR3");
        else if (tmp_meter == FOUR4)
            writer.writeAttribute("meter", "FOUR4");
        else if (tmp_meter == EIGHT6)
            writer.writeAttribute("meter", "EIGHT6");
        else
            writer.writeAttribute("meter", "FOUR4");
        writer.writeAttribute("speed", itos(iter_bar->speed).c_str());

        //写入音符信息
        list<Note>::const_iterator iter_note = iter_bar->notes.begin();
        for (;iter_note != iter_bar->notes.end(); ++iter_note)
        {
            writer.writeStartElement("note");
            writer.writeAttribute("pitch", itos(iter_note->pitch).c_str());
            writer.writeAttribute("duration", itos(iter_note->duration).c_str());
            writer.writeAttribute("position", itos(iter_note->position).c_str());
            writer.writeAttribute("tone", itos(iter_note->tone).c_str());
            writer.writeAttribute("volume", itos(iter_note->volume).c_str());
            writer.writeEndElement();
        }

        //</bar>
        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
    return 0;
}

int Staff::load(const char *filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return -1;
    }

    QXmlStreamReader reader;
    reader.setDevice(&file);

    reader.readNextStartElement();
    if (reader.name() == "staff")
    {
        //读取标题
        QXmlStreamAttributes attrib = reader.attributes();
        this->title = attrib.value("title").toString().toStdString();

        int count_of_bar = -1;
        reader.readNextStartElement();
        while (!reader.atEnd())
        {
            if (reader.name() == "bar")
            {
                attrib = reader.attributes();
                if (!attrib.empty())
                {
                    count_of_bar++;

                    CurrentStatus::Instance()->setKey(attrib.value("key").toString().toInt());
                    QString tmp_meter = attrib.value("meter").toString();
                    if (tmp_meter == "FOUR2")
                    {
                        CurrentStatus::Instance()->setMeter(FOUR2);
                    }
                    else if (tmp_meter == "FOUR3")
                    {
                        CurrentStatus::Instance()->setMeter(FOUR3);
                    }
                    else if (tmp_meter == "FOUR4")
                    {
                        CurrentStatus::Instance()->setMeter(FOUR4);
                    }
                    else if (tmp_meter == "EIGHT6")
                    {
                        CurrentStatus::Instance()->setMeter(EIGHT6);
                    }
                    else
                    {
                        CurrentStatus::Instance()->setMeter(FOUR4);
                    }
                    CurrentStatus::Instance()->setSpeed(attrib.value("speed").toString().toInt());
                }
            }
            else if (reader.name() == "note")
            {
                attrib = reader.attributes();
                if(!attrib.empty())
                {
                    CurrentStatus::Instance()->setTone(attrib.value("tone").toString().toInt());
                    CurrentStatus::Instance()->setVolume(attrib.value("volume").toString().toInt());

                    this->addNote(attrib.value("pitch").toString().toInt(),
                                  attrib.value("duration").toString().toInt(),
                                  attrib.value("position").toString().toInt(),
                                  count_of_bar);
                }
            }
            else
            {
                //什么都不是，直接跳过
            }

            reader.readNextStartElement();
        }
    }
    else
    {
        return -2;
    }

    return 0;
}

string Staff::itos(int i)
{
    static char buf[20] = {'\0'};
    snprintf(buf, 20, "%d", i);
    string tmp(buf);
    return tmp;
}
