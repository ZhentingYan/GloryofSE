#pragma once
#include"cocos2d.h"
USING_NS_CC;
class fieldMonster : public Sprite
{
public:
	ProgressTimer * blood;   //Ѫ��
	int bloodNum;  //Ѫ��
	//void attack();
	Vec2 initPos;
	virtual bool init();   //  Ұ���ܵĿ���

	void initBloodBar();

};