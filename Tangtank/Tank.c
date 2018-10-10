#include"Tank.h"
#include"Draw.h"
#include"windows.h"
#include"conio.h"
#include"Utils.h"

#define KEYDOWN(vk_code)((GetAsyncKeyState(vk_code)&0x8000)?1:0)
#define KEYUP(vk_code)((GetAsyncKeyState(vk_code)&0x8000)?0:1)

//监测自己坦克状态的改变
void ownTankChange() {

	int x = ownTank.CoordX;
	int y = ownTank.CoordY;

	switch (ownTank.Direction)
	{
	case 1:    //当我的坦克方向向上时
	{
		for (int i = 0; i < 3; i++) {
			int m1 = enemyBullet[i].CoordX;
			int n1 = enemyBullet[i].CoordY;

			if (x == m1 && (y - 1) == n1 || (x - 1) == m1&&y == n1 || x == m1&&y == n1 ||
				(x + 1) == m1&&y == n1 || (x - 1) == m1 && (y + 1) == n1 || (x + 1) == m1 && (y + 1) == n1)
				enemyBullet[i].CoordX = 0,
				enemyBullet[i].CoordY = 0,
				ownTank.HealthPoint--,
				printScoreboard(),
				checkGame(),
				turnUp(&ownTank);
			//坦克子弹消失，生命值减1，检查游戏是否结束，若没结束初始化方向
		}

	}break;
	case 2:
	{
		for (int i = 0; i < 3; i++) {
			int m1 = enemyBullet[i].CoordX;
			int n1 = enemyBullet[i].CoordY;
			if (x == m1 && (y + 1) == n1 || (x - 1) == m1&&y == n1 || x == m1&&y == n1 || (x + 1) == m1&&y == n1 ||
				(x - 1) == m1 && (y - 1) == n1 || (x + 1) == m1 && (y - 1) == n1)
				enemyBullet[i].CoordX = 0,
				enemyBullet[i].CoordY = 0,
				ownTank.HealthPoint--,
				printScoreboard(),
				checkGame(),
				turnUp(&ownTank);
		}

	}break;
	case 3:
	{
		for (int i = 0; i < 3; i++) {
			int m1 = enemyBullet[i].CoordX;
			int n1 = enemyBullet[i].CoordY;
			if (x == m1 && (y - 1) == n1 || (x - 1) == m1&&y == n1 || x == m1&&y == n1 ||
				(x + 1) == m1 && (y - 1) == n1 || x == m1 && (y + 1) == n1 || (x + 1) == m1 && (y + 1) == n1)
				enemyBullet[i].CoordX = 0, enemyBullet[i].CoordY = 0, ownTank.HealthPoint--, printScoreboard(), checkGame(), turnUp(&ownTank);
		}
	}break;
	case 4:
	{
		for (int i = 0; i < 3; i++) {
			int m1 = enemyBullet[i].CoordX;
			int n1 = enemyBullet[i].CoordY;
			if (x == m1 && (y - 1) == n1 || (x - 1) == m1 && (y - 1) == n1 || x == m1&&y == n1 ||
				(x - 1) == m1 && (y + 1) == n1 || x == m1 && (y + 1) == n1 || (x + 1) == m1&&y == n1)
				enemyBullet[i].CoordX = 0,
				enemyBullet[i].CoordY = 0,
				ownTank.HealthPoint--,
				printScoreboard(),
				checkGame(),
				turnUp(&ownTank);
		}
	}break;

	}
}


