//#pragma once
//#include"cocos2d.h"
//#include"Core/Sprite/Hero.h"
//#include"Core/Sprite/Buff.h"
//#include"Core/Sprite/CannonFodder .h"
//
//#include<assert.h>
//USING_NS_CC;
//typedef enum
//{
//	Hero = 0,  //Ӣ��
//	Buff=1,    //Ұ��
//	CannonFodder=2 //�ڻ�
//	
//}sprite_type;   //��������
//
//class CreateSprite :public Sprite
//{
//private:
//	int blood;   //Ѫ��
//
//public:
//	//static cocos2d::Sprite* createScene();
//	CreateSprite*CreateSpriteTpye(sprite_type s_type)   //
//	{
//		switch (s_type)
//		{
//			case Hero:
//				{
//				auto sprite=Hero::create();
//				break;
//				}
//			case Buff:
//				{
//				auto sprite =Buff::create();
//				break;
//
//				}
//			case CannonFodder:
//				{
//				auto sprite = CannonFodder::create();
//				break;
//
//				}
//		}
//
//
//
//	}
//
//};
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//class daji :public Hero
//{
//public:
//	static cocos2d::Sprite* createScene();
//	virtual bool init();   //  Ӣ�۵��ܵĿ���
//	virtual bool createHero();  //����Ӣ�۵ĺ�����ÿ��Ӣ���ڴ�����ʱ�������д
//
//
//	CREATE_FUNC(Hero);
//
//};
//
//
//
//Sprite* daji::createScene()
//{
//	return daji::create();
//}