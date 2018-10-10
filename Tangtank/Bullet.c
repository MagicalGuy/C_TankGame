#include"TankGame.h"
#include"Tank.h"
#include"Bullet.h"
#include"Draw.h"

int checkBullet(int x, int y)//检测能不能在此打印子弹
{
	if (gameMap[y][x])
		return 0;
	return 1;
}


void ownBulletMove() {
	for (int i = 0; i < 50; i++) {
		int m = ownBullet[i].CoordX;
		int n = ownBullet[i].CoordY;

		if (m != 0 || n != 0)
			if (gameMap[n][m] == 0)//先擦掉		
				clearBullet(ownBullet);

		switch (ownBullet[i].Direction)
		{
		case 1:ownBullet[i].CoordY--; break;
		case 2:ownBullet[i].CoordY++; break;
		case 3:ownBullet[i].CoordX--; break;
		case 4:ownBullet[i].CoordX++; break;
		}

		//检查是否击中障碍物
		existChange();
		//检查是否击中基地
		baseChange();
		//检查是否击中子弹
		bulletChange();
		//检查是否击中敌方坦克
		badTankChange();

		if (checkBullet(ownBullet[i].CoordX, ownBullet[i].CoordY))
			printBullet();
		else
			ownBullet[i].CoordX = 0, ownBullet[i].CoordY = 0;
	}
}



void enemyBulletMove(Object* badTankBullet) {
	int m = badTankBullet->CoordX;
	int n = badTankBullet->CoordY;

	if (m != 0 || n != 0)
		if (gameMap[n][m] == 0) {//先清除掉	
			clearBadBullet(m, n);
		}

	switch (badTankBullet->Direction)
	{
	case 1:badTankBullet->CoordY--; break;
	case 2:badTankBullet->CoordY++; break;
	case 3:badTankBullet->CoordX--; break;
	case 4:badTankBullet->CoordX++; break;
	}

	//检查是否击中障碍物
	existChange();

	//检查是否击中基地
	baseChange();

	//检查是否击中子弹
	bulletChange();

	//检查是否击中我的坦克
	ownTankChange();

	if (badTankBullet->CoordX != 0 && badTankBullet->CoordY != 0) {
		if (checkBullet(badTankBullet->CoordX, badTankBullet->CoordY))
			printBadBullet(badTankBullet);
		else
			badTankBullet->CoordX = 0, badTankBullet->CoordY = 0;
	}
}


//监测子弹碰撞的改变
void bulletChange() {
	for (int i = 0; i < 50; i++) {
		int m = ownBullet[i].CoordX;
		int n = ownBullet[i].CoordY;

		for (int i = 0; i < 3; i++) {//我的坦克子弹和敌人坦克子弹的碰撞

			if (enemyBullet[i].CoordX == m && m != 0 && enemyBullet[i].CoordY == n && n != 0) {
				clearBullet(&ownBullet[i]);//删除我坦克的子弹
				ownBullet[i].CoordX = 0;
				ownBullet[i].CoordY = 0;

				clearBadBullet(enemyBullet[i].CoordX, enemyBullet[i].CoordY);//删除敌方坦克的子弹
				enemyBullet[i].CoordX = 0;
				enemyBullet[i].CoordY = 0;
			}
		}
	}
}