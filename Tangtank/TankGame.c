#include"stdio.h"
#include"stdlib.h"
#include"conio.h"
#include"Utils.h"
#include"windows.h"
#include"time.h"
#include"TankGame.h"
#include"Draw.h"
#include"Bullet.h"
#include"Tank.h"

int score;  //游戏分数
int enemyCount;//敌人数量
int gameMap[40][40];//游戏地图
int existence[38][38];//地图存在物
Object base;//基地
Object ownTank;//自己的坦克
Object enemyTank[3];//敌人的坦克
Object ownBullet[50];//自己的子弹
Object enemyBullet[3];//敌人坦克的子弹

void initGame() {
	enemyCount = 10;
	score = 0;
	//自己坦克的初始化
	ownTank.Camp = 1;
	ownTank.speed = 100;
	ownTank.CoordX = 6;
	ownTank.CoordY = 37;
	ownTank.Direction = 0;
	ownTank.HealthPoint = 10;

	//敌方坦克的初始化
	for (int i = 0; i < 3; i++) {
		enemyTank[i].CoordX = 2 + i * 15;
		enemyTank[i].CoordY = 2;
		enemyTank[i].Direction = 0;
		enemyTank[i].speed = 400;
		enemyTank[i].Camp = 2;
	}

	int _base[3][3] = { { 3,3,3 },{ 3,2,3 },{ 3,2,3 } };
	for (int i = 0; i < 3; i++)//基地初始化
		for (int j = 0; j < 3; j++)
			base.Shape[i][j] = _base[i][j];

	//自己子弹初始化
	for (int i = 0; i < 50; i++) {
		ownBullet[i].CoordX = 0;
		ownBullet[i].CoordY = 0;
		ownBullet[i].Direction = 0;
	}

	//敌方坦克子弹的初始化
	for (int i = 0; i < 3;i++) {
		enemyBullet[i].CoordX = 0;
		enemyBullet[i].CoordY = 0;
		enemyBullet[i].Direction = 0;
	}

	for (int i = 1; i < 39; i++)//地图清屏
		for (int j = 1; j < 39; j++)
		{
			gotoXY(2 * i, j);
			printf("  ");
		}

	if (isNull()==1) {
		getExistMap();
	}

	renewMap();
	printBase();
	printExist();
	printScoreboard();

	turnUp(&ownTank);
	turnDown(&enemyTank[0]);
	turnDown(&enemyTank[1]);
	turnDown(&enemyTank[2]);
}


int isNull() {
	for (int i = 0; i < 38; i++) {
		for (int j = 0; j < 38; j++) {
			if (existence[i][j] != 0) {
				return 0;
				break;
			}
		}
	}

	return 1;
}

void stopGame() {
	int flag = 0;
	char key;
	while (1)
	{
		for (int i = 0; i < 50; i++)
		{
			Sleep(2000);
			if (_kbhit()) //检测
			{
				key = _getch();//捕获按键
				if (key == 32)
				{
					flag = 1;
					break;
				}
			}
			if (flag)
				break;
		}
		if (flag)
			break;
	}
}



//判断该方向能不能前进
int allowGo(Object* tank) {
	switch (tank->Direction)
	{
	case 1:
		if (gameMap[tank->CoordY - 2][tank->CoordX] == 0 &&
			gameMap[tank->CoordY - 2][tank->CoordX - 1] == 0 &&
			gameMap[tank->CoordY - 2][tank->CoordX + 1] == 0)
			return 1;
		else
			return 0;
	case 2:
		if (gameMap[tank->CoordY + 2][tank->CoordX] == 0 &&
			gameMap[tank->CoordY + 2][tank->CoordX - 1] == 0 &&
			gameMap[tank->CoordY + 2][tank->CoordX + 1] == 0)
			return 1;
		else
			return 0;
	case 3:
		if (gameMap[tank->CoordY][tank->CoordX - 2] == 0 &&
			gameMap[tank->CoordY - 1][tank->CoordX - 2] == 0 &&
			gameMap[tank->CoordY + 1][tank->CoordX - 2] == 0)
			return 1;
		else
			return 0;
	case 4:if (gameMap[tank->CoordY][tank->CoordX + 2] == 0 &&
		gameMap[tank->CoordY - 1][tank->CoordX + 2] == 0 &&
		gameMap[tank->CoordY + 1][tank->CoordX + 2] == 0)
		return 1;
		   else
			   return 0;
	}
	return 0;
}

