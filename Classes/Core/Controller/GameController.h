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
USING_NS_CC;
class GameController : public Layer   //��Ϸ������
{
	
public:
//����
	//������
	ButtonLayer*button;
	//
	//����
	TMXTiledMap * _tileMap;
	Hero * hero1, *hero2;
	Vector<Buff*> BuffVector;    //���Buff���������
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