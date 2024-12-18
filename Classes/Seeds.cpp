#include "Seeds.h"
#include "SimpleAudioEngine.h"

bool Seeds::init(TMXTiledMap* map) {
    isseeds = 0;
    seedsnum = 10;
    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

     mapWidth = map->getMapSize().width;  // �����ש����
     mapHeight = map->getMapSize().height; // �����ש����
     tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ���
     tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setseedscheckbox();//���ó�ͷ��ѡ��
    showseedsnum();//��ʾ��������
    seedsListenerMouse(map);
    return true;
}

void  Seeds::setseedscheckbox() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    //������ͷͼ��
    seedscheckbox = ui::CheckBox::create("seeds1.png", "seeds2.png");
    seedscheckbox->setPosition(Vec2(visibleSize.width*9 / 10, visibleSize.height*8 / 10)); // ����λ��

    //// �����¼�������
    //seedscheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
    //    switch (type) {
    //        case ui::CheckBox::EventType::SELECTED:
    //            isseeds = 1;
    //            break;
    //        case ui::CheckBox::EventType::UNSELECTED:
    //            isseeds = 0;
    //            break;
    //        default:
    //            break;
    //    }
    //    });
    this->addChild(seedscheckbox);


}

Seeds* Seeds::create(TMXTiledMap* map) {

    Seeds* ret = new Seeds();
    if (ret && ret->init(map)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

void Seeds::seedsListenerMouse(TMXTiledMap* map) {
    // ��������¼�������
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = [=](Event* event) {
        EventMouse* mouseEvent = static_cast<EventMouse*>(event);
        Vec2 mapPosition = map->getPosition();
        if (isseeds == 1) {
            // ��ȡ�������λ��
            Vec2 clickPos = mouseEvent->getLocation();//�����Ͻ�Ϊԭ��
            clickPos.y = visibleSize.height - clickPos.y;//ת��Ϊ���½�Ϊԭ��
            auto tileLayer = map->getLayer("soil");
            //����ת��Ϊ��Ե�ͼ���½ǵ�
            clickPos.x = clickPos.x - mapPosition.x + maplength / 2;
            clickPos.y = clickPos.y - mapPosition.y + mapwidth / 2;
            // ת��Ϊ��Ե�ͼ���Ͻǵ�ͼ�鵥λ����
            int tileX = static_cast<int>(clickPos.x / (ScaleFactor * 16));
            int tileY = mapHeight - 1 - static_cast<int>((clickPos.y) / (ScaleFactor * 16));
            int tileGID = tileLayer->getTileGIDAt(Vec2(tileX, tileY));
            //CCLOG("Tile GID at (tileX: %d, tileY: %d) is %d", tileX, tileY, tileGID);
            if (tileLayer) {

                if ((tileGID == HoeOverID)&&seedsnum>0 ){//�Ѿ��������Ƭid���ж��Ƿ����ֲ

                    tileLayer->setTileGID(RawPlantID, Vec2(tileX, tileY));//�滻����ֲ���ͼ�飬��ʼ״̬
                    seedsnum--;//��ֲ�ɹ���������������
                    // ʹ�õ�����������������ƬID
                    auto callback = [this, tileX, tileY,tileLayer]() {
                        tileLayer->setTileGID(MaturePlantID, Vec2(tileX, tileY)); // �滻�ɳ���״̬��ͼ��
                        };

                    // �������ӳ�ִ�У�2�볤����
                    this->runAction(Sequence::create(DelayTime::create(MatureTime), CallFunc::create(callback), nullptr));
                    //CCLOG("Tile GID at (tileX: %d, tileY: %d) is %d", tileX, tileY, tileGID);
                }
                //��Ƭ���½�Ϊê��

            }
        }
        };
    // �����������ӵ��¼�������
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Seeds::showseedsnum() {
    // ������ǩ�����ӵ�������
    auto label = Label::createWithTTF(std::to_string(seedsnum), "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height*7.5 / 10)); // ���ñ�ǩ��ʾ��λ��
    this->addChild(label,1);

    // ����һ����ʱ������������Ա���ÿ֡���±�ǩ
    this->schedule([this,label](float dt) {
        label->setString(std::to_string(seedsnum));
        }, "update_label_key");
}