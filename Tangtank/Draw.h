#pragma once
void WelcomeScreen();
void printBorder();
void printInstru();

void printBase();//打印基地
void printExist();//打印地图所有物
void printTank(Object* tank);//打印坦克
void clearTank(Object* tank);//清除坦克
void printBullet();//打印自己的子弹
void printBadBullet(Object* badBullet);//打印敌人子弹
void clearBullet(Object* object);//清除自己子弹
void clearBadBullet(int x, int y);//清除敌人坦克的子弹
void printScoreboard();