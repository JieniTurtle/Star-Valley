#include "Gloves.h"
#include "SimpleAudioEngine.h"

bool Gloves::init(TMXTiledMap* map) {
    isgloves = 0;
    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setglovescheckbox();//�������׸�ѡ��

    glovesListenerMouse(map);
    return true;
}

void  Gloves::setglovescheckbox() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    //������ͷͼ��
    glovescheckbox = ui::CheckBox::create("gloves1.png", "gloves2.png");
    glovescheckbox->setPosition(Vec2(visibleSize.width *3.5/ 8, visibleSize.height / 4)); // ����λ��

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
    this->addChild(glovescheckbox);


}

Gloves* Gloves::create(TMXTiledMap* map) {

    Gloves* ret = new Gloves();
    if (ret && ret->init(map)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

void Gloves::glovesListenerMouse(TMXTiledMap* map) {
    // ��������¼�������
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = [=](Event* event) {
        EventMouse* mouseEvent = static_cast<EventMouse*>(event);
        Vec2 mapPosition = map->getPosition();
        if (isgloves == 1) {
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

                if (tileGID == MaturePlantID) {//����������Ƭid���ж��Ƿ����ȡ

                    tileLayer->setTileGID(AbleHoeID, Vec2(tileX, tileY));//�滻��ԭʼͼ��
                    wheat_number++;
                    experience += GainExp;
                    //CCLOG("Tile GID at (tileX: %d, tileY: %d) is %d", tileX, tileY, tileGID);
                }
                //��Ƭ���½�Ϊê��
                if (tileGID == MaturePlantTwoID) {//����������Ƭid���ж��Ƿ����ȡ

                    tileLayer->setTileGID(AbleHoeID, Vec2(tileX, tileY));//�滻��ԭʼͼ��
                    carrot_number++;
                    experience += GainExp;
                    //CCLOG("Tile GID at (tileX: %d, tileY: %d) is %d", tileX, tileY, tileGID);
                }
                //��Ƭ���½�Ϊê��
            }
        }
        };
    // ����������ӵ��¼�������
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}