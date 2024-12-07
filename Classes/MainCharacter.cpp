
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
    return true;
}
void MainCharacter::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    // ��ȡ��ǰ��ɫλ��
    Vec2 position =this->getPosition();

    // ��ȡ��ɫ�ĳߴ�
    Size characterSize = this->getContentSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    // ���ݰ��µļ��ƶ���ɫ
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_W: // ����
            position.y += 10; // 10 ���ƶ�����
            break;
        case EventKeyboard::KeyCode::KEY_A: // ����
            position.x -= 10;
            break;
        case EventKeyboard::KeyCode::KEY_S: // ����
            position.y -= 10;
            break;
        case EventKeyboard::KeyCode::KEY_D: // ����
            position.x += 10;
            break;
        default:
            return;
    }
    //����Ƿ񳬳��߽�
    if (position.x < characterSize.width / 2) {
        position.x = characterSize.width / 2;
    }
    if (position.y < characterSize.height / 2) {
        position.y = characterSize.height / 2;
    }
    if (position.x > visibleSize.width - characterSize.width / 2) {
        position.x = visibleSize.width - characterSize.width / 2;
    }
    if (position.y > visibleSize.height - characterSize.height / 2) {
        position.y = visibleSize.height - characterSize.height / 2;
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
    std::string staticnext;//��ֹ����ͼƬ
    // ������·����
    if (             keyCode == EventKeyboard::KeyCode::KEY_S 
       ) {
        walkAnimationnext = walkAnimationdown->clone();
        staticnext = "characterdown2.png";
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_D) {
         walkAnimationnext = walkAnimationright->clone();
         staticnext = "characterright2.png";
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        walkAnimationnext = walkAnimationleft->clone();
        staticnext = "characterleft2.png";
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_W) {
        walkAnimationnext = walkAnimationup->clone();
        staticnext = "characterup2.png";
    }
    // ���� Animate ����
    auto animateActionnext = Animate::create(walkAnimationnext);
    this->runAction(RepeatForever::create(animateActionnext));
    //��ɫ�ƶ������Ŷ���
    this->runAction(Sequence::create(MoveTo::create(0.5, position), CallFunc::create([this, staticnext]() {

        this->stopAllActions(); // ֹͣ���ж���
        
        this->setTexture(staticnext); // �л�Ϊ��̬ͼ��

        }), nullptr));

}

void MainCharacter::addKeyboardListener() {
    // ��Ӽ����¼�����
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MainCharacter::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
