#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "animals.h"
#include"MainCharacter.h"
#include "ui/CocosGUI.h"
#include "Seeds.h"
#include "Gloves.h"
#include "Wheat.h"
#include "NPC.h"
USING_NS_CC;

enum Mouse {
    notTaken,
    TakenByNPC
};

class GameScene : public cocos2d::Scene
{
public:
    //����ָʾ��걻˭ռ�ݣ�1����NPCռ��
    enum Mouse MouseStatus;
    //��ͼ����
    static int mapscale;

    static Scene* createScene(std::string s);
    static GameScene* create(std::string s);
    bool init();
    void CheckboxOnlyone();//ֻ��ѡ��һ����ѡ��
  
    MainCharacter* character;//����
    int mapWidth;   // �����ש����
    int mapHeight; // �����ש����
    int tileWidth;  // ������ש�����ؿ��
    int tileHeight;  // ������ש�����ظ߶�

    NPC* NPC_Willy;
    NPC* NPC_Gus;
    NPC* NPC_Jodi;
    NPC* NPC_Harvey;

    NPC* initNPC(std::string NPC_Name, std::vector<Vec2>& NPC_Path, TMXTiledMap* NPC_Map);

    void addMouseListener();
    void Mouseupdate(float delta);
    void onMouseDown(cocos2d::Event* event);
    void MouseClickNPC(NPC* npc);
    Tools* tools ;//���빤��   
    Seeds* seeds;//��������   
    Wheat* wheat ;//����С��   
    Gloves* gloves ;//��������
    std::string scene_name_;

    int clickNPCButtons();
};

#endif // __HELLOWORLD_SCENE_H__
#pragma once
