#include"stdio.h"
#include"stdlib.h"
#include"Utils.h"
#include"windows.h"
#include"conio.h"
#include"TankGame.h"
#include"Draw.h"
#include"editMap.h"

void edit_map() {
	system("cls");

	int x = 1, y = 4;//编辑地图光标的坐标
	int map[38][38] = { 0 };//自定义的地图

	char key;

	for (int i = 0; i < 38; i++)      //初始化
		for (int j = 0; j < 38; j++)
			existence[i][j] = 0;   //置空

	ownTank.CoordX = 6;//初始化坦克
	ownTank.CoordY = 37;
	ownTank.Camp = 1;
	ownTank.Direction = 0;

	//敌方坦克位置的初始化
	for (int i = 0; i < 3; i++) {
		enemyTank[i].CoordX = 2 + i * 15;
		enemyTank[i].CoordY = 2;
		enemyTank[i].Camp = 2;
		enemyTank[i].Direction = 0;
	}

	printBorder();

	int _base[3][3] = { { 3,3,3 },{ 3,2,3 },{ 3,2,3 } };
	for (int i = 0; i < 3; i++)//基地位置初始化
		for (int j = 0; j < 3; j++)
			base.Shape[i][j] = _base[i][j];

	printBase();//打印基地

	int tankUp[3][3] = { { 0,2,0 },{ 2,2,2 },{ 2,0,2 } };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			ownTank.Shape[i][j] = tankUp[i][j];
	printTank(&ownTank);//编辑地图上打印一个我的坦克

	int tankDown[3][3] = { { 2,0,2 },{ 2,2,2 },{ 0,2,0 } };

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			enemyTank[0].Shape[i][j] = tankDown[i][j];
			enemyTank[1].Shape[i][j] = tankDown[i][j];
			enemyTank[2].Shape[i][j] = tankDown[i][j];
		}
	printTank(&enemyTank[0]);//编辑地图上打印三个敌人坦克
	printTank(&enemyTank[1]);
	printTank(&enemyTank[2]);

//	setEnglish();

	int flag = 1;

	while (flag)
	{
		gotoXY(2 * x, y);
		switch (map[y - 1][x - 1])
		{
		case 0:
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
			printf("□");
		}break;
		case 3://土墙
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			printf("■");
		}break;
		case 4://钢墙
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf("■");
		}break;

		}

		if (_kbhit()) //检测，如果有按键就执行if里面的
		{
			key = _getch();//捕获按键
			switch (key)
			{
			case 72: //上箭头
			{
				if (map[y - 1][x - 1] == 0) {
					gotoXY(2 * x, y);
					printf("  ");
				}
				if (y > 4)    y--;//编辑光标活动范围
			}break;
			case 75: //左箭头
			{
				if (map[y - 1][x - 1] == 0) {
					gotoXY(2 * x, y);
					printf("  ");
				}
				if (x > 1)    x--;//编辑光标活动范围
			}break;
			case 77: //右箭头
			{
				if (map[y - 1][x - 1] == 0) {
					gotoXY(2 * x, y);
					printf("  ");
				}
				if (x < 38)   x++;//编辑光标活动范围
			}break;
			case 80: //下箭头
			{
				if (map[y - 1][x - 1] == 0) {
					gotoXY(2 * x, y);
					printf("  ");
				}
				if (y < 38)   y++;//编辑光标活动范围
			}break;
			case 32: //按空格开始游戏
			{
				if (map[y - 1][x - 1] == 0) {
					gotoXY(2 * x, y);
					printf("  ");
				}
				flag = 0;
			}break;
			case 116:  //t键设置土墙
			{
				map[y - 1][x - 1] = 3;
			}break;
			case 103:  //g 键设置钢墙
			{
				map[y - 1][x - 1] = 4;
			}break;
			case 114:  //r 键清空位置
			{
				map[y - 1][x - 1] = 0;
			}break;
			default:;
			}
		}
	}

	for (int i = 0; i < 38; i++)
		for (int j = 0; j < 38; j++)
			existence[i][j] = map[i][j];//将自定义地图数据保存至地图所有物数组

	renewMap();//刷新地图

	startGame();//开始游戏

	system("cls");

}