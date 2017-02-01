#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mtg.h"
#include "mtgsound.h"

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define BG1 "1.mp3"
#define BG2 "2.mp3"
#define BG3 "3.mp3"
#define EP1 "1.wav"

#define MapX 45
#define MapY 25
////////////////////////////////
//����ü

struct Enemy //����
{
	int x;
	int y;
	int life;
	int type;
	int speed;
};
struct Enemy g_Enemy[100];

struct Player //�÷��̾� 
{
	int x;
	int y;
	int life;
};
struct Player g_Player;
////////////////////////////////////////
// ���� ���� 
char g_Debug[80]="DEBUG";
int g_Stage=0; //���ʹ���������+1
int g_RunManX=0;
int g_RunManY=21;
int g_RunManXX=70;
int g_RunManYY=16;
int g_Color=1;
int g_cho;
int g_bun;
int g_si;
int g_RainBowX=15;//������x
int g_RainBowY=0;//������y
int g_RainBow=1;
int g_EnemyColor=1; 
int g_WallX=4; //�𼭸����ִ� ���׶��
int g_WallXR=27; //�𼭸����ִ� ���׶��
int g_WallY=1; //�𼭸����ִ� ���׶��
int Slug=200; //���������½ð� 1�ʸ���-1
int Speed;
int RainBowSlug=400;
int g_Score=0;
int g_Time_Score=0;
int StillAlive;
////////////////////////////////////////
//��
char g_Map[MapY][MapX+3]=
{
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��",
	"��                         ��"
};
////////////////////////////////////////
// ȭ�� ó��

