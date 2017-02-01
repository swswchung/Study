#pragma once
//////////////////////////////////
//								\\
//								\\
//	   ���ʻ�,�̼� ���Ӽ���		\\
//								\\
//								\\
//////////////////////////////////
//�α���
#define CS_LOGIN 0	//Ŭ���̾�Ʈ ->����
#define SC_RLOGIN 1 // ���� -> Ŭ���̾�Ʈ
#define SCA_NEWUSER 2 //������ ��� Ŭ���̾�Ʈ
#define CS_SENDME 3
#define CS_SENDONE 4
#define SC_OLDUSER 5
//����
#define CS_XY 11 //��ǥ �ѱ�
#define SCA_XY 12 //��ǥ �Ѹ�
#define CS_SPACE 13  //Ʋ���� ����
#define SCA_COLLECT 14 //����
#define SCA_INCOLLECT 15 //����
#define CS_NEXTSTAGE 16 // ��������������
#define SCA_END 17 //��������
//�κ�
#define CS_READY 21 //�غ񴩸�
#define SCA_READY 22 //�ٸ�����ڰ� �غ񴩸�
#define SCA_START 23 //���� ������ �غ񴩸��� ����
//ä��
#define CS_MSG 31
#define SCA_MSG 32
////////////////////////////////////////////////
//-----------------------------------------------------------------------
typedef struct _S_H
{
	int cmd;
	int len;

}S_H;

typedef struct _S_LOGIN
{
	char id[20];

}S_LOGIN;

typedef struct _S_RLOGIN
{
	char id[20];
	int index;
	int ret; //-1 �� ���Ӿȵ� 1�� ���� ��
	
}S_RLOGIN;

typedef struct _S_NEWUSER
{
	char id[20];
	int index;

}S_NEWUSER;

typedef struct _S_ME
{
	char id[20];
	int index;
	int newindex;
}S_ME;

typedef struct _S_ONE
{
	int index;
}S_ONE;

typedef struct _S_OLDUSER
{
	char id[20];
	int index;
}S_OLDUSER;

typedef struct _S_XY
{
	int index;
	int x;
	int y;
}S_XY;

typedef struct _S_READY
{
	int index;
	bool ready;
}S_READY;

typedef struct _S_START
{
	bool start;
	int stage;
}S_START;

typedef struct _S_SPACE
{
	int stage;
	int x;
	int y;
}S_SPACE;

typedef struct _S_COLLECT
{
	int index;
	int stage;
	int i;
	int count;
}S_COLLECT;

typedef struct _S_INCOLLECT
{
	int stage;
	int index;
}S_INCOLLECT;

typedef struct _S_NEXTSTAGE
{
	int stage;
}S_NEXTSTAGE;

typedef struct _S_END//���� ǥ��
{
	int count;
	int index;
	char id[20];
}S_END;

////////////////////////////////////

typedef struct _S_MSG
{
	char msg[80];

}S_MSG;

typedef struct _S_RMSG
{
	char id[20];
	char msg[80];

}S_RMSG;

typedef struct _S_LOGOUT
{
	
}S_LOGOUT;

typedef struct _S_RLOGOUT
{
	char id[20];
}S_RLOGOUT;