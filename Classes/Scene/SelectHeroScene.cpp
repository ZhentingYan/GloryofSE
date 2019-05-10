#include"Scene/SelectHeroScene.h"
hero_role HeroRole = moonGoddess; //����һ��ȫ�ֱ���  ���ҳ�ʼ��
using namespace CocosDenshion;

Scene*  SelectHeroScene::createScene()
{
	return  SelectHeroScene::create();
}
void  SelectHeroScene::onEnter()
{
	Scene::onEnter();
	log("MainMenu onEnter");
}

void  SelectHeroScene::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	log("MainMenu onEnterTransitionDidFinish");
	//����
	//if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
	//	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Lose1.mp3", true);
	//}
}

void  SelectHeroScene::onExit()
{
	Scene::onExit();
	log("MainMenu onExit");
}

void  SelectHeroScene::onExitTransitionDidStart()
{
	Scene::onExitTransitionDidStart();
	log("MainMenu onExitTransitionDidStart");
}

void  SelectHeroScene::cleanup()
{
	Scene::cleanup();
	log("MainMenu cleanup");
	//ֹͣ
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/Lose.mp3");
}


bool  SelectHeroScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Lose1.mp3", true);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��ӱ���
	Sprite *bg = Sprite::create("SelectHeroground.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);

	//��Ӳ˵�
	/*MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);*/


	//���ÿ�ʼ�����ò˵�
	MenuItemFont*moonGoddessItem = MenuItemFont::create("moonGoddess", CC_CALLBACK_1( SelectHeroScene::moonGoddessCallback, this));
	moonGoddessItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	

	//���˵���ŵ��˵�������
	Menu *mn = Menu::create(moonGoddessItem,NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	return true;
}


void  SelectHeroScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}
void  SelectHeroScene::moonGoddessCallback(Ref *pSender)
{
	HeroRole =moonGoddess;;   //��ȫ�ֱ�����ֵ
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}