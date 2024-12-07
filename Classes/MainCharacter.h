
#ifndef __MAINCHARACTER_H__
#define __MAINCHARACTER_H__

#include "cocos2d.h"
#include "Tools.h"
USING_NS_CC;

class MainCharacter : public Sprite {
public:
    static MainCharacter* create(const std::string& filename); // ���ش�������
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//wasd�ĸ����ƶ��¼�
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//wasd�ĸ����ƶ��¼�
    void addKeyboardListener();//��Ӽ��̼����¼�
    void update(float delta);
    //�����ͼָ��
    void setMap(TMXTiledMap* map) {
        mainmap = map;
    }

    std::string staticnext="characterdown2.png";//��ֹ����ͼƬ
    virtual bool init(const std::string& filename);
    int movementkeys[4];//����wasd�ĸ���Ϊ
    Animation* walkAnimationdown; // ��·����
    Animation* walkAnimationup;
    Animation* walkAnimationleft;
    Animation* walkAnimationright;
    TMXTiledMap* mainmap;//��ͼָ��
};

#endif 
#pragma once
