#pragma once

class Puyo;

class Map
{
public:
	//�Ղ�̐F��񋓂Őݒ�
	enum Color { NON, RED, GREEN, BLUE, YELLOW, PURPLE };
	Color color;

	struct ConnectFlag
	{
		//�Ȃ���ꏊ���������false��Ԃ�
		bool Upflag;
		bool Downflag;
		bool Leftflag;
		bool Rightflag;

		//�������ׂ�K�v������Ƃ��ēx�`�F�b�N���邽�߂̃��[�v�p�ϐ�
		int ConnectRoop;

		//�Ȃ����Ă�����i�[
		int ConnectCount;

	};

private:
	//�Ղ�̘g�̑傫��
	static const int Mapx = 6, Mapy = 12;

	//�Ղ悪�ǂ��ɂ���̂�����p
	Color PuyoData[Mapy][Mapx];
	//�Ȃ����Ă��ď�����Ղ��true��
	bool connectPuyo[Mapy][Mapx];
	
	ConnectFlag connectFlag[2];

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
