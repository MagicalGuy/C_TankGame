#include"stdio.h"
#include"stdlib.h"
#include"windows.h"
#include"TankGame.h"
#include"Utils.h"
#include"editMap.h"
#include"Draw.h"

void WelcomeScreen() {
	setEnglish();
	system("cls");
	gotoXY(20,5);
	color(14);
	printf("        〓██▄▄▄▄▄▄\n");
	gotoXY(20, 6);
	printf("    ▄▅██████▅▄▃▂\n");
	gotoXY(20, 7);
	printf("██████████████\n");
	gotoXY(20, 8);
	printf("◥⊙▲⊙▲⊙▲⊙▲⊙▲⊙▲◤\n");
	gotoXY(20, 10);
	printf("1、开始游戏\n");
	gotoXY(20, 11);
	printf("2、编辑地图\n");
	gotoXY(20, 12);
	printf("3、操作说明\n");
	gotoXY(20, 13);
	printf("4、退出游戏\n");
	gotoXY(20, 14);
	printf("请输入您的操作选项：");

	int flag = 1;
	char operate;
	while(flag) {
		operate = getchar();
		switch (operate) {
		case '1':startGame(); flag = 0; break;
		case '2':edit_map(); flag = 0; break;
		case '3':printInstru(); flag = 0; break;
		case '4':exit(0); flag = 0; break;
		default:printf("输入错误，请重新输入：");break;	
		}
	}
}

//打印操作说明
void printInstru() {

	system("cls");
	gotoXY(20,10);
	printf("游戏中wsad按键分别控制坦克的上下左右");
	gotoXY(20, 12);
	printf(" 游戏中f键攻击，p键暂停，空格键开始 ");
	gotoXY(1, 14);
	printf("编辑地图中按四个箭头移动光标，t、g、r键分别创建土墙，钢墙和擦除，空格键则结束编辑开始游戏");
	gotoXY(20, 16);
	system("pause");
	getchar();
	WelcomeScreen();
}
//打印围墙
void printBorder() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);//白色
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	for (int i = 0; i<38; i++)
		printf("■                                                                            ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
}


void printBase() {

	for (int i = 0; i < 3; i++)          //打印基地
		for (int j = 0; j < 3; j++)
		{
			if (base.Shape[i][j] == 2) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				gotoXY(36 + 2 * j, 36 + i);
				printf("■");
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				gotoXY(36 + 2 * j, 36 + i);
				printf("■");
			}
		}
}


void printExist() {
	for (int j = 0; j < 38; j++)
		for (int i = 0; i < 38; i++)
			if (existence[i][j] == 3)//土墙
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				gotoXY(2 + 2 * j, 1 + i);
				printf("■");
			}
			else if (existence[i][j] == 4)////钢墙
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoXY(2 + 2 * j, 1 + i);
				printf("■");
			}
}

//打印坦克
void printTank(Object* tank) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			if (tank->Shape[i][j] == 2 && tank->Camp == 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);// 红色
				gotoXY(2 * tank->CoordX + 2 * j - 2, tank->CoordY + i - 1);
				printf("■");
			}
			if (tank->Shape[i][j] == 2 && tank->Camp == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);//淡蓝色
				gotoXY(2 * tank->CoordX + 2 * j - 2, tank->CoordY + i - 1);
				printf("■");
			}
		}
}


void clearTank(Object* tank) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			gotoXY(2 * tank->CoordX + 2 * j - 2, tank->CoordY + i - 1);
			printf("  ");
		}
}

//打印自己的子弹
void printBullet() {
	for (int i = 0; i < 50; i++) {
		if (ownBullet[i].CoordX != 0 && ownBullet[i].CoordY != 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			gotoXY(ownBullet[i].CoordX * 2, ownBullet[i].CoordY);
			ownBullet[i].ID = i;
			printf("◎");
		}
	}
}

//打印敌人子弹
void printBadBullet(Object* badBullet) {

	if (badBullet->CoordX != 0 && badBullet->CoordY != 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		if (badBullet->CoordX * 2 < 80) {
			gotoXY(badBullet->CoordX * 2, badBullet->CoordY);
			printf("  ");
		}
		gotoXY(badBullet->CoordX * 2, badBullet->CoordY);
		printf("◎");
	}
}


//打印计分
void printScoreboard() {
	gotoXY(5 * 2, 41);
	printf("                               ");
	gotoXY(10 * 2, 41);
	printf("                               ");
	gotoXY(5 * 2, 41);
	printf("score: %d", score);
	gotoXY(12 * 2, 41);
	printf("HP: %d", ownTank.HealthPoint);
}


//清除自己的子弹
void clearBullet(Object* object) {
	for (int i = 0; i < 50; i++) {
		if (object[i].CoordX != 0 && object[i].CoordY != 0) {
			gotoXY(object[i].CoordX * 2, object[i].CoordY);
			printf("  ");
		}
	}
}

//清除敌方坦克子弹
void clearBadBullet(int x, int y) {
	if (x != 0 && y != 0)
	{
		gotoXY(2 * x, y);
		printf("  ");
	}
}

