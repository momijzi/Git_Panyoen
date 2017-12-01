#pragma once


class Puyo;
class Map;

class GameManager
{
private:
	int SPEED;//��i�����鏈���̃X�s�[�h
	int CurrentSpeed;//�X�s�[�h�ɒB�������𔻒肷��
	bool contactPuyoLeft;//�Ղ悪�����ƂԂ�����
	bool contactPuyoRight;

public:
	GameManager();
	~GameManager();

	void SetContactPuyoLeft(bool flag) { contactPuyoLeft = flag; }
	void SetContactPuyoRight(bool flag) { contactPuyoRight = flag; }
	bool GetContactPuyoLeft() { return contactPuyoLeft; }
	bool GetContactPuyoRight() { return contactPuyoRight; }

	void MovePuyo(Puyo* puyo ,Map* map);

};
