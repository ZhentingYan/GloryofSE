#pragma once
#include"cocos2d.h"
#include"Scene/SelectHeroScene.h"
#include"Scene/GameScene.h"
#include"Core/Sprite/Hero.h"
USING_NS_CC;
class GameController : public Scene    //��Ϸ������
{
public:
//����
	Sprite * hero1, *hero2;
	Layer *map;


//����




	virtual bool init();
	void createHero();//hero_role HeroRole);  //����Ӣ��
	static cocos2d::Scene* createScene();


	//�ж�Ӣ���Ƿ�����
	//�ж���Ϸ�Ƿ����
	//�ж�С���Ƿ�����
	//�ж�Buff�Ƿ�����
	//Ӣ�۸����
	

	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameController);

};