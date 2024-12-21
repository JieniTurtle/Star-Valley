#ifndef __ANIMALS_H__
#define __ANIMALS_H__

#include"MainCharacter.h"
#include "cocos2d.h"
USING_NS_CC;

class Animal : public Sprite {
public:
	//Animal���� ����·��ʾ����Animal/filename/moveup1.png
	Animate* moveup;
	Animate* moveleft;
	Animate* moveright;
	Animate* movedown;

	//���Animal�Ƿ�ѡ��
	bool ifSelected;

	//·�����
	std::vector<Vec2> Animalpath;//·������
	int currentPathIndex;//·������
	float speed;//�ٶ�

	//Anima����
	std::string animalName;

	//����Animal���ƶ��Ͷ���
	void updatemove(float dt);

	// ���Ŷ���
	void playAnimation(const std::string& direction);

	// �����ƶ�·��
	void setPath(const std::vector<Vec2>& path);
};

class Cow : public Animal {
public:
	//Animal��ֹͼƬ·��Ϊ Animal/filename/static.png
	static Cow* create(const std::string& filename);

	//Animal�����С
	static int Animalsize_x;
	static int Animalsize_y;

	//Animal����Ķ���˳��
	static int Animalorder_up;
	static int Animalorder_left;
	static int Animalorder_right;
	static int Animalorder_down;

	//�Ҹ���
	double happiness = 0;

	//����
	MainCharacter* mainChar;
	//��ͼָ��
	TMXTiledMap* mainmap;

	//cow�ѱ�ι���ķ�������
	cocos2d::Label* cow_feed_label;

	//cow�ѱ������ķ�������
	cocos2d::Label* cow_touch_label;

	//��������붯���λ�ù�ϵ
	void isMainCharNear(float delta);

	//����Ƿ񱻸���
	void isMainCharTouch(float delta);

	//��ʱ���Ҹ��ή��
	void decreaseHappiness(float delta);

	//�Ƿ��ڸ���
	bool isNearSprite = false;

	//��Ӽ��̼����¼�
	void addKeyboardListener();

	//����������ʱ�������¼�
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	//��ǩ����
	void hideLabel(float dt);

	//��ʼ��
	bool init();

	//��������
	void setMaincharacter(MainCharacter* mainCharacter) {
		mainChar = mainCharacter;
	}
	//�����ͼָ��
	void setMap(TMXTiledMap* map) {
		mainmap = map;
	}
	//���Ŷ���
	static void move(Cow* cow, TMXTiledMap* map);
};

class Sheep : public Animal {
public:
	//Animal��ֹͼƬ·��Ϊ Animal/filename/static.png
	static Sheep* create(const std::string& filename);

	//Animal�����С
	static int Animalsize_x;
	static int Animalsize_y;

	//Animal����Ķ���˳��
	static int Animalorder_up;
	static int Animalorder_left;
	static int Animalorder_right;
	static int Animalorder_down;

	//�Ҹ���
	double happiness = 0;

	//����
	MainCharacter* mainChar;
	//��ͼָ��
	TMXTiledMap* mainmap;

	//cow�ѱ�ι���ķ�������
	cocos2d::Label* sheep_feed_label;

	//cow�ѱ������ķ�������
	cocos2d::Label* sheep_touch_label;

	//��������붯���λ�ù�ϵ
	void isMainCharNear(float delta);

	//����Ƿ񱻸���
	void isMainCharTouch(float delta);

	//��ʱ���Ҹ��ή��
	void decreaseHappiness(float delta);

	//�Ƿ��ڸ���
	bool isNearSprite = false;

	//��Ӽ��̼����¼�
	void addKeyboardListener();

	//����������ʱ�������¼�
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	//��ǩ����
	void hideLabel(float dt);

	//��ʼ��
	bool init();

	//��������
	void setMaincharacter(MainCharacter* mainCharacter) {
		mainChar = mainCharacter;
	}
	//�����ͼָ��
	void setMap(TMXTiledMap* map) {
		mainmap = map;
	}

	//���Ŷ���
	static void move(Sheep* sheep, TMXTiledMap* map);
};

class Chicken : public Animal {
public:
	//Animal��ֹͼƬ·��Ϊ Animal/filename/static.png
	static Chicken* create(const std::string& filename);

	//Animal�����С
	static int Animalsize_x;
	static int Animalsize_y;

	//Animal����Ķ���˳��
	static int Animalorder_up;
	static int Animalorder_left;
	static int Animalorder_right;
	static int Animalorder_down;

	//�Ҹ���
	double happiness = 0;

	//����
	MainCharacter* mainChar;
	//��ͼָ��
	TMXTiledMap* mainmap;

	//cow�ѱ�ι���ķ�������
	cocos2d::Label* chicken_feed_label;
	//cow�ѱ�ι���ķ�������
	cocos2d::Label* chicken_touch_label;

	//��������붯���λ�ù�ϵ
	void isMainCharNear(float delta);

	//����Ƿ񱻸���
	void isMainCharTouch(float delta);

	//��ʱ���Ҹ��ή��
	void decreaseHappiness(float delta);

	//�Ƿ��ڸ���
	bool isNearSprite = false;

	//��Ӽ��̼����¼�
	void addKeyboardListener();

	//����������ʱ�������¼�
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	//��ǩ����
	void hideLabel(float dt);

	//��������
	void setMaincharacter(MainCharacter* mainCharacter) {
		mainChar = mainCharacter;
	}
	//�����ͼָ��
	void setMap(TMXTiledMap* map) {
		mainmap = map;
	}

	//��ʼ��
	bool init();
	//���Ŷ���
	static void move(Chicken* chicken, TMXTiledMap* map);
};
#endif 
#pragma once
