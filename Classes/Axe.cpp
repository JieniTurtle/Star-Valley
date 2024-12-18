#include "Axe.h"

#include "SimpleAudioEngine.h"

bool Axe::init(TMXTiledMap* map, int& woodnum) {
    isaxe = 0;
    visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�

    mapWidth = map->getMapSize().width;  // �����ש����
    mapHeight = map->getMapSize().height; // �����ש����
    tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
    tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
    maplength = mapWidth * tileWidth;
    mapwidth = mapHeight * tileHeight;
    setaxecheckbox();//���ó�ͷ��ѡ��

    axeListenerMouse(map,woodnum);
    return true;
}

void  Axe::setaxecheckbox() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    //������ͷͼ��
    axecheckbox = ui::CheckBox::create("axe1.png", "axe2.png");
    axecheckbox->setPosition(Vec2(visibleSize.width*2 / 8, visibleSize.height / 4)); // ����λ��
    this->addChild(axecheckbox);


}

Axe* Axe::create(TMXTiledMap* map, int& woodnum) {

    Axe* ret = new Axe();
    if (ret && ret->init(map,woodnum)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

void Axe::axeListenerMouse(TMXTiledMap* map, int& woodnum) {
    // ��������¼�������
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = [=,&woodnum](Event* event) {
        EventMouse* mouseEvent = static_cast<EventMouse*>(event);
        Vec2 mapPosition = map->getPosition();
        if (isaxe == 1) {
            // ��ȡ�������λ��
            Vec2 clickPos = mouseEvent->getLocation();//�����Ͻ�Ϊԭ��
            clickPos.y = visibleSize.height - clickPos.y;//ת��Ϊ���½�Ϊԭ��
            //����ת��Ϊ��Ե�ͼ���½ǵ�
            clickPos.x = clickPos.x - mapPosition.x + maplength / 2;
            clickPos.y = clickPos.y - mapPosition.y + mapwidth / 2;
            // ת��Ϊ��Ե�ͼ���Ͻǵ�ͼ�鵥λ����
            int tileX = static_cast<int>(clickPos.x / (ScaleFactor * 16));
            int tileY = mapHeight - 1 - static_cast<int>((clickPos.y) / (ScaleFactor * 16));
          //����ÿһ����ͼ��
            for (int i = 1; i <= numberOfTree; ++i) {
                // ����ͼ������
                std::string layerName = "Tree" + std::to_string(i); // ���� "Tree1", "Tree2", ...

                // ��ȡ����ͼ��
                auto treeLayer = map->getLayer(layerName);

                // ���ͼ���Ƿ���Ч
                if (treeLayer) {
                    int tileGID = treeLayer->getTileGIDAt(Vec2(tileX, tileY));//������Ƿ�����
                    if (tileGID != 0) {
                        map->removeChild(treeLayer, true);//�Ƴ���ͼ�㣬��ʾ������
                        woodnum += OneTreeForWood;
                    }
                    
                }

            }
          
            
            
        }
        };
    // ����������ӵ��¼�������
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}