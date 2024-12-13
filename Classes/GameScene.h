#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include"MainCharacter.h"
#include "ui/CocosGUI.h"
#include "Seeds.h"
#include "Gloves.h"
#include "Wheat.h"
USING_NS_CC;
class GameScene : public cocos2d::Scene
{
public:
    static Scene* createScene(std::string s);
    static GameScene* create(std::string s);
    bool init();
    void CheckboxOnlyone();//ֻ��ѡ��һ����ѡ��
  
    MainCharacter* character;//����
    int mapWidth;   // �����ש����
    int mapHeight; // �����ש����
    int tileWidth;  // ������ש�����ؿ��
    int tileHeight;  // ������ש�����ظ߶�

    Tools* tools ;//���빤��   
    Seeds* seeds;//��������   
    Wheat* wheat ;//����С��   
    Gloves* gloves ;//��������
    std::string scene_name_;
};

#endif // __HELLOWORLD_SCENE_H__
#pragma once
