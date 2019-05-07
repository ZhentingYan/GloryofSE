#pragma once
//����Ϸ�м��ص�ͼ
//������ͼ
//����Ӣ�ۣ��ڻҺ�Ұ��
//��SelectHero�����л���ѡ��Ӣ�۵Ľ��棬   �û����ĳ��Ӣ�ۣ�ͨ��һ���ص�����������һ��hero_role������
//Ȼ���������������ж�   ���ݲ�ͬ�������Ӣ��

#include"cocos2d.h"
//#include"Scene/SelectHeroScene.h"
#include"Core/Sprite/Hero.h"
#include"Core/Sprite/Buff.h"
#include"Core/Sprite/CannonFodder .h"
#include"Core/Sprite/Skill.h"
USING_NS_CC;
#define GameMapNodeBatchTagSkill				   902  
#define GameMapNodeBatchTagEnemy					903

//���似�ܵ��ٶ�
#define GameMapSkillVelocity						300
class GameMap: public Layer
{
public:
	//����
	TMXTiledMap * _tileMap;
	Hero * hero1, *hero2;
	Vector<Buff*> BuffVector;    //���Buff���������
	Vector<CannonFodder*>CannonFodderVector;  //����ڻҶ��������
	Vec2 mouse_up;      //����뿪����
	Vec2 mouse_down;    //����������
	bool ismousedown;
	Vec2 repair; //����������
	DrawNode* drawNode;
//����
	static GameMap* createScene();
	virtual bool init();
	

	void setHero();//hero_role HeroRole);  //����Ӣ��
	void createBuff();  //����Buff
	void createCannonFodder();  //�����ڻ�
	void onEnter();//   ��дonEnter ����
	void onExit();   //��дonExit ����

	void updateGame(float dt);  //ˢ�º���



	//����Ϊ�ƶ����麯��
	bool onTouchBegan(Touch *touch, Event*unused_event);
	void onTouchEnded(Touch *touch, Event*unused_event);
	void onTouchMoved(Touch *touch, Event*unused_event);
	bool moveHero(Vec2 targetPosition);
	CREATE_FUNC(GameMap);
};