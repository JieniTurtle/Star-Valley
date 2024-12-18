#ifndef __WOOD_H__
#define __WOOD_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#define ScaleFactor 2  //�������ӣ���ͼ��2
// ľͷ��
class Wood : public cocos2d::Scene {
public:
    bool iswood;//�Ƿ���ľͷ
    int woodnum;//ľͷ����
    ui::CheckBox* woodcheckbox;//���Ӹ�ѡ��
    Vec2 mapPosition;//��ͼλ��
    int maplength;//��ͼ����
    int mapwidth;//��ͼ���
    Size visibleSize;//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�


    int mapWidth;  // �����ש����
    int mapHeight; // �����ש����
    int tileWidth; // ������ש�����ؿ��
    int tileHeight; // ������ש�����ظ߶�
    //
    virtual bool init(TMXTiledMap* map);
    void setwoodcheckbox();//����ľͷ��ѡ�� 
    static Wood* create(TMXTiledMap* map);
    //void wheatListenerMouse(TMXTiledMap* map);//���ؼ�������
    void showwoodnum();//��Ļ��ʾľͷ����
};
#endif
#pragma once
