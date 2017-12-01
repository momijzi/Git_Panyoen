#pragma once


class Puyo;
class Map;

class GameManager
{
private:
	int SPEED;//一段落ちる処理のスピード
	int CurrentSpeed;//スピードに達したかを判定する
	bool contactPuyoLeft;//ぷよが何かとぶつかった
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
