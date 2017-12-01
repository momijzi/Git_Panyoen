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
	bool connectPuyo[Mapy][Mapx];
	//���������p�̔z��
	int AroundData[2]{ -1,1 };
	

public:
	Map();
	~Map();
	//�Ղ�Ƀf�[�^���i�[
	

	int GetMapx() { return Mapx; }
	int GetMapy() { return Mapy; }
	Color GetPuyoData(int x, int y) { return PuyoData[y][x]; }
	
	//�������Ă����Ղ�̍Ō�̍��W���i�[
	void SetPuyoData(int x, int y, int num);
	//�Ղ�̃f�[�^��ǂݍ���
	void StorePuyoData(Puyo* puyo);
	//�Ȃ����Ă��邩���f
	void ConnectPuyo(Puyo* puyo);
	//�A���ɉ����Ă̗���
	void mFallPuyo(Puyo* puyo);

	//������//���Z�b�g�p
	void Release();
};
