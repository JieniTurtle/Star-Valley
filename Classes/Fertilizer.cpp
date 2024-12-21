#include "Fertilizer.h"
#include "SimpleAudioEngine.h"

bool Fertilizer::init(TMXTiledMap* map) {
    isfertilizer = 0;
   
    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setfertilizercheckbox();//���ó�ͷ��ѡ��
    showfertilizernum();//��ʾ��������
    fertilizerListenerMouse(map);
    return true;
}

void  Fertilizer::setfertilizercheckbox() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    //������ͷͼ��
    fertilizercheckbox = ui::CheckBox::create("fertilizer1.png", "fertilizer2.png");
    fertilizercheckbox->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height * 5 / 10)); // ����λ��

    this->addChild(fertilizercheckbox);


}

Fertilizer* Fertilizer::create(TMXTiledMap* map) {

    Fertilizer* ret = new Fertilizer();
    if (ret && ret->init(map)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

void Fertilizer::fertilizerListenerMouse(TMXTiledMap* map) {
    // ��������¼�������
    auto mouseListener = EventListenerMouse::create();
   
    mouseListener->onMouseDown = [=](Event* event) {
        EventMouse* mouseEvent = static_cast<EventMouse*>(event);
        Vec2 mapPosition = map->getPosition();
        if (isfertilizer == 1) {
        
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

                if ((tileGID == RawPlantWaterID) && fertilizer_number > 0) {//�н�ˮ�ķ�ѿid���ж��Ƿ���÷���
                   
                    tileLayer->setTileGID(MaturePlantID, Vec2(tileX, tileY));
                    // ʹ���꼴�̳���
 
                    fertilizer_number--;//ʩ�ʳɹ���������������
                }
                //��Ƭ���½�Ϊê��
                if ((tileGID == RawPlantWaterTwoID) && fertilizer_number > 0) {//�н�ˮ�ķ�ѿid���ж��Ƿ���÷���

                    tileLayer->setTileGID(MaturePlantTwoID, Vec2(tileX, tileY));
                    // ʹ���꼴�̳���
                
                    fertilizer_number--;//ʩ�ʳɹ���������������
                }
            }
        }
        };
    // ����������ӵ��¼�������
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Fertilizer::showfertilizernum() {
    // ������ǩ����ӵ�������
    auto label = Label::createWithTTF(std::to_string(fertilizer_number), "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height * 4.5 / 10)); // ���ñ�ǩ��ʾ��λ��
    this->addChild(label, 1);

    // ����һ����ʱ������������Ա���ÿ֡���±�ǩ
    this->schedule([this, label](float dt) {
        label->setString(std::to_string(fertilizer_number));
        }, "update_label_key");
}



