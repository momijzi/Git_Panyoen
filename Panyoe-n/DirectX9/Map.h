#pragma once

class Puyo;

class Map
{
public:
	//�Ղ�̐F��񋓂Őݒ�
	enum Color { NON, RED, GREEN, BLUE, YELLOW, PURPLE };
	Color color;

private:
	//�Ղ�̘g�̑傫��
	static const int Mapx = 6, Mapy = 12;

	//�Ղ悪�ǂ��ɂ���̂�����p
	Color PuyoData[Mapy][Mapx];
	//�Ȃ����Ă��ď�����Ղ��true��
	bool connectPuyo[Mapy][Mapx];
	bool checkPuyo[Mapy][Mapx];
	bool dousePuyo[Mapy][Mapx];
	//���݂̂Ȃ���̐��܂��t���O������
	int ConnectCount;
	//���ׂ�Ղ�̐F������
	Color checkPuyoColor;

	//�s���t���O
	bool douseFlag;
	bool fallFlag;
	bool NewPuyoFlag;

public:
	Map();
	~Map();
	//�Ղ�Ƀf�[�^���i�[

	int GetMapx() { return Mapx; }
	int GetMapy() { return Mapy; }
	bool GetDouseFlag(){ return douseFlag; }
	bool GetFallFlag() { return fallFlag; }
	bool GetNewPuyoFlag() { return NewPuyoFlag; }
	Color GetPuyoData(int x, int y) { return PuyoData[y][x]; }
	

	//�������Ă����Ղ�̍Ō�̍��W���i�[
	void SetPuyoData(int x, int y, int num);
	//�Ղ�̃f�[�^��ǂݍ���
	void StorePuyoData(Puyo* puyo);
	//�Ȃ����Ă��邩���f
	void ConnectPuyo();
	void CheckConnectPuyo(int x, int y);

	//�Ȃ����Ă���Ղ悪������������
	void DousePuyo();
	//�A���ɉ����Ă̗���
	void mFallPuyo();

	//������//���Z�b�g�p
	void Release();
};
