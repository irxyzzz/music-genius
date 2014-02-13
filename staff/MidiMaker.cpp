// MidiMaker.cpp: implementation of the CMidiMaker class.
//
//////////////////////////////////////////////////////////////////////

#include "MidiMaker.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CMidiMaker::CMidiMaker()
{

}

bool CMidiMaker::makeMidi(Staff & staff, const string & fileName)
{
	m_ofile.open(fileName.c_str(),ios::trunc|ios::binary);
	if (!m_ofile.is_open())
	{
		cout << "fileopen1 wrong" << endl;
		return false;
	}

	ofstream &os = m_ofile;
	if(!writeHead(os))
	{
		cout << "writehead wrong" << endl; 
		return false;
	}

	if(!writeOverallStageTrack(staff, os))
	{
		cout << "writeStageTrack wrong" << endl; 
		return false;
	}
	
	if(!writeNotesTrack(staff.bars, os))
	{
		cout << "writeNotesTrack wrong" << endl; 
		return false;
	}

	return true;
}


bool CMidiMaker::writeHead(ofstream &os)
{
	if (!os.is_open())
	{
		cout << "fileWrong";
		return false;
	}
	os << "MThd";
	os << (char)0 << (char)0<< (char)0<< (char)6;
	os << (char)0 << (char)1 << (char)0 << (char)2 << (char)0 << (char)0x78;
	return true;
}

bool CMidiMaker::writeOverallStageTrack(Staff & staff, ofstream & os)
{
	if (!os.is_open())
	{
		return false;
	}
	os << "MTrk";
	char titleSize = staff.title.size();
	os << (char)0 << (char)0 << (char)0 << (char)(titleSize + 8);
	os << (char)0 << (char)0xFF << (char)0x03 << titleSize << staff.title.c_str();
	os << (char)0x00 << (char)0xFF << (char)0x2F << (char)0x00;
	return true;
}

bool CMidiMaker::writeNotesTrack(vector<Bar> &bars, ofstream &os)
{
	if (!os.is_open())
	{
		return false;
	}
	os << "MTrk" << (char)0x00 << (char)0x00 << (char)0x00 << (char)0xaa;

	//data
	os << (char)0x00 << (char)0x96 << (char)0x45 << (char)0x00;
	char keyMap[12] = {0,-5,2,-3,4,-1,6,1,-4,3,-2,5};
	m_pKeyMap = keyMap;
	int beforeTime = 0;
	int beforeBarTime = 0;
	int dataSum = 4;//前面加了4个打开通道的字节
	minHeap mHeap(32);
	for (vector<Bar>::iterator iter2 = bars.begin(); iter2 != bars.end(); ++iter2)
	{
		dataSum += 21;
		dataSum += iter2->notes.size() * 6;
		mHeap.minusAll(beforeBarTime);
		beforeTime -= beforeBarTime;
		modifyKey(os, iter2->key);
		modifyMeter(os, iter2->meter);
		modifySpeed(os, iter2->speed);
		
		int noteCount = 0;
		list<Note>::iterator notesIter = iter2->notes.begin();
		while(true)
		{
			if (false)
			{
			}
// 			if (notesIter == iter2->notes.end())
// 			{
// 				break;
// 			}
			else if (notesIter != iter2->notes.end() && (0 == mHeap.size() || (0 != mHeap.size() && notesIter->position < mHeap.getMin().time)))
			{
				++noteCount;
				dataSum += _writeEventTime(os, notesIter->position - beforeTime) - 1;
				os << _convertPitch(notesIter->pitch) << _convertVolume(notesIter->volume);
				beforeTime = notesIter->position;
				NotePair nPair;
				nPair.note = &(*notesIter);
				nPair.time = notesIter->position + notesIter->duration;
				mHeap.push(nPair);
				++notesIter;
			}
			else if (0 != mHeap.size() && (notesIter == iter2->notes.end() || notesIter->position >= mHeap.getMin().time))
			{
				NotePair nPair = mHeap.getMin();
				dataSum += _writeEventTime(os, nPair.time - beforeTime) - 1;
				os << _convertPitch(nPair.note->pitch) << (char)0x00;
				beforeTime = nPair.time;
				mHeap.popMin();
			}
			else
			{
				break;
			}
		}
		beforeBarTime = _getBarDuration(iter2->meter);
	}

	os << (char)0x00 << (char)0xff << (char)0x2f << (char)0x00;
	dataSum += 4;
	while(0 != mHeap.size())
	{
		
	}

	cout << dataSum;
	os.seekp(-dataSum - 4, ios::cur);
	_writeTrackDataSum(os, dataSum);
	cout << dataSum ;
	m_pKeyMap = 0;
        os.close();
	return true;
}

