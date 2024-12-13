#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "cocos2d.h"
#include <fstream>
//#include "ui/CocosGUI.h"

USING_NS_CC;

class Dialog : public Layer
{
public:
    std::string User;//�Ի�������
    LayerColor* Dialog_Layer;//�Ի�͸����
    Label* Dialog_Label;//�Ի�����
    MenuItemImage* Dialog_CloseBotton;
    Menu* Dialog_Menu;//�Ի��˵�

    std::string GetDialogContent(std::string path);

    static Dialog* create(const std::string& Username);

    bool init();//��ʼ������

    bool Dialog::JudgeClickButton(Vec2 clickp, int mapscale);

    //�˳���ť�ص�����
    void onExitButtonClick(Ref* obj);
};

#endif // __DIALOG_H__
