#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include"MainCharacter.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class GameScene : public cocos2d::Scene
{
public:
    static Scene* createScene();
    virtual bool init();

  
    MainCharacter* character;//����
    int mapWidth;   // �����ש����
    int mapHeight; // �����ש����
    int tileWidth;  // ������ש�����ؿ��
    int tileHeight;  // ������ש�����ظ߶�
    CREATE_FUNC(GameScene);

};

#endif // __HELLOWORLD_SCENE_H__
#pragma once
