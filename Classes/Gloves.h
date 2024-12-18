#ifndef __GLOVES_H__
#define __GLOVES_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Wheat.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
#define MaturePlantID 5548//����ͼ��id
#define AbleHoeID 809  //�ɸ�����ͼ��id
// ������
class Gloves : public cocos2d::Layer {
public:
    bool isgloves;//�Ƿ������
    ui::CheckBox* glovescheckbox;//���׸�ѡ��
    Vec2 mapPosition;//��ͼλ��
    int maplength;//��ͼ����
    int mapwidth;//��ͼ���
    Size visibleSize;//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    int mapWidth;  // �����ש����
    int mapHeight; // �����ש����
    int tileWidth; // ������ש�����ؿ��
    int tileHeight; // ������ש�����ظ߶�
    //
    virtual bool init(TMXTiledMap* map,int& wheatnum);
    void setglovescheckbox();//�������׸�ѡ��

    static Gloves* create(TMXTiledMap* map, int& wheatnum);
    void glovesListenerMouse(TMXTiledMap* map, int& wheatnum);//���׼�������

};


#endif
#pragma once
