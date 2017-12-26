#pragma once
#include<vector>
#include<list>
#include<algorithm>

class Puyo;

class Map
{
public:
	//�Ղ�̐F��񋓂Őݒ�
	enum Color {RED, GREEN, BLUE, YELLOW, PURPLE , NON=999	};
	Color color;


	struct ConnectNum
	{
		//�Ȃ���̐�
		int Connect;
	};
	std::vector<ConnectNum> ConnectData[5];
	ConnectNum ConnectCheck;

	std::list<int> douseData;

	//�F�̃`�F�b�N�p
	int ColorNum;
	int PuyocheakX;
	int PuyocheakY;

private:
	//�Ղ�̘g�̑傫��
	static const int Mapx = 6, Mapy = 12;

	//�Ղ悪�ǂ��ɂ���̂�����p
	Color PuyoData[Mapy][Mapx];
	ConnectNum *pConnectNum;
	//�Ղ�̌��݂̊֘A��Ԃ�ۑ�

	//�Ȃ����Ă��ď�����Ղ��true��

	//���ׂ�Ղ�̐F������
	Color checkPuyoColor;

	//�e�O���[�v�𒲂ׂ邽�߂ɕK�v�ȕϐ�
	//�O���[�v�̌Q�w�������ϐ�
	int groupCount;
	//�ŏ��̒l�𒲂ׂ邽�߂ɕK�v
	int miniNum;
	//���X�^�X�L��������悤�ɔz��쐬
	int RasutaData[Mapy][Mapx];
	//�����̃��x�����m�F���܂����@�ŏ��̐��l��Ԃ��܂�
	bool SufferLabel;

	//�s���t���O
	bool overFlag;
	bool inspectFlag;
	bool douseFlag;
	bool fallFlag;
	bool NewPuyoFlag;
	int ConnectCount;
	bool Connectflag;
	bool cheakflag;

public:
	Map();
	~Map();
	//�Ղ�Ƀf�[�^���i�[

	int GetMapx() { return Mapx; }
	int GetMapy() { return Mapy; }
	bool GetOverFlag() { return overFlag; }
	bool GetDouseFlag(){ return douseFlag; }
	bool GetFallFlag() { return fallFlag; }
	bool GetNewPuyoFlag() { return NewPuyoFlag; }
	bool GetCheakFlag() { return cheakflag; }
	Color GetPuyoData(int x, int y) { return PuyoData[y][x]; }


	//�������Ă����Ղ�̍Ō�̍��W���i�[
	void SetPuyoData(int x, int y, int num);
	//�Ղ�̃f�[�^��ǂݍ���
	void StorePuyoData(Puyo* puyo);

	void CheckConnectPuyo(Puyo* puyo);
	//�Ղ�̊֘A�f�[�^���ēx�`�F�b�N����
	void RastaPuyoData(Puyo* puyo);

	//�Ȃ����Ă���Ղ悪������������
	void DousePuyo(Puyo* puyo);
	//�A���ɉ����Ă̗���
	void mFallPuyo();

	//������//���Z�b�g�p
	void Release();
};
