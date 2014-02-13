// minHeap.h: interface for the minHeap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MINHEAP_H__7879B513_07C2_4EE0_96EF_0E90872C8B19__INCLUDED_)
#define AFX_MINHEAP_H__7879B513_07C2_4EE0_96EF_0E90872C8B19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <algorithm>
#include "music_element.h"
using namespace std;
struct NotePair
{
	Note * note;
	int time;
};



class minHeap  
{
public:
	minHeap(int volume = 32);
	int size();
	NotePair & getMin();
	void popMin();
	void push(NotePair & note);
	void push(Note * note, int time);
	void minusAll(int value);
	~minHeap();
private:
	bool m_bIsOrder;
	int m_nSize;
	NotePair * m_pArray;
	int m_nVolume;
	

};

#endif // !defined(AFX_MINHEAP_H__7879B513_07C2_4EE0_96EF_0E90872C8B19__INCLUDED_)
