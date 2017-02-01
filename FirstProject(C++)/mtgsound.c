#pragma once

#include <windows.h>
#include <mmsystem.h>
 
#pragma comment(lib,"winmm.lib")

#define     MCI_SETAUDIO              0x0873 
#define     MCI_DGV_SETAUDIO_VOLUME    0x4002 
#define     MCI_DGV_SETAUDIO_ITEM      0x00800000 
#define     MCI_DGV_SETAUDIO_VALUE     0x01000000 
#define     MCI_DGV_STATUS_VOLUME  0x4019


typedef struct 
{ 
	DWORD dwCallback; 
	DWORD dwItem; 
	DWORD dwValue; 
	DWORD dwOver; 
	LPSTR lpstrAlgorithm; 
	LPSTR lpstrQuality; 
} MCI_DGV_SETAUDIO_PARMS; 
/////////////////////////////////////////
MCI_OPEN_PARMS mciOpenParms;
DWORD wDeviceID;
LONG m_nTotalTime;
MCI_PLAY_PARMS  mciPlayParms;

UINT m_h1=-1;
UINT m_h2=-1;
/////////////////////////////////////



/////////////////////////////////////////
void MTGOpen(LPSTR filename)
{
    MCI_STATUS_PARMS mciStatusParms;

    mciOpenParms.lpstrElementName = filename;                           //ȭ�� ����
    mciOpenParms.lpstrDeviceType = "MPEGVideo";                     //����̽� �� waveaudio��
    mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT|MCI_OPEN_TYPE,
                    (DWORD)(LPVOID)&mciOpenParms);          //MCI_OPEN ����� �ش�.
    wDeviceID = mciOpenParms.wDeviceID;                     //���� ����̽� ���̵� �޴���.
    mciStatusParms.dwItem = MCI_STATUS_LENGTH;
    mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);
    m_nTotalTime = (LONG)mciStatusParms.dwReturn;
}
BOOL MTGPause()
{

    mciSendCommand(wDeviceID,MCI_PAUSE,MCI_NOTIFY,
                    (DWORD)(LPVOID) &mciPlayParms);
    return TRUE;
}
BOOL MTGPlay()
{
    mciSendCommand(wDeviceID,MCI_PLAY,MCI_NOTIFY,
                    (DWORD)(LPVOID) &mciPlayParms);
    return TRUE;
}

BOOL MTGStop()
{
    mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
    return TRUE;
}

void MTGSetPosition(DWORD dwPos)
{

    MCI_SEEK_PARMS mciSeekParms;
    mciSeekParms.dwTo = dwPos;
    mciSendCommand(wDeviceID, MCI_SEEK, MCI_TO, (DWORD)(LPVOID)&mciSeekParms);
    MTGPlay();
}

DWORD MTGGetMode()
{

    DWORD dwMode;
    MCI_STATUS_PARMS mciStatusParms;

    mciStatusParms.dwItem = MCI_STATUS_MODE;
    mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);
    dwMode = (LONG)mciStatusParms.dwReturn;

    return dwMode;
}
 

DWORD MTGGetPosition()
{

    DWORD nTime;

    MCI_STATUS_PARMS mciStatusParms;
    mciStatusParms.dwItem = MCI_STATUS_POSITION;
    mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);

    nTime = (LONG)mciStatusParms.dwReturn;
    return nTime;
}

DWORD MTGGetLength()
{

    DWORD nTime;
    MCI_STATUS_PARMS mciStatusParms;

    mciStatusParms.dwItem = MCI_STATUS_LENGTH;
    mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);
    nTime = (LONG)mciStatusParms.dwReturn;

    return nTime;
}
void MTGSetVolume( DWORD volume ) 
{    //Volume: 0 - 1000 
	MCI_DGV_SETAUDIO_PARMS  p;

	if( volume>100 ) volume=100; 
	if( volume<0   ) volume=0; 

	volume *= 10; 

	p.dwCallback = 0; 
	p.dwItem     = MCI_DGV_SETAUDIO_VOLUME; 
	p.dwValue    = volume; 
	p.dwOver     = 0; 
	p.lpstrAlgorithm = NULL; 
	p.lpstrQuality   = NULL; 

	mciSendCommand( wDeviceID, MCI_SETAUDIO,MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&p ); 
} 

int MTGGetVolume() 
{ 
  MCI_STATUS_PARMS p; 

  p.dwCallback = 0; 
  p.dwItem     = MCI_DGV_STATUS_VOLUME; 
  mciSendCommand( wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&p ); 

  return (int)(p.dwReturn/10);  // Volume: 0 - 1000  
} 

void MTGPlayWave(char* filename, int ch)
{
	MCI_OPEN_PARMS a;
	MCI_PLAY_PARMS b;
	DWORD r;
	UINT chid;
	

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

	
	a.lpstrDeviceType = "WaveAudio";
	a.lpstrElementName = filename;
	// ���� ī�带 ���� �ڵ��� Ȯ��
	r = mciSendCommand(ch, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&a);
	//if( r )
	//{
	//}
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


