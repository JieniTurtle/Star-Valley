#include "Pickaxe.h"

#include "SimpleAudioEngine.h"

bool Pickaxe::init(TMXTiledMap* map) {
    ispickaxe = 0;
    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setpickaxecheckbox();//���ø�ѡ��

    pickaxeListenerMouse(map);
    return true;
}

void  Pickaxe::setpickaxecheckbox() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    //������ͷͼ��
    pickaxecheckbox = ui::CheckBox::create("pickaxe1.png", "pickaxe2.png");
    pickaxecheckbox->setPosition(Vec2(visibleSize.width *1.5/ 8, visibleSize.height / 4)); // ����λ��

 
    this->addChild(pickaxecheckbox);


}

Pickaxe* Pickaxe::create(TMXTiledMap* map) {

    Pickaxe* ret = new Pickaxe();
    if (ret && ret->init(map)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

void Pickaxe::pickaxeListenerMouse(TMXTiledMap* map) {
    // ��������¼�������
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = [=](Event* event) {
        EventMouse* mouseEvent = static_cast<EventMouse*>(event);
        Vec2 mapPosition = map->getPosition();
        if (ispickaxe == 1) {
            // ��ȡ�������λ��
            Vec2 clickPos = mouseEvent->getLocation();//�����Ͻ�Ϊԭ��
            clickPos.y = visibleSize.height - clickPos.y;//ת��Ϊ���½�Ϊԭ��
            auto tileLayer = map->getLayer("Mineral");
            //����ת��Ϊ��Ե�ͼ���½ǵ�
            clickPos.x = clickPos.x - mapPosition.x + maplength / 2;
            clickPos.y = clickPos.y - mapPosition.y + mapwidth / 2;
            // ת��Ϊ��Ե�ͼ���Ͻǵ�ͼ�鵥λ����
            int tileX = static_cast<int>(clickPos.x / (ScaleFactor * 16));
            int tileY = mapHeight - 1 - static_cast<int>((clickPos.y) / (ScaleFactor * 16));
            int tileGID = tileLayer->getTileGIDAt(Vec2(tileX, tileY));
            //CCLOG("Tile GID at (tileX: %d, tileY: %d) is %d", tileX, tileY, tileGID);
            if (tileLayer) {

                if (tileGID == StoneID) {//�ж��Ƿ����

                    tileLayer->setTileGID(0, Vec2(tileX, tileY));//ɾ��ͼ��
                    experience += GemExp;
                    stone_number++;
                }
                //��Ƭ���½�Ϊê��
                if (tileGID == GemID) {//�ж��Ƿ����

                    tileLayer->setTileGID(0, Vec2(tileX, tileY));//ɾ��ͼ��
                    experience += GemExp;
                    mineral_number++;
                }
            }
        }
        };
    // ����������ӵ��¼�������
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}