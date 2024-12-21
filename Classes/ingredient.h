#ifndef ingredients_h
#define ingredients_h
#include "global.h"
#include"MainCharacter.h"
#include "cocos2d.h"
USING_NS_CC;
class Iingredients {
public:
    std::string ingredientsName;
    int *quantity;
    std::string imageFile;

    Iingredients(std::string ingreName, int *itemQuantity, std::string itemImageFile)
        : ingredientsName(ingreName), quantity(itemQuantity), imageFile(itemImageFile) {}

    void addQuantity(int qty) {
        *quantity += qty;
    }

    bool consumeQuantity(int qty) {
        if (*quantity >= qty) {
            *quantity -= qty;
            return true;
        }
        return false;
    }
};

// CookLayer �࣬չʾ��Ʒ�ͺϳɰ�ť
class CookLayer : public cocos2d::Layer {
public:
    CookLayer() : selectedItem(nullptr) {}

    //��ʼ��
    bool init();

    // ������Ʒ
    void createItems();

    //�����˵�
    void createMenu();

    //����ϳ�
    void onCombineButtonClicked1(Iingredients& ingredient);
    void onCombineButtonClicked2(Iingredients& ingredient);

    //����UI
    void updateUI();

    //����ʵ��
    static CookLayer* create();

    // ��ʼ�����̼�����
    void initKeyboardListener();

    // �л��˵���ʾ������
    void toggleMenuVisibility();

    EventListenerKeyboard* listener;
private:
    std::vector<Iingredients> ingredients;
    Iingredients* selectedItem;
    bool menuVisible;  // ��¼�˵�����ʾ״̬
};


#endif 
#pragma once
