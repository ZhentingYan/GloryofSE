#pragma once
#include"cocos2d.h"
USING_NS_CC;
class fieldMonster : public Sprite
{
public:
	Sprite * blood;   //Ѫ��
	int bloodNum;  //Ѫ��
	//void attack();
	ValueMap spawnPoint;
	virtual bool init();   //  Ӣ�۵��ܵĿ���

};