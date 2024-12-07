
#ifndef __MAINCHARACTER_H__
#define __MAINCHARACTER_H__

#include "cocos2d.h"

USING_NS_CC;

class MainCharacter : public Sprite {
public:
    static MainCharacter* create(const std::string& filename); // ���ش�������
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//wasd�ĸ����ƶ��¼�
    void addKeyboardListener();//��Ӽ��̼����¼�
    virtual bool init(const std::string& filename);
 
    Animation* walkAnimationdown; // ��·����
    Animation* walkAnimationup;
    Animation* walkAnimationleft;
    Animation* walkAnimationright;
};

#endif 
#pragma once