void EnemyLife()// ���� �̵��Ұ������� ���� ������-1
{
	int i;

	for(i=0;i<100;i++)
	{
		if(27<=g_Enemy[i].x || 3>=g_Enemy[i].x ||  24<=g_Enemy[i].y)
		{
			g_Enemy[i].life=-1;
		}
	}
}
void TimeMap()//�ð����
{
	char tmp[50];
	sprintf(tmp,"�÷��̽ð� : %d�� %d�� %d��",g_si,g_bun,g_cho);
	_DrawText(45,19,tmp);
	sprintf(tmp,"�� �ӵ� : %d%%  (�ִ�200%%)",Speed);
	_DrawText(45,20,tmp);
}
int PlayerMove(int sx, int sy, int dx, int dy) //�÷��̾��̵�����
{
	if(sx<4 || sx>27)
	{
		return -1;
	}
	else
	{
		return 1;
	}
	return -1;
}
void Move()//�÷��̾��̵�
{
	char k;
	k=_GetKey();

	if(k==KEY_LEFT)
	{
		if(1==PlayerMove(g_Player.x-1,g_Player.y,g_Player.x,g_Player.y))
		{
			g_Player.x--;
		}
	}
	else if(k==KEY_RIGHT)
	{
		if(1==PlayerMove(g_Player.x+1,g_Player.y,g_Player.x,g_Player.y))
		{
			g_Player.x++;
		}
	}
}
void Creater()//��������°� ����
{
	_DrawTextColor(60,22,"������ ���ʻ�",3);

	_DrawTextColor(60,24,"��������:q",3);
}
void RunMan()//�̻����� ���� ����ġ�»��
{
	char msg[20];

	sprintf(msg,"���١ڡٿ�");

	_DrawTextColor(g_RunManX,g_RunManY,msg,g_Color);
}
void MoveRunMan()//�̻����� ���� ����ġ�»���� �̵����
{
	static long oldT=0;
	long newT;

	newT=_GetTickCount();

	if(50 <= newT-oldT)
	{
		if(g_Stage==1)
		{
		g_RunManX++;
		oldT=newT;
		g_Color++;
		}
		if(16 <=g_Color)
		{
			g_Color=1;
		}
		if(70 <= g_RunManX)
		{
			g_RunManX=0;
		}
		_Invalidate();
	}
}
void GameOverYo() // �׿���
{
	char tmp[30];
	int TimeScore;
	int Score;
	int FinalScore;
	char k;
	StillAlive=-1;

	
		k=_GetKey();
			_cls();
			TimeScore=g_Time_Score*87;
			FinalScore=TimeScore;
			_DrawText(40,11,"GameOver");
			sprintf(tmp,"������? : %d",FinalScore);
			_DrawText(40,12,tmp);
			_DrawText(50,5,"���������");
			_BitBlt();
			_Delay(1000);
	
	MTGStop();
	MTGOpen(BG3);
	MTGSetVolume(100);
	MTGPlay();
}
void GameOver()//�׿�������
{
	int i;
	if(g_Stage==2)
	{
		if(g_WallX==g_Player.x && g_WallY==g_Player.y)
		{
			GameOverYo();
		}
		if(g_RainBowX==g_Player.x && g_RainBowY==g_Player.y)
		{
			GameOverYo();
		}
		for(i=0;i<100;i++)
		{
			if(1==g_Enemy[i].life)
			{
				if(g_Player.x==g_Enemy[i].x && g_Player.y==g_Enemy[i].y)
				{
					GameOverYo();
				}
			}
		}
	}
}
void Check()//�����ܰ�� �Ѿ������ �ܰ�
{
	_DrawText(30,12,"EnterŰ�� �����ּ���");
}
void Main()//������ ����, �������� ����ġ�»�� ����
{
	_DrawTextColor(1,1,"  �ܡܡ�    ��     ��           �ܡ�   �� ��     ��     ��",7);
	_DrawTextColor(1,2,"�ܡܡܡܡ�  ��     ��          ��  �ܡܡ� ��    ��    �ܡ�",7);
	_DrawTextColor(1,3,"   �ܡ�     �� ��  ��           �ܡ�   �� ��   �� ��    ��",7);
	_DrawTextColor(1,4,"  ��  ��    ��     �ܡܡܡܡ�          �� ��  ��    ��  ��",7);
	_DrawTextColor(1,5,"   �ܡ�     ��                         �� ��            ��",7);
	_DrawTextColor(1,6,"                 �ܡܡܡܡܡܡ�",7);                           
	_DrawTextColor(1,7,"                                                          ",7);
	_DrawTextColor(1,8,"                    �ܡܡܡ�",7);                      
	_DrawTextColor(1,9,"                        ��",7);                       
	_DrawTextColor(1,10,"                      ��",7);                         
	_DrawTextColor(1,11,"                     �ܡܡܡ�",7);                    
	_DrawTextColor(1,12,"      ��      ��  ��   �ܡܡܡ�   ��  ��",7);            
	_DrawTextColor(1,13,"      ��      ��  ��        ��    ��  ��",7);         
	_DrawTextColor(1,14,"      ��      �ܡܡ�      ��      ��  ��",7);           
	_DrawTextColor(1,15,"      �ܡܡܡܡ�  ��    �ܡܡܡ�  ��  �ܡܡܡܡ�",7);    
	_DrawTextColor(1,16,"              ��  ��              ��",7);                  
	_DrawTextColor(1,17,"                                    �ܡܡܡܡܡ�",7);
	_DrawTextColor(1,18,"                                      ��",7);
	_DrawTextColor(1,19,"                                      ��",7);
	_DrawTextColor(1,20,"                                      �ܡܡܡܡ�",7);
	_DrawTextColor(59,1,"     �ܡܡܡܡ�  ��",10);
	_DrawTextColor(59,2,"        �� ��    ��",10);
	_DrawTextColor(59,3,"      �ܡܡܡܡ� ��",10);
	_DrawTextColor(59,4,"                 ��",10);
	_DrawTextColor(59,5,"       �ܡܡ�     ",10);
	_DrawTextColor(59,6,"     �ܡܡܡܡ� ��",10);
	_DrawTextColor(59,7,"        �ܡ�    ��",10);
	_DrawTextColor(59,8,"       ��  ��   �ܡ�",10);
	_DrawTextColor(59,9,"        �ܡ�    ��",10);
	_DrawTextColor(59,10,"                ��",10);
	_DrawTextColor(59,12,"      �ܡܡܡ�  ��",10); 
	_DrawTextColor(59,13,"            ��  ��",10);
	_DrawTextColor(59,14,"            ��  ��",10);
	_DrawTextColor(59,15,"            ��  ��",10);
	_DrawTextColor(59,16,"                ��",10);
	_DrawTextColor(50,8,"��    ��  ��",14);
	_DrawTextColor(50,9,"��    ��  ��",14);
	_DrawTextColor(50,10,"�ڡڡڡڡڡ�",14);
	_DrawTextColor(50,11,"��    ��  ��",14);
	_DrawTextColor(50,12,"�ڡڡڡڡڡ�",14);
	_DrawTextColor(50,13,"          ��",14);
	_DrawTextColor(50,14,"  �ڡڡڡ�",14);
	_DrawTextColor(50,15,"      ��",14);
	_DrawTextColor(50,16,"    ��",14);
	_DrawTextColor(50,17,"   �ڡڡڡ�",14);
	_DrawTextColor(20,23,"Enter : ���ӽ���, 'q' : ��������",5);
	RunMan();
}
void EnemySpot(int i) //�� ���� ��ġ
{
	int a;
	
	
	a=rand()%4;
	if(0==a)
	{
		a=rand()%8+3;
		g_Enemy[i].x=a;
		g_Enemy[i].y=1;

		a=rand()%5+1;
		g_Enemy[i].type=a;
	}
	else if(1==a)
	{
		a=rand()%16+3;
		g_Enemy[i].x=a;
		g_Enemy[i].y=1;

		a=rand()%10+1;
		g_Enemy[i].type=a;
	}
	else if(2==a)
	{
		a=rand()%24+3;
		g_Enemy[i].x=a;
		g_Enemy[i].y=1;

		a=rand()%9+1;
		g_Enemy[i].type=a;
	}
	else if(3==a)
	{
		a=rand()%30+3;
		g_Enemy[i].x=a;
		g_Enemy[i].y=1;

		a=rand()%8+1;
		g_Enemy[i].type=a;
	}
}
void EnemyStart() //������ ������ �ο�
{
	int i;
	int a;

	for(i=0;i<50;i++)
	{
		if(-1==g_Enemy[i].life)
		{
			a=rand()%5;

			if(0==a)
			{
				g_Enemy[i].life=1;
				EnemySpot(i);
			}
		}
	}
}
void ShowWall() //�� ��系��
{
	int i;
	char tmp[40];
	for(i=0;i<50;i++)
	{
		if(1==g_Enemy[i].life)
		{
			_DrawTextColor(g_Enemy[i].x,g_Enemy[i].y,"��",14);
		}
	}
	_DrawTextColor(g_RainBowX,g_RainBowY,"��",g_RainBow);
	sprintf(tmp,"o");
	_DrawText(g_WallX,g_WallY,tmp);
	sprintf(tmp,"o");
	_DrawText(g_WallXR,g_WallY,tmp);
}
void DownWall() //�𼭸����ִ� ���׶�� �̵�
{
	static long OLD=0;
	long NEW;

	NEW=_GetTickCount();
	if(100<= NEW-OLD)
	{
		OLD=NEW;
		g_WallY++;
		if(26 <= g_WallY)
		{
			g_WallY=0;

			_Invalidate();
		}
	}
	if(g_WallX==g_Player.x && g_WallY==g_Player.y)
	{
		GameOverYo();
	}
	if(g_WallXR==g_Player.x && g_WallY==g_Player.y)
	{
		GameOverYo();
	}
}
void RainBow()//������
{
	static long oldR=0;
	long newR;

	newR=_GetTickCount();
	if(RainBowSlug <= newR-oldR)
	{
		if(g_Stage==2)
		{
			g_RainBowY++;
			oldR=newR;
			g_RainBow++;

			_Invalidate();
		}
		if(24 <= g_RainBowY)
		{
			g_RainBowY=0;
		}
		if(g_RainBowX < g_Player.x)
		{
			g_RainBowX++;
		}
		if(g_Player.x < g_RainBowX)
		{
			g_RainBowX--;
		}
		if(16 <= g_RainBow)
		{
			g_RainBow=1;
		}
	}

}
void ShowPlayer()//�÷��̾� ���
{
	_DrawText(g_Player.x,g_Player.y,"��");
}
void RandomMove() //�� ������
{
	int i;

	for(i=0;i<100;i++)
	{
		if(1==g_Enemy[i].life)
		{
			switch(g_Enemy[i].type)
			{
			case 1:
				g_Enemy[i].y++;
				break;
			case 2:
				g_Enemy[i].y++;
				break;
			case 3:
				g_Enemy[i].x++;
				g_Enemy[i].y++;
				break;
			case 4:
				g_Enemy[i].y++;
				break;
			case 6:
				g_Enemy[i].y++;
				break;
			case 7:
				g_Enemy[i].x--;
				g_Enemy[i].y++;
				break;
			default:
				g_Enemy[i].life=-1;
				break;
			}
		}
	}
}
void Game()//���� ����
{

	int y;
	//�����
	//Map();
	for(y=0; y<MapY; y++)
	{
		_DrawText(1,y,g_Map[y]);
	}
	//�÷��̾����
	ShowPlayer();
	//�����
	ShowWall();
	//�ð����
	TimeMap();
	GameOver();
	
	
}

