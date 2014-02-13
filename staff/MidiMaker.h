// MidiMaker.h: interface for the CMidiMaker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIDIMAKER_H__6BAD9F0F_AEBF_4B59_8C09_17121749EE6E__INCLUDED_)
#define AFX_MIDIMAKER_H__6BAD9F0F_AEBF_4B59_8C09_17121749EE6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "music_element.h"
#include "staff.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <list>
#include "minHeap.h"
using namespace std;
struct BarInfo
{
	int key;
	Meter meter;
	int speed;
	int startNotesPosition;
};

struct NEventInfo
{
	int timeCha;
	int pitch;
	int volume;
};
class CMidiMaker  
{
public:
	CMidiMaker();

	bool makeMidi(Staff & staff, const string & fileName);

	Staff * makeStaff(const string & fileName);
	void test();
	void saveThenPlay(Staff * staff);
	virtual ~CMidiMaker();

private:
	ofstream m_ofile;
	bool writeHead(ofstream &os);
	bool writeOverallStageTrack(Staff & staff, ofstream & os);

	bool writeNotesTrack(vector<Bar> &bars, ofstream &os);
	bool modifySpeed(ofstream &os, int speed);
	bool modifyMeter(ofstream &os, Meter meter);
	bool modifyKey(ofstream &os, int key);
	int _writeEventTime(ofstream &os, int time);
	int _getBarDuration(Meter meter);
	char _convertPitch(int pitch); 
	char _convertVolume(int volume);
	void _writeTrackDataSum(ofstream & os, int dataSum);

	int _readTime(ifstream &is);
        unsigned char _readEventType(ifstream &is);
	int _getBarInfo(ifstream &is, BarInfo & bif);
/*	int _getDuration()*/
	char * m_pKeyMap;
};

#endif // !defined(AFX_MIDIMAKER_H__6BAD9F0F_AEBF_4B59_8C09_17121749EE6E__INCLUDED_)