//向上后刷新
void turnUp(Object* tank1) {
	int tankUp[3][3] = { { 0,2,0 },{ 2,2,2 },{ 2,0,2 } };
	if (tank1->Direction == 1)
	{
		if (allowGo(tank1))
		{
			clearTank(tank1);
			tank1->CoordY--;
			printTank(tank1);
			renewMap();
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				tank1->Shape[i][j] = tankUp[i][j];
		clearTank(tank1);
		printTank(tank1);
		tank1->Direction = 1;
		renewMap();

	}
}


//向下后刷新
void turnDown(Object* tank2) {
	int tankDown[3][3] = { { 2,0,2 },{ 2,2,2 },{ 0,2,0 } };
	if (tank2->Direction == 2)
	{
		if (allowGo(tank2))
		{
			clearTank(tank2);
			tank2->CoordY++;
			printTank(tank2);
			renewMap();
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				tank2->Shape[i][j] = tankDown[i][j];
		clearTank(tank2);
		printTank(tank2);
		tank2->Direction = 2;
		renewMap();
	}
}

//向左后刷新
void turnLeft(Object* tank3) {
	int tankLeft[3][3] = { { 0,2,2 },{ 2,2,0 },{ 0,2,2 } };
	if (tank3->Direction == 3)
	{
		if (allowGo(tank3))
		{
			clearTank(tank3);
			tank3->CoordX--;
			printTank(tank3);
			renewMap();
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				tank3->Shape[i][j] = tankLeft[i][j];
		clearTank(tank3);
		printTank(tank3);
		tank3->Direction = 3;
		renewMap();
	}
}

//向右后刷新
void turnRight(Object* tank4) {
	int tankRight[3][3] = { { 2,2,0 },{ 0,2,2 },{ 2,2,0 } };
	if (tank4->Direction == 4)
	{
		if (allowGo(tank4))
		{
			clearTank(tank4);
			tank4->CoordX++;
			printTank(tank4);
			renewMap();
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				tank4->Shape[i][j] = tankRight[i][j];
		clearTank(tank4);
		printTank(tank4);
		tank4->Direction = 4;
		renewMap();
	}
}


//监测子弹对存在障碍物的改变，即是碰撞后的改变
void existChange() {
	for (int i = 0; i < 50; i++) {
		int m = ownBullet[i].CoordX;
		int n = ownBullet[i].CoordY;
		if (m > 0 && m < 39 && n>0 && n < 39) {//被我坦克子弹击中
			if (existence[n - 1][m - 1] == 3)//打到土墙
			{
				existence[n - 1][m - 1] = 0;
				gotoXY(2 * m, n);
				printf("  ");
				ownBullet[i].CoordX = 0, ownBullet[i].CoordY = 0;//子弹消失
				printExist();
				renewMap();
			}

			else if (existence[n - 1][m - 1] == 4)//打到钢墙
			{
				ownBullet[i].CoordX = 0, ownBullet[i].CoordY = 0;//子弹消失
			}
		}
	}


	for (int i = 0; i < 3;i++) {
	int m1 = enemyBullet[i].CoordX;
	int n1 = enemyBullet[i].CoordY;

	if (m1 > 0 && m1 < 39 && n1>0 && n1 < 39) {//被敌方各坦克的各个子弹击中
		if (existence[n1 - 1][m1 - 1] == 3)//打到土墙
		{
			existence[n1 - 1][m1 - 1] = 0;
			gotoXY(2 * m1, n1);
			printf("  ");
			enemyBullet[i].CoordX = 0, enemyBullet[i].CoordY = 0;
			printExist();
			renewMap();
		}
		else if (existence[n1 - 1][m1 - 1] == 4)//打到钢墙
		{
			enemyBullet[i].CoordX = 0, enemyBullet[i].CoordY = 0;//子弹消失
		}
		else if (existence[n1 - 1][m1 - 1] == 2)//打到坦克
		{
			enemyBullet[i].CoordX = 0, enemyBullet[i].CoordY = 0;//子弹消失
		}
	}
	else {
		if (m1>40||m1<0||n1>40||n1<0) {
		gotoXY(2 * m1, n1);
		printf("  ");
		enemyBullet[i].CoordX = 0, enemyBullet[i].CoordY = 0;
		printExist();
		renewMap();
		}
	}
	}
}

//监测基地的变化
void baseChange() {
	for (int i = 0; i < 50; i++) {
		int m = ownBullet[i].CoordX;
		int n = ownBullet[i].CoordY;
		if (m == 37 && n == 38 || m == 38 && n == 38) {
			gameOver();
			break;
		}

		for (int a = 0; a < 3; a++) {
			for (int b = 0; b < 3; b++) {//自己子弹对基地的碰撞
				if (m == 36 + 2 * a  && n == 36 + b) {
					if (base.Shape[a][b] == 3) {
						base.Shape[a][b] = 0;
						gotoXY(2 * m, n);
						printf("  ");
						ownBullet[i].CoordX = 0;
						ownBullet[i].CoordY = 0;
						printBase();
						renewMap();
					}
				}
			}
		}
	}


	for (int i = 0; i < 3;i++) {

	int m1 = enemyBullet[i].CoordX;
	int n1 = enemyBullet[i].CoordY;//敌人子弹对基地的碰撞
	if (m1 == 37 && n1 == 38 || m1 == 38 && n1 == 38) {
		gameOver();
		return;
	}

	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			if (m1 == 36 + 2 * a  && n1 == 36 + b) {
				if (base.Shape[a][b] == 3) {
					base.Shape[a][b] = 0;
					gotoXY(2 * m1, n1);
					printf("  ");
					enemyBullet[i].CoordX = 0;
					enemyBullet[i].CoordY = 0;
					printBase();
					renewMap();
				}
			}
		}
	}
	}
}


//游戏结束的显示
void gameOver() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoXY(30, 17);
	printf("          游戏结束        ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoXY(32, 23);
	printf("    按 空格键 重新开始或者按 n 返回主菜单    ");

	while (1)
	{
		if (32 == _getch())
		{
			getExistMap();
			renewMap();
			startGame();
			break;
		}
		if('n'== _getch()){
			getExistMap();
			renewMap();
			WelcomeScreen();
			break;
		}
	}
}

//监测游戏是否结束
void checkGame() {
	if (ownTank.HealthPoint == 0)
		gameOver();
	if (enemyCount == 0) {
		printf("您获得游戏的胜利！\n");
		system("pause");
		gameOver();
	}	
}


void getExistMap() {//制造障碍物
	for (int j = 0; j < 38; j++) {
		existence[19][j] = 3;//土墙
		existence[20][j] = 3;
	}

	for (int i = 14; i < 28; i++) {
		existence[21][i] = 4;//钢墙
	}
}


void renewMap() {
	for (int i = 0; i < 40; i++)          //游戏地图初始化
		for (int j = 0; j < 40; j++)
			gameMap[i][j] = 0;

	for (int i = 0; i < 40; i++)    //围墙
	{
		gameMap[i][0] = 4;
		gameMap[i][39] = 4;
	}
	for (int j = 0; j < 40; j++)
	{
		gameMap[0][j] = 4;
		gameMap[39][j] = 4;
	}

	for (int i = 0; i < 38; i++)  //地图所有物
		for (int j = 0; j < 38; j++)
			gameMap[i + 1][j + 1] = existence[i][j];

	for (int i = 0; i < 3; i++)   //基地
		for (int j = 0; j < 3; j++)
			gameMap[i + 36][j + 18] = base.Shape[i][j];

	switch (ownTank.Direction)          //坦克
	{
	case 1:
	{
		gameMap[ownTank.CoordY - 1][ownTank.CoordX - 1] = 0;  gameMap[ownTank.CoordY - 1][ownTank.CoordX] = 2;      gameMap[ownTank.CoordY - 1][ownTank.CoordX + 1] = 0;
		gameMap[ownTank.CoordY][ownTank.CoordX - 1] = 2;    gameMap[ownTank.CoordY][ownTank.CoordX] = 2;        gameMap[ownTank.CoordY][ownTank.CoordX + 1] = 2;
		gameMap[ownTank.CoordY + 1][ownTank.CoordX - 1] = 2;  gameMap[ownTank.CoordY + 1][ownTank.CoordX] = 0;      gameMap[ownTank.CoordY + 1][ownTank.CoordX + 1] = 2;

	}break;
	case 2:
	{
		gameMap[ownTank.CoordY - 1][ownTank.CoordX - 1] = 2;  gameMap[ownTank.CoordY - 1][ownTank.CoordX] = 0;      gameMap[ownTank.CoordY - 1][ownTank.CoordX + 1] = 2;
		gameMap[ownTank.CoordY][ownTank.CoordX - 1] = 2;    gameMap[ownTank.CoordY][ownTank.CoordX] = 0;        gameMap[ownTank.CoordY][ownTank.CoordX + 1] = 2;
		gameMap[ownTank.CoordY + 1][ownTank.CoordX - 1] = 0;  gameMap[ownTank.CoordY + 1][ownTank.CoordX] = 2;      gameMap[ownTank.CoordY + 1][ownTank.CoordX + 1] = 0;

	}break;
	case 3:
	{
		gameMap[ownTank.CoordY - 1][ownTank.CoordX - 1] = 0;  gameMap[ownTank.CoordY - 1][ownTank.CoordX] = 2;      gameMap[ownTank.CoordY - 1][ownTank.CoordX + 1] = 2;
		gameMap[ownTank.CoordY][ownTank.CoordX - 1] = 2;    gameMap[ownTank.CoordY][ownTank.CoordX] = 2;        gameMap[ownTank.CoordY][ownTank.CoordX + 1] = 0;
		gameMap[ownTank.CoordY + 1][ownTank.CoordX - 1] = 0;  gameMap[ownTank.CoordY + 1][ownTank.CoordX] = 2;      gameMap[ownTank.CoordY + 1][ownTank.CoordX + 1] = 2;

	}break;
	case 4:
	{
		gameMap[ownTank.CoordY - 1][ownTank.CoordX - 1] = 2;  gameMap[ownTank.CoordY - 1][ownTank.CoordX] = 2;      gameMap[ownTank.CoordY - 1][ownTank.CoordX + 1] = 0;
		gameMap[ownTank.CoordY][ownTank.CoordX - 1] = 0;    gameMap[ownTank.CoordY][ownTank.CoordX] = 2;        gameMap[ownTank.CoordY][ownTank.CoordX + 1] = 2;
		gameMap[ownTank.CoordY + 1][ownTank.CoordX - 1] = 2;  gameMap[ownTank.CoordY + 1][ownTank.CoordX] = 2;      gameMap[ownTank.CoordY + 1][ownTank.CoordX + 1] = 0;
	}break;
	}

	for (int i = 0; i < 3; i++) {
		switch (enemyTank[i].Direction)  //敌方坦克
		{
		case 1://上
		{
			gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX - 1] = 0;  gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX] = 2;      gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX + 1] = 0;
			gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX - 1] = 2;    gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX] = 2;        gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX + 1] = 2;
			gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX - 1] = 2;  gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX] = 0;      gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX + 1] = 2;

		}break;
		case 2://下
		{
			gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX - 1] = 2;  gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX] = 0;      gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX + 1] = 2;
			gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX - 1] = 2;    gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX] = 0;        gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX + 1] = 2;
			gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX - 1] = 0;  gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX] = 2;      gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX + 1] = 0;

		}break;
		case 3://左
		{
			gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX - 1] = 0;  gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX] = 2;      gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX + 1] = 2;
			gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX - 1] = 2;    gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX] = 2;        gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX + 1] = 0;
			gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX - 1] = 0;  gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX] = 2;      gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX + 1] = 2;

		}break;
		case 4://右
		{
			gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX - 1] = 2;  gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX] = 2;      gameMap[enemyTank[i].CoordY - 1][enemyTank[i].CoordX + 1] = 0;
			gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX - 1] = 0;    gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX] = 2;        gameMap[enemyTank[i].CoordY][enemyTank[i].CoordX + 1] = 2;
			gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX - 1] = 2;  gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX] = 2;      gameMap[enemyTank[i].CoordY + 1][enemyTank[i].CoordX + 1] = 0;
		}break;
		}
	}
}

