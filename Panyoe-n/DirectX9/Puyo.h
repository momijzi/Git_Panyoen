#pragma once

class GameManager;
class Map;

class Puyo
{
private:
	
	int MaxPuyoColor;

public:
	Puyo();
	~Puyo();

	struct PuyoColor
	{
		//�Ղ�̐F
		int PuyoLeftColor;
		int PuyoRightColor;
		//�Ղ�̍��W
		int PuyoLeftx;
		int PuyoLefty;
		int PuyoRightx;
		int PuyoRighty;
	};
	//���ړ�
	void SideMovePuyo(int w, Map* map);
	//��]
	void RotaPuyo(int wh, Map* map,GameManager* gMane);

	void FallPuyo(Map* map,GameManager* gMane);

private:

	PuyoColor* pPuyoColor;

	PuyoColor PuyoData[2];
public:

	int GetMaxPuyoColor() { return MaxPuyoColor; }

	void ResetPuyoData(int num);
	void SetMaxPuyoColor(int mColor) { MaxPuyoColor = mColor; }
	PuyoColor GetPuyoInfo(int Num) { return PuyoData[Num]; }
	//�V�����Ղ��ҋ@���Ă���f�[�^����Ăяo��
	//�܂��ҋ@�f�[�^��V���ɍ쐬
	void NewPuyoData();
	//�ŏ��ɏo���Ղ�̃f�[�^��ݒ�
	void Release();
};
