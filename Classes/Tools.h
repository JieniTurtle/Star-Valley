#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

// ������
class Tools: public cocos2d::Layer{
public:
    bool ishoe;//�Ƿ��ó�ͷ

    ui::CheckBox* hoecheckbox;//��ͷ��ѡ��
    virtual bool init();
    void sethoecheckbox();//���ó�ͷ��ѡ��
    CREATE_FUNC(Tools);
};


#endif
