
#include "MainCharacter.h"
#include "SimpleAudioEngine.h"
MainCharacter* MainCharacter::create(const std::string& filename) {

    MainCharacter* ret = new MainCharacter();
    if (ret && ret->init(filename)) {
        ret->autorelease(); // �Զ��ͷ��ڴ�
        return ret;
    }
    CC_SAFE_DELETE(ret); // �������ʧ�ܣ���ȫɾ��
    return nullptr;
}

bool MainCharacter::init(const std::string& filename) {
    if (!Sprite::initWithFile(filename)) { // ʹ�ô�����ļ�����ʼ������
        return false;
    }

    this->setScale(0.25);

    

    //��Ӽ��̼����¼�
    addKeyboardListener();
    this->schedule(CC_SCHEDULE_SELECTOR(MainCharacter::update), 0.15f); //ʱ��ˢ���¼�

    return true;
}
void MainCharacter::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_W: // W
            movementkeys[0] = true; // �����ƶ�
            break;
        case EventKeyboard::KeyCode::KEY_A: // A
            movementkeys[1] = true; // �����ƶ�
            break;
        case EventKeyboard::KeyCode::KEY_S: // S
            movementkeys[2] = true; // �����ƶ�
            break;
        case EventKeyboard::KeyCode::KEY_D: // D
            movementkeys[3] = true; // �����ƶ�
            break;
        default:
            break;
    }

}
void MainCharacter::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_W:
            movementkeys[0] = false;
            break;
        case EventKeyboard::KeyCode::KEY_A:
            movementkeys[1] = false;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            movementkeys[2] = false;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            movementkeys[3] = false;
            break;
        default:
            break;
    }
}
void MainCharacter::addKeyboardListener() {
    // ��Ӽ����¼�����
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MainCharacter::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(MainCharacter::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
// ���½�ɫλ��
void MainCharacter::update(float delta) {
    // ��ȡ��ǰ��ͼλ��
    Vec2 position = mainmap->getPosition();
    int mapWidth = mainmap->getMapSize().width;  // �����ש����
    int mapHeight = mainmap->getMapSize().height; // �����ש����
    int tileWidth = mainmap->getTileSize().width * 2; // ������ש�����ؿ��
    int tileHeight = mainmap->getTileSize().height * 2; // ������ש�����ظ߶�
    int mapwidth = mapWidth * tileWidth;
    int mapheight = mapHeight * tileHeight;//��ͼ����
    // ��ȡ��ɫ�ĳߴ�
    Size characterSize = this->getContentSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    // ���ݰ��µļ��ƶ���ɫ
      // �����ƶ��߼�
    if (movementkeys[0]) { // W
        position.y -= 10; // �����ƶ�
    }
    if (movementkeys[1]) { // A
        position.x += 10; // �����ƶ�
    }
    if (movementkeys[2]) { // S
        position.y += 10; // �����ƶ�
    }
    if (movementkeys[3]) { // D
        position.x -= 10; // �����ƶ�
    }
    //����Ƿ񳬳��߽�
    if (position.x > mapwidth / 2) {
        position.x = mapwidth / 2;
    }
    if (position.y > mapheight / 2) {
        position.y = mapheight / 2;
    }
    if (position.x < visibleSize.width - mapwidth / 2) {
        position.x = visibleSize.width - mapwidth / 2;
    }
    if (position.y < visibleSize.height - mapheight / 2) {
        position.y = visibleSize.height - mapheight / 2;
    }

    // ��������֡
    Vector<SpriteFrame*> animationFramesdown;//�����߶���
    for (int i = 1; i <= 3; i++) {
        auto frame = SpriteFrame::create(StringUtils::format("characterdown%d.png", i).c_str(), Rect(0, 0, 100, 160));
        animationFramesdown.pushBack(frame);
    }

    Vector<SpriteFrame*> animationFramesright;//�����߶���
    for (int i = 1; i <= 3; i++) {
        auto frame = SpriteFrame::create(StringUtils::format("characterright%d.png", i).c_str(), Rect(0, 0, 100, 160));
        animationFramesright.pushBack(frame);
    }

    Vector<SpriteFrame*> animationFramesleft;//�����߶���
    for (int i = 1; i <= 3; i++) {
        auto frame = SpriteFrame::create(StringUtils::format("characterleft%d.png", i).c_str(), Rect(0, 0, 100, 160));
        animationFramesleft.pushBack(frame);
    }

    Vector<SpriteFrame*> animationFramesup;//�����߶���
    for (int i = 1; i <= 3; i++) {
        auto frame = SpriteFrame::create(StringUtils::format("characterup%d.png", i).c_str(), Rect(0, 0, 100, 160));
        animationFramesup.pushBack(frame);
    }
    // ��������
    walkAnimationdown = Animation::createWithSpriteFrames(animationFramesdown, 0.1f);
    walkAnimationright = Animation::createWithSpriteFrames(animationFramesright, 0.1f);
    walkAnimationleft = Animation::createWithSpriteFrames(animationFramesleft, 0.1f);
    walkAnimationup = Animation::createWithSpriteFrames(animationFramesup, 0.1f);
    auto walkAnimationnext = Animation::create();
  
    // ������·����
    if (movementkeys[2]
        ) {
        walkAnimationnext = walkAnimationdown->clone();
        staticnext = "characterdown2.png";
    }
    if (movementkeys[3]) {
        walkAnimationnext = walkAnimationright->clone();
        staticnext = "characterright2.png";
    }
    if (movementkeys[1]) {
        walkAnimationnext = walkAnimationleft->clone();
        staticnext = "characterleft2.png";
    }
    if (movementkeys[0]) {
        walkAnimationnext = walkAnimationup->clone();
        staticnext = "characterup2.png";
    }

    // ���� Animate ����
    if (movementkeys[0] || movementkeys[1] || movementkeys[2] || movementkeys[3]) {
        auto animateActionnext = Animate::create(walkAnimationnext);
        this->runAction(RepeatForever::create(animateActionnext));
        mainmap->runAction(MoveTo::create(0.3, position));
    }
    else {
        this->stopAllActions(); // ֹͣ���ж���

        this->setTexture(staticnext); // �л�Ϊ��̬ͼ��
    }


}