//监测敌人坦克状态的改变
void badTankChange()
{

	for (int i = 0; i < 50; i++) {
		int m = ownBullet[i].CoordX;
		int n = ownBullet[i].CoordY;

		for (int j = 0; j < 3; j++) {

			int x1 = enemyTank[j].CoordX;
			int y1 = enemyTank[j].CoordY;

			switch (enemyTank[j].Direction)
			{
			case 1:
			{//以坦克中心点开始判断六个点是否与子弹坐标重合
				if (x1 == m && (y1 - 1) == n || (x1 - 1) == m && y1 == n || x1 == m&&y1 == n ||
					(x1 + 1) == m && y1 == n || (x1 - 1) == m && (y1 + 1) == n || (x1 + 1) == m && (y1 + 1) == n) {
					//如果我的坦克子弹打到敌人
					clearTank(&enemyTank[j]); //清除敌军坦克
					enemyTank[j].CoordX = 2 + j * 10;//敌军坦克回到初始位置
					enemyTank[j].CoordY = 2;
					ownBullet[i].CoordX = 0;//我的坦克子弹消失
					ownBullet[i].CoordY = 0;
					enemyCount--; //敌人坦克数量减1
					score = score + 100;//分数加100
					printScoreboard();
					checkGame();//检查游戏是否胜利
				}

			}break;
			case 2:
			{
				if (x1 == m && (y1 + 1) == n || (x1 - 1) == m&&y1 == n || x1 == m&&y1 == n ||
					(x1 + 1) == m&&y1 == n || (x1 - 1) == m && (y1 - 1) == n || (x1 + 1) == m && (y1 - 1) == n) {
					clearTank(&enemyTank[j]);
					enemyTank[j].CoordX = 2 + j * 10;
					enemyTank[j].CoordY = 2;
					ownBullet[i].CoordX = 0;
					ownBullet[i].CoordY = 0;
					enemyCount--;
					score = score + 100;
					printScoreboard();
					checkGame();
				}

			}break;
			case 3:
			{
				if (x1 == m && (y1 - 1) == n || (x1 - 1) == m&&y1 == n || x1 == m&&y1 == n ||
					(x1 + 1) == m && (y1 - 1) == n || x1 == m && (y1 + 1) == n || (x1 + 1) == m && (y1 + 1) == n) {
					clearTank(&enemyTank[j]);
					enemyTank[j].CoordX = 2 + j * 10;
					enemyTank[j].CoordY = 2;
					ownBullet[i].CoordX = 0;
					ownBullet[i].CoordY = 0;
					enemyCount--;
					score = score + 100;
					printScoreboard();
					checkGame();
				}

			}break;
			case 4:
			{
				if (x1 == m && (y1 - 1) == n || (x1 - 1) == m && (y1 - 1) == n || x1 == m&&y1 == n ||
					(x1 - 1) == m && (y1 + 1) == n || x1 == m && (y1 + 1) == n || (x1 + 1) == m&&y1 == n) {
					clearTank(&enemyTank[j]);
					enemyTank[j].CoordX = 2 + j * 10;
					enemyTank[j].CoordY = 2;
					ownBullet[i].CoordX = 0;
					ownBullet[i].CoordY = 0;
					enemyCount--;
					score = score + 100;
					printScoreboard();
					checkGame();
				}
			}break;
			}
		}
	}
}


void ownTankfire() {
	for (int i = 0; i < 50; i++) {
		int m = ownBullet[i].CoordX;
		int n = ownBullet[i].CoordY;

		if (m == 0 && n == 0)//第几个子弹没有,则重新生成子弹
		{
			switch (ownTank.Direction)
			{
			case 1:
			{
				ownBullet[i].CoordX = ownTank.CoordX;
				ownBullet[i].CoordY = ownTank.CoordY - 2;
				ownBullet[i].Direction = 1;
			}break;
			case 2:
			{
				ownBullet[i].CoordX = ownTank.CoordX;;
				ownBullet[i].CoordY = ownTank.CoordY + 2;
				ownBullet[i].Direction = 2;
			}break;
			case 3:
			{
				ownBullet[i].CoordX = ownTank.CoordX - 2;
				ownBullet[i].CoordY = ownTank.CoordY;
				ownBullet[i].Direction = 3;
			}break;
			case 4:
			{
				ownBullet[i].CoordX = ownTank.CoordX + 2;
				ownBullet[i].CoordY = ownTank.CoordY;
				ownBullet[i].Direction = 4;
			}break;
			}

			break;
		}

	}
}


void badTankfire(Object* badTank, Object* badTankBullet) {

	int m = badTankBullet->CoordX;
	int n = badTankBullet->CoordY;

	if (m == 0 && n == 0)//没有坦克的子弹,则重新发射子弹
	{
		switch (badTank->Direction)
		{
		case 1:
		{
			badTankBullet->CoordX = badTank->CoordX;
			badTankBullet->CoordY = badTank->CoordY - 2;
			badTankBullet->Direction = 1;
		}break;
		case 2:
		{
			badTankBullet->CoordX = badTank->CoordX;;
			badTankBullet->CoordY = badTank->CoordY + 2;
			badTankBullet->Direction = 2;
		}break;
		case 3:
		{
			badTankBullet->CoordX = badTank->CoordX - 2;
			badTankBullet->CoordY = badTank->CoordY;
			badTankBullet->Direction = 3;
		}break;
		case 4:
		{
			badTankBullet->CoordX = badTank->CoordX + 2;
			badTankBullet->CoordY = badTank->CoordY;
			badTankBullet->Direction = 4;
		}break;
		}
	}
}


void tankMove() {

	if (KEYDOWN('f') || KEYDOWN('F'))
	{
		ownTankfire();
		return;
	}
	if (KEYDOWN('W') || KEYDOWN('w'))
	{
		turnUp(&ownTank);
		return;
	}
	if (KEYDOWN('s') || KEYDOWN('S'))
	{
		turnDown(&ownTank);
		return;
	}
	if (KEYDOWN('a') || KEYDOWN('A'))
	{
		turnLeft(&ownTank);
		return;
	}
	if (KEYDOWN('d') || KEYDOWN('D'))
	{
		turnRight(&ownTank);
		return;
	}
	if (KEYDOWN('p') || KEYDOWN('P'))
	{
		stopGame();
		return;
	}
	if (KEYDOWN('o') || KEYDOWN('O'))
	{
		exit(0);
		return;
	}
}


void badTankMove(Object* badTank) {

	int direction = (rand() % 4 + 1);
	switch (direction)
	{
	case 1:turnUp(badTank); break;
	case 2:turnDown(badTank); break;
	case 3:turnLeft(badTank); break;
	case 4:turnRight(badTank); break;
	}
}
