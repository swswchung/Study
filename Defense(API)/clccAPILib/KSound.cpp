#include "StdAfx.h"
#include "KSound.h"

#include <vfw.h>

extern HINSTANCE hInst;

KSound::KSound(void)
{
	m_Video=NULL;

	m_h1 = -1;
	m_h2 = -1;
}

KSound::~KSound(void)
{
}
BOOL KSound::PlayMp3(HWND hWnd,TCHAR* path)
{	
	if(NULL != m_Video)
		StopMp3();

	m_Video = MCIWndCreate(hWnd,
		  hInst,
		  WS_CHILD | MCIWNDF_NOMENU,path);
	MCIWndPlay(m_Video);
	return TRUE;
}

void KSound::StopMp3()
{
	MCIWndStop(m_Video);
	if(m_Video !=NULL)
	{
		MCIWndDestroy(m_Video);
		
	}
}

void KSound::PlayWave(TCHAR* filename, int ch)
{
	if( 0 == ch )
	{
		if( -1 != m_h1)
		{
			//0��ä�� ���� ����̽��� �����ִٸ� �ݴ´�.
			mciSendCommand(m_h1, MCI_CLOSE, 0, (DWORD)NULL);
		}
	}
	else
	{
		if( -1 != m_h2)
		{
		//1��ä�� ���� ����̽��� �����ִٸ� �ݴ´�.
		mciSendCommand(m_h2, MCI_CLOSE, 0, (DWORD)NULL);
		}
	}

	MCI_OPEN_PARMS a;
	MCI_PLAY_PARMS b;
	DWORD r;
	a.lpstrDeviceType = _T("WaveAudio");
	a.lpstrElementName = filename;
	// ���� ī�带 ���� �ڵ��� Ȯ��
	r = mciSendCommand(ch, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&a);
	//if( r )
	//{
	//}
	UINT chid;
	chid = a.wDeviceID; //ä�ι�ȣ�� �Ѱ��ش�.
	//�ڵ��� �̿��� �÷��� ����� ������.
	mciSendCommand(chid, MCI_PLAY, 0, (DWORD)(LPVOID)&b);
	// ���� ��ɵ� ���������� ������������ ���� Ȯ���Ѱ��� ����̽��� �ݴ°��̴�.
	if( 0 == ch ) //0�� ä��
	{
		m_h1 = chid;
	}
	else //1�� ä��
	{
		m_h2 = chid;
	}
}