bool CMidiMaker::modifyKey(ofstream &os, int key)
{
	if (!os.is_open())
	{
		return false;
	}
	os << (char)0x00 << (char)0xFF << (char)0x59 << (char)0x02 << m_pKeyMap[key] << (char)0x00;
	return true;
}

bool CMidiMaker::modifyMeter(ofstream &os, Meter meter)
{	
	char fenzi,fenmu;
	switch (meter)
	{
	case EIGHT6:
		{
			fenzi = 6;
			fenmu = 3;
			break;
		}
	case FOUR2:
		{
			fenzi = 2;
			fenmu = 2;
			break;
		}
	case FOUR3:
		{
			fenzi = 3;
			fenmu = 2;
			break;
		}
	case FOUR4:
		{
			fenzi = 4;
			fenmu = 2;
			break;
		}		
	}
	os << (char)0x00 << (char)0xFF << (char)0x58 << (char)0x04 << fenzi << fenmu << (char)0x00 << (char)0x00;
	return true;
}

bool CMidiMaker::modifySpeed(ofstream &os, int speed)
{
	if (!os.is_open())
	{
		return false;
	}
	os << (char)0x00 << (char)0xFF << (char)0x51 << (char)0x03;
	
	speed = ((float)60 / (float)speed) * (float)(1000000);
	char * tSize = (char *)&speed;
	
	int i = 0;
	bool findFirst = false;
	for (i = 1; i < 4; i++)
	{
		if (false == findFirst && 0 != tSize[3 - i])
		{
			findFirst = true;
		}
		if (true == findFirst)
		{
			os << tSize[3- i];
		}
		else
			os << (char)0;
	}
	return true;
}

int CMidiMaker::_writeEventTime(ofstream &os, int time)
{
	time *= 5;
	if (time <= 480 && time >= 0)
	{
		if (time < 128)
		{
			os << (char)time;
			return 1;
		}
		else
		{
			os << (char)(time/128 + 0x80) << (char)(time - ((time/128)*128));
			return 2;
		}
	}
	else
	{
		os << (char)0x00;
		return 1;
	}
}
char CMidiMaker::_convertPitch(int pitch)
{
	return (char)(pitch + 12);
}
 
char CMidiMaker::_convertVolume(int volume)
{
	return (char)volume;
}

int CMidiMaker::_getBarDuration(Meter meter)
{
	switch (meter)
	{
	case EIGHT6:
		{
		}
	
	case FOUR3:
		{
			return 72;
		}
	case FOUR4:
		{
			return 96;
		}	
	case FOUR2:
		{
			return 48;
		}
	} 
	return -1;
}
void CMidiMaker::_writeTrackDataSum(ofstream & os, int trackSize)
{
	char * tSize = (char *)&trackSize;
	
	int i = 0;
	bool findFirst = false;
	for (i = 0; i < 4; i++)
	{
		if (false == findFirst && 0 != tSize[3 - i])
		{
			findFirst = true;
		}
		if (true == findFirst)
		{
			os << tSize[3- i];
		}
		else
			os << (char)0;
	}
}