void Draw()
{	
	switch(g_Stage)
	{
	case 0:
		Check();
		break;
	case 1:
		Main();
		break;
	case 2:
		Game();
		break;
	}
	Creater();

	_DrawText(50,0,g_Debug);
}
/////////////////////////////////////////
// �̺�Ʈ 
void RunStart()//ó��ȭ�� ��Ÿ��ũ�Ҹ�����
{
	int x=0;
	char msg[30]="��Now Loading��";

	MTGOpen(EP1); 
	MTGSetVolume(100);
	MTGPlay();

	while(1)
	{
		_DrawTextOrg(x,12,msg);
		x++;
		if(x > 65)
		{
			break;
		}
		_Delay(45);
	}
	_Invalidate();
}
void RunTime() //�ð�â
{
	static long old1=0; 
	long new1;

	new1=_GetTickCount();

	if(1000<=new1-old1)
	{
		if(g_Stage==2)
		{
			old1=new1;
			Slug--;
			RainBowSlug--;
			g_cho++;
			g_Time_Score++;
			Speed++;
			_Invalidate();
		}
		if(Slug<=50)
		{
			Slug++;
		}
		if(200<=Speed)
		{
			Speed--;
		}
		if(g_cho == 60)
		{
			g_cho=0;
			g_bun++;
			_Invalidate();
		}
		if(g_bun == 60)
		{
			g_bun=0;
			g_si++;
			_Invalidate();
		}

	}
	_Invalidate();
}
	void EnemyTimeA() //�� ������ �ο� �ð�
{
	static long old=0;
	long time;

	time=_GetTickCount();

	if(g_Stage==2)
	{
		if(Slug<=time-old)
		{
			old=time;
			EnemyStart();
		}
	}
}
void EnemyTimeB()//�� �������� �ð�
{
	int i=100;
	static long old=0;
	long time;

	time=_GetTickCount();

	if(Slug<=time-old)
	{
		old=time;
		RandomMove();
	}
}
int RunKey(char k)// Ű���� ����
{
	Move();
	if(k==13)
	{
		g_Stage++;
		if(1 < g_Stage)
		{
			g_Stage=2;
		}
		if(g_Stage==0)
		{

		}
		else if(g_Stage==1)
		{  
			MTGStop();
			MTGOpen(BG1);
			MTGSetVolume(100);
			MTGPlay();

		}else if(g_Stage==2)
		{
			g_Player.x=18;
			g_Player.y=24;
			MTGStop();
			MTGOpen(BG2);
			MTGSetVolume(100);
			MTGPlay();
		}
	}
	if('q'==k)
	{
		exit(1);
	}
	sprintf(g_Debug,"key:%d Press 'q' key to Quit!",k);

	return 0;
}
void StageTime()
{
	
	EnemyLife();
	EnemyTimeA();
	EnemyTimeB();
	RunTime();

	_Invalidate();
}
/////////////////////////////////////////
// GameMain
void GameMain() 
{
	char k;
	
	RunStart();

	while(1)
	{
		MoveRunMan();
		RainBow();
		GameOver();
		StageTime();
		DownWall();
		k=_GetKey();
		if(-1==k) continue;		
		if(-1==RunKey(k))
		{
			break;
		}
		_Invalidate();
	}

}
///////////////////////////////////////////
// main
int main(void) 
{
	_BeginWindow();

	GameMain();

	_EndWindow();

	return 0;
}