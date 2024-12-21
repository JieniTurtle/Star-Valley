#include "Fishing.h"
#include "SimpleAudioEngine.h"

bool Fishing::init(TMXTiledMap* map, MainCharacter* maincharacter) {
    isfishing = 0;
  
    fishingcondition = 0;
    scheduleCounter = 0;
    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    //��ʼ����ǩ�뱳��
    isfishingnow = Label::createWithSystemFont("You are fishing now.\nClick fish pole again to cancel", "Arial", 30);
    isfishingnow->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(isfishingnow,2);
    isfishingnow->setVisible(false);
    //
    isfishingnowtext = Sprite::create("fishingtext.png");
    isfishingnowtext->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(isfishingnowtext, 1);
    isfishingnowtext->setScale(0.9);
    isfishingnowtext->setVisible(false);
    //
    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setfishingcheckbox();//���ø�ѡ��

    fishingListenerMouse(map, maincharacter);
    return true;
}

void  Fishing::setfishingcheckbox() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    //������ͷͼ��
    fishingcheckbox = ui::CheckBox::create("fishing1.png", "fishing2.png");
    fishingcheckbox->setPosition(Vec2(visibleSize.width * 3 / 8, visibleSize.height / 4)); // ����λ��

    //// ����¼�������
    //glovescheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
    //    switch (type) {
    //        case ui::CheckBox::EventType::SELECTED:
    //            isgloves = 1;
    //            break;
    //        case ui::CheckBox::EventType::UNSELECTED:
    //            isgloves = 0;
    //            break;
    //        default:
    //            break;
    //    }
    //    });
    this->addChild(fishingcheckbox);


}
//�������
void  Fishing::fishingprocess(TMXTiledMap* map, MainCharacter* maincharacter) {
    isfishingnow->setVisible(true);
    isfishingnowtext->setVisible(true);
   
  
    std::string updateKey = "update_function_key_" + std::to_string(scheduleCounter++);
    this->schedule([=](float dt) {
        myUpdateFunction(updateKey); // ���ø��º���
        }, 0.02f, updateKey);
    std::string updateKey2 = "update2_function_key_" + std::to_string(scheduleCounter++);
    this->schedule([=](float dt) {
        myUpdateFunction2(map,maincharacter, updateKey2); // ���ø��º���
        }, 0.02f, updateKey2);
    std::string updateKey3 = "update3_function_key_" + std::to_string(scheduleCounter++);
    this->schedule([=](float dt) {
        myUpdateFunction3( updateKey3); // ���ø��º���
        }, 0.02f, updateKey3);
}
Fishing* Fishing::create(TMXTiledMap* map, MainCharacter* maincharacter) {

    Fishing* ret = new Fishing();
    if (ret && ret->init(map, maincharacter)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}
//�Ƿ�����
void Fishing::ifgainfish() {
    
    int random_number = std::rand() % (5000 + 1); // ���� 0 �� max_value ֮��������
    if (random_number == 5) {
        fish_number++;
        //������ʾ��ǩ
        auto label = Label::createWithSystemFont("You gain a fish!", "Arial", 35);
        label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
        label->setTextColor(Color4B::RED);
        this->addChild(label, 7);
        auto callback = [=]() {
            this->removeChild(label);
          
            };
        Action* rebackaction = Sequence::create(DelayTime::create(0.5), CallFunc::create(callback), nullptr);
        this->runAction(rebackaction);
    }
}
void Fishing::fishingListenerMouse(TMXTiledMap* map, MainCharacter* maincharacter) {
    // ��������¼�������
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = [=](Event* event) {
        EventMouse* mouseEvent = static_cast<EventMouse*>(event);
        Vec2 mapPosition = map->getPosition();
        if (isfishing == 1) {
            // ��ȡ�������λ��
            Vec2 clickPos = mouseEvent->getLocation();//�����Ͻ�Ϊԭ��
            clickPos.y = visibleSize.height - clickPos.y;//ת��Ϊ���½�Ϊԭ��
            auto tileLayer = map->getLayer("Back");
            //����ת��Ϊ��Ե�ͼ���½ǵ�
            clickPos.x = clickPos.x - mapPosition.x + maplength / 2;
            clickPos.y = clickPos.y - mapPosition.y + mapwidth / 2;
            // ת��Ϊ��Ե�ͼ���Ͻǵ�ͼ�鵥λ����
            int tileX = static_cast<int>(clickPos.x / (ScaleFactor * 16));
            int tileY = mapHeight - 1 - static_cast<int>((clickPos.y) / (ScaleFactor * 16));
            int tileGID = tileLayer->getTileGIDAt(Vec2(tileX, tileY));
            //CCLOG("Tile GID at (tileX: %d, tileY: %d) is %d", tileX, tileY, tileGID);
            if (tileLayer) {

                if (tileGID == AbleFishing) {//�ж��Ƿ��diaoyu
                    fishingcondition = 1;
                    
                    fishingprocess(map, maincharacter);
                    //�������
                }

            }
        }
        };
    // ����������ӵ��¼�������
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}
//ֹͣ��ɫ�ƶ�
void Fishing::myUpdateFunction2(TMXTiledMap* map,MainCharacter*maincharacter, std::string updateKey) {
   
        if (fishingcondition == 1) {
            map->stopAllActions(); // ֹͣ���ж���
            maincharacter->stopAllActions(); // ֹͣ���ж���
        
        }
        else {
            this->unschedule(updateKey);
        }
    
}
//���õ����ǩ���ɼ�
void Fishing::myUpdateFunction(std::string updateKey) {
 
        if (fishingcondition!=1) {
            isfishingnow->setVisible(false);
            isfishingnowtext->setVisible(false);
            this->unschedule(updateKey);
        }
    
}
//�Ƿ����ifgainfish����
void Fishing::myUpdateFunction3(std::string updateKey3) {
    if (fishingcondition == 1) {
       
            ifgainfish(); // ���ú���

        
    }
    else
        this->unschedule(updateKey3);
}