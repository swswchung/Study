#pragma once



// Interface �� ���Դϴ�.

class Interface : public CFormView
{
	DECLARE_DYNCREATE(Interface)

protected:
	Interface();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~Interface();

public:
	enum { IDD = IDD_INTERFACE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};


