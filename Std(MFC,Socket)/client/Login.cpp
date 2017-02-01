// Login.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DC.h"
#include "Login.h"
#include "MTGSOUND.h"

#define MP1 "1.mp3"


// Login ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Login, CDialog)

Login::Login(CWnd* pParent /*=NULL*/)
	: CDialog(Login::IDD, pParent)
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_id);
}


BEGIN_MESSAGE_MAP(Login, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &Login::OnBnClickedButton1)
END_MESSAGE_MAP()

BOOL Login::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_pWnd = (CFrameWnd*)AfxGetMainWnd();
	m_pView = (CDCView*)(m_pWnd->GetActiveView());

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


// Login �޽��� ó�����Դϴ�.

void Login::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if(m_id.GetLength()==0)
	{
		AfxMessageBox("�ѱ��ڶ� �Է����ּ���");
		return;
	}
	strcpy(m_pView->PlayerID,m_id);

	UpdateData(FALSE);
	
	m_pView->Connect();

	OnOK();
}

