#pragma once
#include"TankGame.h"

int checkBullet(int x, int y);//检测某位置能否打印子弹
void ownBulletMove();  //自己子弹自动移动
void enemyBulletMove(Object* badTankBullet);//敌人坦克子弹自由移动
void bulletChange();//监测子弹的改变