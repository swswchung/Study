#pragma once
#define MAX_USER 2
typedef struct  _S_USER
{
	SOCKET cid; //����id
	char id[20]; //�̸�
	int index; //�ĺ���ȣ
	bool ready; //�غ����
	int count;  //���� ����
	int stage;
	int check; // -1�� ���ƴ� 1 �� �����
}S_USER;

extern S_USER g_aUser[MAX_USER];
void IniUser();
int GetEmptyUser(SOCKET cid);