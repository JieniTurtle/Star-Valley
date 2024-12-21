#include "Dialog.h"

Dialog* Dialog::create(std::string& Username)
{
    Dialog* dialog = new Dialog();
    if (dialog) {
        dialog->User = Username;
        if (dialog && dialog->init()) {
            dialog->autorelease();
            return dialog;
        }
    }
    CC_SAFE_DELETE(dialog);
    return nullptr;
}

bool Dialog::init() {
    if (!Layer::create()) { return false; }

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    // ����һ����ɫ�İ�͸��������ֻռ����Ļ���°벿��
    BackLayer = LayerColor::create(Color4B(0, 0, 0, 180), visibleSize.width, visibleSize.height / 3);
    BackLayer->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    BackLayer->setPosition(Vec2(0, 0));  // ����������Ļ���°벿��
    this->addChild(BackLayer);

    //¼��Ի��ı�
    contentIndex = 0;
    contentstore.push_back(GetDialogContent("NPC/" + User + "/DialogContent_Normal.txt"));
    contentstore.push_back(GetDialogContent("NPC/" + User + "/DialogContent_TaskGiving.txt"));
    contentstore.push_back(GetDialogContent("NPC/" + User + "/DialogContent_TaskInProgress.txt"));
    contentstore.push_back(GetDialogContent("NPC/" + User + "/DialogContent_TaskCompleted.txt"));

    //����������ť
    button_continue = ui::Button::create("NPC/" + User + "/DialogContinue1.png", "NPC/" + User + "/DialogContinue2.png");
    button_continue->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    button_continue->setPosition(visibleSize / 8);
    button_continue->addClickEventListener(CC_CALLBACK_1(Dialog::onContinueButtonClick, this));
    this->addChild(button_continue);
    button_continue->setTitleText("continue");  // ���ð�ť����ʾ���ı�
    button_continue->setTitleFontSize(24);      // ���������С
    button_continue->setTitleColor(Color3B::WHITE);  // ����������ɫ

    //�����˳���ť
    button_close = ui::Button::create("NPC/" + User + "/DialogEnd1.png", "NPC/" + User + "/DialogEnd2.png");
    button_close->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    Vec2 button_close_position;
    button_close_position.x = visibleSize.width * 7 / 8;
    button_close_position.y = visibleSize.height / 8;
    button_close->setPosition(button_close_position);
    button_close->addClickEventListener(CC_CALLBACK_1(Dialog::onEndButtonClick, this));
    this->addChild(button_close);
    button_close->setTitleText("end");  // ���ð�ť����ʾ���ı�
    button_close->setTitleFontSize(24);      // ���������С
    button_close->setTitleColor(Color3B::WHITE);  // ����������ɫ

    // ������Ϣ��ǩ
    content = Label::createWithSystemFont("HW", "arial", 24);
    content->setString(contentstore[contentIndex]);
    content->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    content->setPosition(visibleSize.width / 2, visibleSize.height / 4);
    //�����ı�ˮƽ��������ߣ���ֱ�������ϱ���ʾ
    content->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
    content->setDimensions(visibleSize.width * 0.8, 0);
    this->addChild(content);

    ChangeToClose = 0;
    TaskStatus = 0;
    this->retain();
    return true;
}

std::string Dialog::GetDialogContent(std::string path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf(); // ���ļ����ݶ�ȡ������
    return buffer.str();    // �����ļ�����
}

//���������ť
void Dialog::onEndButtonClick(Ref* obj)
{
    button_close->retain();
    ChangeToClose = 1;
    if (contentIndex == 0) {
        this->removeFromParent();
    }
    else if (contentIndex == 1) {
        contentIndex = 2;
        content->setString(contentstore[contentIndex]);
        this->addChild(button_continue);
        this->removeFromParent();
    }
    else if (contentIndex == 2) {
        this->removeFromParent();
    }
    else if (contentIndex == 3) {
        this->removeFromParent();
    }
}

//���������ť
void Dialog::onContinueButtonClick(Ref* obj)
{
    button_continue->retain();
    if (contentIndex == 0) {
        contentIndex = 1;
        TaskStatus = 1;
        content->setString(contentstore[contentIndex]);
        this->removeChild(button_continue);
    }
    else if (contentIndex == 2) {
        ChangeToClose = 2;
        contentIndex = 3;
        TaskStatus = 2;
        content->setString(contentstore[contentIndex]);
        this->removeChild(button_continue);
        this->removeFromParent();
    }
}