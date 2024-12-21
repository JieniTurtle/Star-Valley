#include "Carrot.h"
#include "SimpleAudioEngine.h"

bool Carrot::init(TMXTiledMap* map) {
    iscarrot = 0;
 
    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setcarrotcheckbox();//���ó�ͷ��ѡ��
    showcarrotnum();//��ʾ��������
    //wheatListenerMouse(map);
    return true;
}

void  Carrot::setcarrotcheckbox() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    //������ͷͼ��
    carrotcheckbox = ui::CheckBox::create("carrot1.png", "carrot2.png");
    carrotcheckbox->setPosition(Vec2(visibleSize.width * 9.7 / 10, visibleSize.height * 7 / 10)); // ����λ��

    //// ����¼�������
    //wheatcheckbox->addEventListener([this](Ref* sender, ui::CheckBox::EventType type) {
    //    switch (type) {
    //        case ui::CheckBox::EventType::SELECTED:
    //            iswheat = 1;
    //            break;
    //        case ui::CheckBox::EventType::UNSELECTED:
    //            iswheat = 0;
    //            break;
    //        default:
    //            break;
    //    }
    //    });
    this->addChild(carrotcheckbox);


}

Carrot* Carrot::create(TMXTiledMap* map) {

    Carrot* ret = new Carrot();
    if (ret && ret->init(map)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

//void Wheat::wheatListenerMouse(TMXTiledMap* map) {
//    // ��������¼�������
//    auto mouseListener = EventListenerMouse::create();
//
//    mouseListener->onMouseDown = [=](Event* event) {
//        EventMouse* mouseEvent = static_cast<EventMouse*>(event);
//        Vec2 mapPosition = map->getPosition();
//        if (iswheat == 1) {
//            // ��ȡ�������λ��
//            Vec2 clickPos = mouseEvent->getLocation();//�����Ͻ�Ϊԭ��
//            clickPos.y = visibleSize.height - clickPos.y;//ת��Ϊ���½�Ϊԭ��
//            auto tileLayer = map->getLayer("Back");
//            //����ת��Ϊ��Ե�ͼ���½ǵ�
//            clickPos.x = clickPos.x - mapPosition.x + maplength / 2;
//            clickPos.y = clickPos.y - mapPosition.y + mapwidth / 2;
//            // ת��Ϊ��Ե�ͼ���Ͻǵ�ͼ�鵥λ����
//            int tileX = static_cast<int>(clickPos.x / (ScaleFactor * 16));
//            int tileY = mapHeight - 1 - static_cast<int>((clickPos.y) / (ScaleFactor * 16));
//            int tileGID = tileLayer->getTileGIDAt(Vec2(tileX, tileY));
//            //CCLOG("Tile GID at (tileX: %d, tileY: %d) is %d", tileX, tileY, tileGID);
//            if (tileLayer) {
//
//                if ((tileGID == 8000) && seedsnum > 0) {//�Ѿ��������Ƭid���ж��Ƿ����ֲ
//
//                    tileLayer->setTileGID(4000, Vec2(tileX, tileY));//�滻����ֲ���ͼ�飬��ʼ״̬
//                    seedsnum--;//��ֲ�ɹ���������������
//                    // ʹ�õ�����������������ƬID
//                    auto callback = [this, tileX, tileY, tileLayer]() {
//                        tileLayer->setTileGID(5000, Vec2(tileX, tileY)); // �滻�ɳ���״̬��ͼ��
//                        };
//
//                    // �������ӳ�ִ�У�2�볤����
//                    this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(callback), nullptr));
//                    //CCLOG("Tile GID at (tileX: %d, tileY: %d) is %d", tileX, tileY, tileGID);
//                }
//                //��Ƭ���½�Ϊê��
//
//            }
//        }
//        };
//    // ����������ӵ��¼�������
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
//}

void Carrot::showcarrotnum() {
    // ������ǩ����ӵ�������
    auto label = Label::createWithTTF(std::to_string(carrot_number), "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(visibleSize.width * 9.7 / 10, visibleSize.height * 6.5 / 10)); // ���ñ�ǩ��ʾ��λ��
    this->addChild(label, 1);

    // ����һ����ʱ������������Ա���ÿ֡���±�ǩ
    this->schedule([this, label](float dt) {
        label->setString(std::to_string(carrot_number));
        }, "update_label_key");
}