#ifndef STAFF_H
#define STAFF_H

#include <cstdio>
#include <cstring>
#include <vector>
#include <list>
#include <string>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include "music_element.h"
#include "currentstatus.h"

class Staff
{
public:
    std::string title;

    int addNote(int pitch, int duration, int position, int barNo);
    int deleteNote(int position, int barNo);
    std::vector<Bar> getBars();

    int save(const char *filename);
    int load(const char *filename);

    std::vector<Bar> bars;
private:
    std::string itos(int i);
};

#endif // STAFF_H