clock_t time1_start;
clock_t time1_end;
clock_t time2_start;
clock_t time2_end;

void startGame() {
	system("mode con cols=90 lines=45");
	system("title 坦克大战");
	hideCursor();
	printBorder();//打印围墙
	initGame();//初始化数据
	srand((unsigned int)time(NULL));
	while (1) {

		time1_end = clock();
		if (time1_end - time1_start > ownTank.speed)
		{
			time1_start = time1_end;
			tankMove();//自己坦克移动
			ownBulletMove();//自己子弹移动
		}

		time2_end = clock();
		if (time2_end - time2_start > enemyTank[0].speed)
		{
			time2_start = time2_end;

			badTankMove(&enemyTank[0]);//敌军移动
			badTankMove(&enemyTank[1]);
			badTankMove(&enemyTank[2]);

			badTankfire(&enemyTank[0], &enemyBullet[0]);//敌军开火
			enemyBulletMove(&enemyBullet[0]);//敌军子弹移动

			badTankfire(&enemyTank[1], &enemyBullet[1]);
			enemyBulletMove(&enemyBullet[1]);

			badTankfire(&enemyTank[2], &enemyBullet[2]);
			enemyBulletMove(&enemyBullet[2]);

		}
	}
}

int main() {
	WelcomeScreen();//游戏选项，主菜单
	system("pause");
	return 0;
}