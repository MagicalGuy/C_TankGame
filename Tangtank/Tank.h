#pragma once
#include"TankGame.h"

void ownTankChange(); //监测自己坦克的改变
void badTankChange();   //监测敌人坦克的改变
void tankMove();//自己的坦克移动
void badTankMove(Object* badTank);//敌人坦克移动
void ownTankfire();//自己坦克开火
void badTankfire(Object* badTank, Object* badTankBullet);//敌人坦克开火