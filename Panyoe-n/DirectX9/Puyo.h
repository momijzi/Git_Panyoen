#pragma once

class GameManager;

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
	void SideMovePuyo(int w);
	//��]
	void RotaPuyo(int wh);

	void FallPuyo(GameManager* gMane);

private:

	PuyoColor* pPuyoColor;

	PuyoColor PuyoData[2];
public:

	void SetMaxPuyoColor(int mColor) { MaxPuyoColor = mColor; }
	PuyoColor GetPuyoInfo(int Num) { return PuyoData[Num]; }
	//�V�����Ղ��ҋ@���Ă���f�[�^����Ăяo��
	//�܂��ҋ@�f�[�^��V���ɍ쐬
	void NewPuyoData();
	//�ŏ��ɏo���Ղ�̃f�[�^��ݒ�
	void Release();
};
