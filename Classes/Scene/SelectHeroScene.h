#pragma once
//������ѡ��Ӣ�۵�ʱ�򱳾�����������ҫ��Ӣ��ר��������
#include"cocos2d.h"
#include"SimpleAudioEngine.h"
#include"Core/Controller/GameScene.h"
#include"Core/Controller/GameController.h"
USING_NS_CC;



typedef enum {
	daji = 0,    //槼�
	houyi = 1,     //����
	yase = 2,   //��ɪ

}hero_role;


//hero_role HeroRole=daji; //����һ��ȫ�ֱ���  ���ҳ�ʼ��
//extern hero_role HeroRole; 

class SelectHeroScene :public Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	//void menuItemStartCallback(cocos2d::Ref*pSender);
	//void menuItem2Callback(cocos2d::Ref*pSender);

	void DajiCallback(Ref *pSender);

    // implement the "static create()" method manually



	CREATE_FUNC(SelectHeroScene);


};