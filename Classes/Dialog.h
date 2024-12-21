 #ifndef __DIALOG_H__
#define __DIALOG_H__

#include "cocos2d.h"
#include <fstream>
#include "ui/CocosGUI.h"

USING_NS_CC;

class Dialog : public Scene
{
public:
    //����
    ~Dialog()
    {
        button_continue->release();
        button_close->release();
        content->release();
    }

    //����Ƿ������˳���ť
    int ChangeToClose;
    int TaskStatus;
    std::string User;//�Ի�������

    LayerColor* BackLayer;//�Ի�͸����
    Label* content;//�Ի�����
    ui::Button* button_continue;//�����Ի���ť
    ui::Button* button_close;//�˳��Ի���ť

    int contentIndex;
    std::vector<std::string> contentstore;//�洢�Ի�����

    std::string GetDialogContent(std::string path);

    static Dialog* create(std::string& Username);

    bool init();//��ʼ������

    void onContinueButtonClick(Ref* obj);//���¼�����ť
    void onEndButtonClick(Ref* obj);//���½�����ť
};

#endif // __DIALOG_H__
