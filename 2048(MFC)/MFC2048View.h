
// MFC2048View.h : CMFC2048View Ŭ������ �������̽�
//

#pragma once
#include "Board.h"

class CMFC2048View : public CView
{
protected: // serialization������ ��������ϴ�.
	CMFC2048View();
	DECLARE_DYNCREATE(CMFC2048View)

// Ư���Դϴ�.
public:
	CMFC2048Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CMFC2048View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

// Ŭ���� ����
public:
	Board m_Board;
	CPoint pt;
	bool m_drag;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMoveLog();
	afx_msg void OnOnlyNum();
	afx_msg void OnNumCol();
	afx_msg void OnTurnLog();
	afx_msg void OnUpdateMoveLog(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNumCol(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOnlyNum(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTurnLog(CCmdUI *pCmdUI);
	bool m_bOnlyChecked;
	bool m_bNCChecked;
	bool m_bMLogChecked;
	bool m_bTLogChecked;
};

#ifndef _DEBUG  // MFC2048View.cpp�� ����� ����
inline CMFC2048Doc* CMFC2048View::GetDocument() const
   { return reinterpret_cast<CMFC2048Doc*>(m_pDocument); }
#endif

