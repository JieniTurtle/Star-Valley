#include "Seedstwo.h"
#include "SimpleAudioEngine.h"

bool Seedstwo::init(TMXTiledMap* map) {
    isseedstwo = 0;
    seedstwonum = 10;
    scheduleCounter = 0;
    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setseedstwocheckbox();//���ó�ͷ��ѡ��
    showseedstwonum();//��ʾ��������
    seedstwoListenerMouse(map);
    return true;
}

void  Seedstwo::setseedstwocheckbox() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    //����seedstwoͼ��
    seedstwocheckbox = ui::CheckBox::create("seedstwo1.png", "seedstwo2.png");
    seedstwocheckbox->setPosition(Vec2(visibleSize.width * 9.7 / 10, visibleSize.height * 8 / 10)); // ����λ��


    this->addChild(seedstwocheckbox);


}

Seedstwo* Seedstwo::create(TMXTiledMap* map) {

    Seedstwo* ret = new Seedstwo();
    if (ret && ret->init(map)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

void Seedstwo::seedstwoListenerMouse(TMXTiledMap* map) {
    // ��������¼�������
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = [=](Event* event) {
        EventMouse* mouseEvent = static_cast<EventMouse*>(event);
        Vec2 mapPosition = map->getPosition();
        if (isseedstwo == 1) {
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

                if ((tileGID == HoeOverID) && seedstwonum > 0) {//�Ѿ��������Ƭid���ж��Ƿ����ֲ

                    tileLayer->setTileGID(RawPlantID, Vec2(tileX, tileY));//�滻����ֲ���ͼ�飬��ʼ״̬
                    seedstwonum--;//��ֲ�ɹ���������������
                    // ʹ�õ�������n��������ƬID
                    auto callback = [this, tileX, tileY, tileLayer]() {
                        tileLayer->setTileGID(AbleHoeID, Vec2(tileX, tileY)); // Ĭ��û��ˮ���滻�ɿɸ��ص�ͼ��
                        };

                    // �������ӳ�ִ�У�n���û��ˮ��ԭ
                    Action* rebackaction = Sequence::create(DelayTime::create(NoWaterDieTime), CallFunc::create(callback), nullptr);
                    this->runAction(rebackaction);
                    if (scheduleCounter > 1000000) {
                        scheduleCounter = 0;
                    }//��ֹscheduleCounter���
                    std::string updateKey = "update_function_key_" + std::to_string(scheduleCounter++);
                    this->schedule([=](float dt) {
                        myUpdateFunction(rebackaction, tileLayer, tileX, tileY, updateKey); // ���ø��º���
                        }, 0.1f, updateKey);
                    //CCLOG("Tile GID at (tileX: %d, tileY: %d) is %d", tileX, tileY, tileGID);
                }
                //��Ƭ���½�Ϊê��

            }
        }
        };
    // ����������ӵ��¼�������
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Seedstwo::showseedstwonum() {
    // ������ǩ����ӵ�������
    auto label = Label::createWithTTF(std::to_string(seedstwonum), "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(visibleSize.width * 9.7 / 10, visibleSize.height * 7.5 / 10)); // ���ñ�ǩ��ʾ��λ��
    this->addChild(label, 1);

    // ����һ����ʱ������������Ա���ÿ֡���±�ǩ
    this->schedule([this, label](float dt) {
        label->setString(std::to_string(seedstwonum));
        }, "update_label_key");
}
//����Ƿ�ȡ�����ظ�ԭ����������ˮ��ȡ���ö���

void Seedstwo::myUpdateFunction(Action* rebackaction, TMXLayer* tileLayer, int tileX, int tileY, std::string updateKey) {
    if (rebackaction) {
        if (tileLayer->getTileGIDAt(Vec2(tileX, tileY)) != RawPlantID) {
            this->stopAction(rebackaction);
            this->unschedule(updateKey);
        }
    }
}