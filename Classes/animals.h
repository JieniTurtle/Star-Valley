#ifndef __ANIMALS_H__
#define __ANIMALS_H__

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
	static int Animalsize_x ;
	static int Animalsize_y ;

	//Animal����Ķ���˳��
	static int Animalorder_up;
	static int Animalorder_left;
	static int Animalorder_right;
	static int Animalorder_down;

	//��ʼ��
	bool init();
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

	//��ʼ��
	bool init();
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

	//��ʼ��
	bool init();
	//���Ŷ���
	static void move(Chicken* chicken, TMXTiledMap* map);
};
#endif 
#pragma once
