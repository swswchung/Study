// DCView.h : CDCView Ŭ������ �������̽�
//

#pragma once
#include "socket.h"
#include "game.h"
#include "Chat.h"
#include "afxwin.h"

class CMainFrame;
class CDCView : public CView
{
protected: // serialization������ ��������ϴ�.
	CDCView();
	DECLARE_DYNCREATE(CDCView)

// Ư���Դϴ�.
public:
	CDCDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CDCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	Socket m_Socket;
	void RunConnect(int error);
	void RunReceive(int error);
	void RunClose(int error);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	Game m_Game;
	char PlayerID[20];
	int PlayerIndex;
	void Connect(void);
	void SendLogin();
	void GetInfo(char* id, int index);
	void SendXY(void);
	void SendReady(bool ready);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SendSpace(void);
	void SendMe(int newindex);
	void SendOne(char* id, int index);
	CDC m_backDC;
	CBitmap m_backBit;
	CDC m_backBufferDC;
	CBitmap m_backBuffer;
	bool end;
	
	void SendMsg(char* msg);
	void SendStage(int stage);
	CDC onedc;
	CDC twodc;
	CBitmap onep;
	CBitmap twop;
};

#ifndef _DEBUG  // DCView.cpp�� ����� ����
inline CDCDoc* CDCView::GetDocument() const
   { return reinterpret_cast<CDCDoc*>(m_pDocument); }
#endif

