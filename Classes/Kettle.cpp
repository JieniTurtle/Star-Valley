#include "Kettle.h"

#include "SimpleAudioEngine.h"

bool Kettle::init(TMXTiledMap* map) {
    iskettle = 0;
    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setkettlecheckbox();//���ó�ͷ��ѡ��

    kettleListenerMouse(map);
    return true;
}

void  Kettle::setkettlecheckbox() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    //������ͷͼ��
    kettlecheckbox = ui::CheckBox::create("kettle1.png", "kettle2.png");
    kettlecheckbox->setPosition(Vec2(visibleSize.width*2.5 / 8, visibleSize.height / 4)); // ����λ��

    this->addChild(kettlecheckbox);


}

Kettle* Kettle::create(TMXTiledMap* map) {

    Kettle* ret = new Kettle();
    if (ret && ret->init(map)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

void Kettle::kettleListenerMouse(TMXTiledMap* map) {
    // ��������¼�������
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = [=](Event* event) {
        EventMouse* mouseEvent = static_cast<EventMouse*>(event);
        Vec2 mapPosition = map->getPosition();
        if (iskettle == 1) {
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

                if (tileGID == RawPlantNoWaterID) {//û�н�ˮ�ķ�ѿid���ж��Ƿ�ɽ�ˮ
                    
                    tileLayer->setTileGID(RawPlantWaterID, Vec2(tileX, tileY));//�滻�ɽ���ˮ���ͼ��
                    // ʹ�õ�����������������ƬID
                    auto callback = [this, tileX, tileY, tileLayer]() {
                        tileLayer->setTileGID(MaturePlantID, Vec2(tileX, tileY)); // �滻�ɳ���״̬��ͼ��
                        };
                    Action* rebackaction = Sequence::create(DelayTime::create(MatureTime), CallFunc::create(callback), nullptr);
                    this->runAction(rebackaction);
                    // �������ӳ�ִ�У�n�볤����
                    
                    if (scheduleCounter > 1000000) {
                        scheduleCounter = 0;
                    }//��ֹscheduleCounter���
                    std::string updateKey = "update_function_key_" + std::to_string(scheduleCounter++);
                    this->schedule([=](float dt) {
                        myUpdateFunction(rebackaction, tileLayer, tileX, tileY, updateKey); // ���ø��º���
                        }, 0.1f, updateKey);
                }
                //��Ƭ���½�Ϊê��
                if (tileGID == RawPlantNoWaterTwoID) {//û�н�ˮ�ķ�ѿid���ж��Ƿ�ɽ�ˮ

                    tileLayer->setTileGID(RawPlantWaterTwoID, Vec2(tileX, tileY));//�滻�ɽ���ˮ���ͼ��
                    // ʹ�õ�����������������ƬID
                    auto callback = [this, tileX, tileY, tileLayer]() {
                        tileLayer->setTileGID(MaturePlantTwoID, Vec2(tileX, tileY)); // �滻�ɳ���״̬��ͼ��
                        };
                    Action* rebackaction = Sequence::create(DelayTime::create(MatureTime), CallFunc::create(callback), nullptr);
                    this->runAction(rebackaction);
                    // �������ӳ�ִ�У�n�볤����

                    if (scheduleCounter > 1000000) {
                        scheduleCounter = 0;
                    }//��ֹscheduleCounter���
                    std::string updateKey = "update_function_key_" + std::to_string(scheduleCounter++);
                    this->schedule([=](float dt) {
                        myUpdateFunction(rebackaction, tileLayer, tileX, tileY, updateKey); // ���ø��º���
                        }, 0.1f, updateKey);
                }
                //��Ƭ���½�Ϊê��
            }
        }
        };
    // ����������ӵ��¼�������
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Kettle::myUpdateFunction(Action* rebackaction, TMXLayer* tileLayer, int tileX, int tileY, std::string updateKey) {
    if (rebackaction) {
        if ((tileLayer->getTileGIDAt(Vec2(tileX, tileY)) != RawPlantWaterID)&& (tileLayer->getTileGIDAt(Vec2(tileX, tileY)) != RawPlantWaterTwoID)) {
            this->stopAction(rebackaction);
            this->unschedule(updateKey);
        }
    }
}