Staff * CMidiMaker::makeStaff(const string & fileName)
{
        Staff * tStaff = new Staff();
        ifstream is(fileName.c_str(), ios::binary | ios::in);
        if (!is)
        {
                cout << "The midi file doesn't exist!" << endl;
                return 0;
        }

        char buf[257];
        is.read(buf, 4);
        buf[4] = 0;
        string tStr = "MThd";
        if (buf != tStr)
        {
                return 0;
        }

        is.seekg(21, ios::cur);
        is >> buf[0];
        is.read(&buf[1], buf[0]);
        buf[buf[0] + 1] = 0;
        tStaff->title = &buf[1];

        is.seekg(8, ios::cur);
        int notesDataSum = 0;
        int temp = 0;
        is.read(buf, 4);
        unsigned char a = buf[0];
        temp = a;
        notesDataSum += (temp << 24);
        a = buf[1];
        temp = a;
        notesDataSum += (temp << 16);
        a = buf[2];
        temp = a;
        notesDataSum += (temp << 8);
        a = buf[3];
        temp = a;
        notesDataSum += temp;

        is.seekg(4, ios::cur);
        //good here

        vector<BarInfo> bInfos;
        int byteCount = 4;
        int noteCount = 0;
        NEventInfo tNIF;
        BarInfo tBIF;
        int tTime;
        int tEventType;
        char tData;
        char keyMap[12] = {1,8,3,10,5,0,7,2,9,4,11,6};
        m_pKeyMap = keyMap;
        vector<NEventInfo> nEvents;
        while (byteCount < notesDataSum - 4)
        {
                tTime = _readTime(is);
                if (tTime * 5 >= 128)
                {
                        byteCount += 1;
                }
                //tTime
                tEventType = _readEventType(is);
                if (0xFF != tEventType)
                {
                        tNIF.timeCha = tTime;
// 			is.read(&tData, 1);
// 			tNIF.pitch = tData - 12;
                        tNIF.pitch = tEventType - 12;
                        is.read(&tData, 1);
                        tNIF.volume = tData;
                        nEvents.push_back(tNIF);
                        cout << "pitch : " << tNIF.pitch << "   volume : " << tNIF.volume << endl;
                        byteCount += 3;
                        ++noteCount;

                }
                else if (0xFF == tEventType)
                {

                        _getBarInfo(is, tBIF);
                        byteCount += 21;

                        tBIF.startNotesPosition = noteCount + 1;
                        cout << bInfos.size() << ":" << noteCount + 1;
                        bInfos.push_back(tBIF);

                }

        //	tNIF.timeCha = tTime;

        }
        int xx;
        cout << endl << nEvents.size() << endl;
        for (xx = 0 ; xx < bInfos.size(); xx++)
        {
                cout << endl <<  xx  << ":"<<  bInfos[xx].key << "  " << (int)bInfos[xx].meter << "  " << bInfos[xx].speed << "  " << bInfos[xx].startNotesPosition;
        }
        m_pKeyMap = 0;

        int i,j;
        int timeCount = 0;
        for (i = 0; i < bInfos.size(); i++)
        {
                CurrentStatus::Instance()->setKey(bInfos[i].key);
                CurrentStatus::Instance()->setMeter(bInfos[i].meter);
                CurrentStatus::Instance()->setSpeed(bInfos[i].speed);
                CurrentStatus::Instance()->setTone(0);

                int barPosition = 0;
                for (j = bInfos[i].startNotesPosition - 1; ; j++)
                {
                        NEventInfo & tEI = nEvents[j];
                        barPosition += nEvents[j].timeCha;
                        if (0 != tEI.volume)
                        {
                                Note tNote;
                                tNote.pitch = tEI.pitch;
                                tNote.volume = tEI.volume;
                                tNote.tone = 0;
                                tNote.position = barPosition;
                                int m = j +1;
                                int duration = 0;
                                while(m < nEvents.size())
                                {
                                        duration += nEvents[m].timeCha;
                                        if (nEvents[m].pitch == nEvents[j].pitch && 0 == nEvents[m].volume)
                                        {

                                                tNote.duration = duration;

                                                CurrentStatus::Instance()->setVolume(tNote.volume);
                                                tStaff->addNote(tNote.pitch, tNote.duration, tNote.position, i);
                                                //static founCount = 0;
                                                //cout << "foundCount" << ++ founCount  << "  "<< nEvents.size()<<  endl;
                                                break;
                                        }
                                        ++m;
                                }

                        }
                        else
                        {
                                if (i == bInfos.size() - 1 && j >= nEvents.size() - 1 || i != bInfos.size() - 1 && j >= bInfos[i + 1].startNotesPosition - 2)
                                {
                                        cout  <<  "j "<< j << endl;
                                        break;
                                }
                                continue;
                        }
                        if (i == bInfos.size() - 1 && j >= nEvents.size() - 1 || i != bInfos.size() - 1 && j >= bInfos[i + 1].startNotesPosition - 2)
                        {
                                cout  <<  "j "<< j << endl;
                                break;
                        }
                }
        }

        return tStaff;
}


int CMidiMaker::_readTime(ifstream &is)
{
	int result = 0;
	unsigned char tData[2];
	is.read((char *)&tData[0],1);
	if (tData[0] >= 128)
	{
		is.read((char *)&tData[1],1);
		result = tData[0] - 0x80;
		result *= 128;
		result += tData[1];
	}
	else
	{
		result = tData[0];
	}
	return result/5;
}

