#include"Scene/GameScene.h"

Scene* GameScene::createScene()
{
	return GameScene::create();
}


//���򽻻�
bool GameScene::init()
{
	auto map = GameMap::create();
	addChild(map);
	return true;

}
