#pragma once

class Puyo;

class Map
{
public:
	//ぷよの色を列挙で設定
	enum Color { NON, RED, GREEN, BLUE, YELLOW, PURPLE };
	Color color;

	struct ConnectFlag
	{
		//つながる場所が無ければfalseを返す
		bool Upflag;
		bool Downflag;
		bool Leftflag;
		bool Rightflag;

		//次も調べる必要があるとき再度チェックするためのループ用変数
		int ConnectRoop;

		//つながっている個数格納
		int ConnectCount;

	};

private:
	//ぷよの枠の大きさ
	static const int Mapx = 6, Mapy = 12;

	//ぷよがどこにいるのか判定用
	Color PuyoData[Mapy][Mapx];
	//つながっていて消えるぷよをtrueに
	bool connectPuyo[Mapy][Mapx];
	
	ConnectFlag connectFlag[2];

public:
	Map();
	~Map();
	//ぷよにデータを格納
	

	int GetMapx() { return Mapx; }
	int GetMapy() { return Mapy; }
	Color GetPuyoData(int x, int y) { return PuyoData[y][x]; }
	

	//動かしていたぷよの最後の座標を格納
	void SetPuyoData(int x, int y, int num);
	//ぷよのデータを読み込み
	void StorePuyoData(Puyo* puyo);
	//つながっているか判断
	void ConnectPuyo(Puyo* puyo);
	//連鎖に応じての落下
	void mFallPuyo(Puyo* puyo);

	//初期化//リセット用
	void Release();
};
