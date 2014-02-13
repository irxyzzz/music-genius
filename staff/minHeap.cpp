// minHeap.cpp: implementation of the minHeap class.
//
//////////////////////////////////////////////////////////////////////

#include "minHeap.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
bool _cmp(NotePair a, NotePair b)
{
	return a.time < b.time;
}
minHeap::minHeap(int volume)
{
	m_pArray = new NotePair[volume];
	m_nSize = 0;
	m_bIsOrder = true;
	m_nVolume = volume;
}


int minHeap::size()
{
	return m_nSize;
}

NotePair & minHeap::getMin()
{
	NotePair *tN = 0;
	if (0 == m_nSize)
	{
		return *tN;
	}
	else if (false == m_bIsOrder)
	{
		make_heap(&m_pArray[0], &m_pArray[m_nSize], _cmp);
	}
	
	return m_pArray[0];
}

void minHeap::popMin()
{
	if (0 == m_nSize)
	{
		return;
	}
	else if (false == m_bIsOrder)
	{
		make_heap(&m_pArray[0], &m_pArray[m_nSize], _cmp);
	}
	
	--m_nSize;
	if (0 == m_nSize)
	{
		return;
	}
	pop_heap(&m_pArray[0], &m_pArray[m_nSize + 1], _cmp);
	
	return;
}

void minHeap::push(Note * note, int time)
{
	NotePair nP;
	nP.note = note;
	nP.time = time;
	push(nP);
}

void minHeap::push(NotePair & note)
{
	if (m_nSize == m_nVolume - 1)
	{
		return;
	}
	++m_nSize;
	
	m_pArray[m_nSize - 1] = note;
	if (1 == m_nSize)
	{
		return;
	}
	
	make_heap(&m_pArray[0], &m_pArray[m_nSize], _cmp);
	m_bIsOrder = true;
}

void minHeap::minusAll(int value)
{
	for (int i = 0; i < m_nSize; i++)
	{
		m_pArray[i].time -= value;
	}
}

minHeap::~minHeap()
{
	delete[] m_pArray;
}
