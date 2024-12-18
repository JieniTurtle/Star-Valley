    #include "Tools.h"

    #include "SimpleAudioEngine.h"

 bool Tools:: init(TMXTiledMap* map) {
     ishoe = 0;
     visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
     
      mapWidth = map->getMapSize().width;  // �����ש����
      mapHeight = map->getMapSize().height; // �����ש����
      tileWidth = map->getTileSize().width * ScaleFactor; // ������ש�����ؿ��
      tileHeight = map->getTileSize().height * ScaleFactor; // ������ש�����ظ߶�
     maplength = mapWidth * tileWidth;
     mapwidth = mapHeight * tileHeight;
     sethoecheckbox( );//���ó�ͷ��ѡ��
     
     hoeListenerMouse(map);
     return true;
}

 void  Tools::sethoecheckbox() {
     auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
     //������ͷͼ��
     hoecheckbox = ui::CheckBox::create("chutou.png", "chutou2.png");
     hoecheckbox->setPosition(Vec2(visibleSize.width / 8, visibleSize.height / 4)); // ����λ��
   
     //// ����¼�������
     //hoecheckbox->addEventListener([this,seeds,wheat,gloves](Ref* sender, ui::CheckBox::EventType type) {
     //    switch (type) {
     //        case ui::CheckBox::EventType::SELECTED:
     //            ishoe = 1;
     //            seeds->seedscheckbox->setSelected(false); // ȡ��ѡ����һ����ѡ��
     //            gloves->glovescheckbox->setSelected(false);
     //            wheat->wheatcheckbox->setSelected(false);
     //            break;
     //        case ui::CheckBox::EventType::UNSELECTED:
     //            ishoe = 0;
     //            break;
     //        default:
     //            break;
     //    }
     //    });
     this->addChild(hoecheckbox);


 }

 Tools* Tools::create(TMXTiledMap* map) {

     Tools* ret = new Tools();
     if (ret && ret->init(map)) {
         ret->autorelease(); // �Զ��ͷ��ڴ�
         return ret;
     }
     CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
     return nullptr;
 }

 void Tools::hoeListenerMouse(TMXTiledMap* map) {
     // ��������¼�������
     auto mouseListener = EventListenerMouse::create();

     mouseListener->onMouseDown = [=](Event* event) {
         EventMouse* mouseEvent = static_cast<EventMouse*>(event);
         Vec2 mapPosition = map->getPosition();
         if (ishoe == 1) {
             // ��ȡ�������λ��
             Vec2 clickPos = mouseEvent->getLocation();//�����Ͻ�Ϊԭ��
             clickPos.y = visibleSize.height - clickPos.y;//ת��Ϊ���½�Ϊԭ��
             auto tileLayer = map->getLayer("soil");
             //����ת��Ϊ��Ե�ͼ���½ǵ�
             clickPos.x = clickPos.x - mapPosition.x + maplength / 2;
             clickPos.y = clickPos.y - mapPosition.y + mapwidth / 2;
             // ת��Ϊ��Ե�ͼ���Ͻǵ�ͼ�鵥λ����
             int tileX = static_cast<int>(clickPos.x / (ScaleFactor * 16));
             int tileY = mapHeight - 1 -static_cast<int>((clickPos.y) / (ScaleFactor * 16));
             int tileGID = tileLayer->getTileGIDAt(Vec2(tileX, tileY));
             //CCLOG("Tile GID at (tileX: %d, tileY: %d) is %d", tileX, tileY, tileGID);
             if (tileLayer) {

                 if (tileGID == AbleHoeID) {//������Ƭid���ж��Ƿ�ɸ���
                     
                     tileLayer->setTileGID(HoeOverID, Vec2(tileX, tileY));//�滻�ɸ����ͼ��
                
                     //CCLOG("Tile GID at (tileX: %d, tileY: %d) is %d", tileX, tileY, tileGID);
                 }
                 //��Ƭ���½�Ϊê��

             }
         }
         };
     // ����������ӵ��¼�������
     Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
 }