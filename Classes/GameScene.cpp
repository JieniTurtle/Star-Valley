

#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//���д����ȡ��ǰ��Ϸ��ͼ���ڵ�ԭ������

   
   
    // ��ӳ�ʼ����ͼ
    auto map = TMXTiledMap::create("Farm_Ranching.tmx");
    if (!map) {
        problemLoading("'Farm_FourCorners.tmx'");
        return false;
    }
    if (!map) {
        CCLOG("map fail");
        return false;
    }
    this->addChild(map, 0);
    map->setScale(2);//��ͼ��������
 
    // ��ȡ��ͼ�Ĵ�С
    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width*2; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height*2; // ������ש�����ظ߶�
    map->setAnchorPoint(Vec2(0.5,0.5));
    map->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

 
    //��������
    character = MainCharacter::create("characterstatic.png");
    character->setScale(0.5);
    character->setPosition(visibleSize.width / 2, visibleSize.height / 2); // ��ʼλ��
    this->addChild(character);
    character->setMap(map);//�����ͼ

    auto tools = Tools::create();//���빤��
    this->addChild(tools, 1);
}



