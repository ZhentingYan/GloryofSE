#pragma once

#include"cocos2d.h"

#include"Scene/SelectHeroScene.h"
//��������ͷ�ļ�
#include"Scene/ButtonLayer.h"

//����������ͷ�ļ�
#include"Core/Sprite/Hero.h"
#include"Core/Sprite/Buff.h"
#include"Core/Sprite/CannonFodder .h"
#include"Core/Sprite/Tower.h"
#include"Core/Sprite/fieldMonster.h"
USING_NS_CC;

enum{
		up = 6,
		down = 4,
		lefts = 5,//
		rigth = 7,//
		rigth_up = 3,//
		rigth_down = 0,//
		left_down = 1,//
		left_up = 2//
};
class GameController : public Layer   //��Ϸ������
{
	
public:
//����
	//������
	ButtonLayer*button;
	//
	//����
	TMXTiledMap * _tileMap;
	TMXLayer * _collidable;
	Hero * hero1, *hero2;
	Vector<Buff*> BuffVector;    //���Buff���������
	fieldMonster* monster1;
    fieldMonster* monster2;
	Vector<CannonFodder*>CannonFodderVector;  //����ڻҶ��������
	Vector<Tower*>TowerVector;      //�����ָ�������
	Vec2 mouse_up;      //����뿪����
	Vec2 mouse_down;    //����������
	bool ismousedown;
	char *bigSkillFormat;    //����·��
	char *mediumSkillFormat;  //����·��
	char *smallSkillFormat;   //С��·��
	int bigSkillNum;    //���ж�������Ƭ��
	int mediumSkillNum;    //���ж�������Ƭ��
	int smallSkillNum;    //���ж�������Ƭ��
//����
	ValueMap player1_initPos;
	void setViewpointCenter(Vec2 position);
	Vec2 tileCoordFromPosition(Vec2 pos);
	int getNowPointDir(Vec2 newpoint);
	void setPlayerPosition(Vec2 position);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    static GameController* createScene(); //��������
	virtual bool init(); //��ʼ�����Ʋ�

	void onEnter();//   ��дonEnter ����
	void onExit();   //��дonExit ����


	void createHero();//hero_role HeroRole);  //����Ӣ��
	void createBuff();  //����Buff
	void createCannonFodder();  //�����ڻ�
	void createTower();    //������

	void updateGame(float dt);  //ˢ�º���

	void CannonFodderMoving();   //�ڻ��ƶ�����
	void backHome();  //�س�



	bool isHeroDeath();           //�ж�Ӣ���Ƿ�����
	bool isCannonFodderDeath(); //�ж��ڻ��Ƿ�����
	bool isBuffDeath();         //�ж�Buff�Ƿ�����
	bool isHeroResurrection();//Ӣ�۸����
	bool isGameOver(); //�ж���Ϸ�Ƿ����
	bool isTowerPushed();   //�ж����Ƿ���
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameController);    

};