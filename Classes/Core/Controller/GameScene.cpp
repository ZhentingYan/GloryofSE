#include"Core/Controller/GameScene.h"
Scene* GameScene::createScene()

{

	auto controller =GameController::createScene();//�������Ʋ�
	auto scene = Scene::create();//���쳡��
	//controller->map = gamemap;  //����Ϸ�������е�GameSceneָ��ָ��gamescene   ע�������಻�ܻ���ָ
	scene->addChild(controller);
	return scene;
}