unsigned char CMidiMaker::_readEventType(ifstream &is)
{
	unsigned char tData;
	is.read((char *)&tData, 1);
	return tData;
// 	if (0xFF != tData)
// 	{
// 		return 1;
// 	}
// 	else
// 	{
// 		return 2;
// 	}
}

int CMidiMaker::_getBarInfo(ifstream &is, BarInfo & bif)
{
	char tData;
	char ttData;
	is.seekg(2, ios::cur);
//	is >> ttData;
	is.read(&ttData, 1);
	bif.key = m_pKeyMap[ttData + 5];

	is.seekg(5, ios::cur);
	is.read(&tData, 1);
	switch(tData)
	{
	case 0x02:
		{
			bif.meter = FOUR2;
			break;
		}
	case 0x03:
		{
			bif.meter = FOUR3;
			break;
		}
	case 0x04:
		{
			bif.meter = FOUR4;
			break;
		}
	case 0x06:
		{
			bif.meter = EIGHT6;
			break;
		}
	}

	is.seekg(7, ios::cur);
	char tData2, tData3;
	is.read(&ttData, 1);
	//is >> tData; 
	//is >> tData2; is >> tData3;
	is.read(&tData2, 1); 
	is.read(&tData3, 1);
	int bifSpeed = ttData;
	bifSpeed <<= 8;
	bifSpeed += tData2;
	bifSpeed <<= 8;
	bifSpeed += tData3;
	bif.speed = 60000000/bifSpeed;
int a;
	return 1;

}


CMidiMaker::~CMidiMaker()
{

}


void CMidiMaker::saveThenPlay(Staff * staff)
{
	this->makeMidi(*staff, string("ourMid.mid"));
}

void CMidiMaker::test()
{
	ofstream os("testFile.mid", ios::trunc | ios::binary);

	if (os.is_open() == false)
	{
		cout << "file nnn";
	}

	//writeHead test
	writeHead(os);

	//writeOverallStageTrack test
	Staff tStaff;
	tStaff.title = "cao ni ma操操操gan ni mei afjldsajflsdjfjaoejioajrosfkljasdfsadl;fhsad;klhgsdfs";
	writeOverallStageTrack(tStaff, os);

	//modifyKey test
	char keyMap[12] = {0,-5,2,-3,4,-1,6,1,-4,3,-2,5};
	m_pKeyMap = keyMap;
	modifyKey(os, 0);
	modifyKey(os, 1);
	modifyKey(os, 2);
	modifyKey(os, 3);
	modifyKey(os, 4);
	modifyKey(os, 5);
	modifyKey(os, 6);
	modifyKey(os, 7);
	modifyKey(os, 8);
	modifyKey(os, 9);
	modifyKey(os, 10);
	modifyKey(os, 11);
	os << "testKeyFinish";

	//modifyMeter test
	modifyMeter(os, FOUR2);
	modifyMeter(os, FOUR3);
	modifyMeter(os, FOUR4);
	modifyMeter(os, EIGHT6);
	os << "testMeterFinish";

	//modifySpeed test
	modifySpeed(os, 120);
	os << "testSpeedFinish";

	//writeEventTime test
	_writeEventTime(os, 24);
	_writeEventTime(os, 48);
	_writeEventTime(os, 96);
	os << "writeEventTimeFinish";

	//convertPitch test
	os << _convertPitch(129);
	os << "convertPitch";

	//convertVolume test
	os << _convertVolume(126);
	os << "convertVolumeFinish";

	//getBarDuration test
	if (48 == _getBarDuration(FOUR2))
	{
		cout << "pass getBarDuration 42 " << endl;
	}
	if (72 == _getBarDuration(FOUR3))
	{
		cout << "pass getBarDuration 43" << endl;
	}
	if (96 == _getBarDuration(FOUR4))
	{
		cout << "pass getBarDuration 44" << endl;
	}
	if (72 == _getBarDuration(EIGHT6))
	{
		cout << "pass getBarDuration 86" << endl;
	}
	
	//writeTrackDataSum test
	_writeTrackDataSum(os, 0x00);
	_writeTrackDataSum(os, 0x127);
	_writeTrackDataSum(os, 0x2415);
	_writeTrackDataSum(os, 0x56782);
	_writeTrackDataSum(os, 0x567834);
	os << "writeTrackDataSumFinish";
}
