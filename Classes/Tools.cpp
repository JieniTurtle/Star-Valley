#include "Tools.h"
#include "SimpleAudioEngine.h"

 bool Tools:: init() {
     sethoecheckbox();//���ó�ͷ��ѡ��
     ishoe = 0;
     return true;
}

 void  Tools::sethoecheckbox() {
     auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

     hoecheckbox = ui::CheckBox::create("chutou.png", "chutou2.png");
     hoecheckbox->setPosition(Vec2(visibleSize.width / 8, visibleSize.height / 4)); // ����λ��
   
     // ����¼�������
     hoecheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
         switch (type) {
             case ui::CheckBox::EventType::SELECTED:
                 ishoe = 1;
                 break;
             case ui::CheckBox::EventType::UNSELECTED:
                 ishoe = 0;
                 break;
             default:
                 break;
         }
         });
     this->addChild(hoecheckbox);
 }