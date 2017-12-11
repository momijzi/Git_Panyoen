#pragma once

class Puyo;

class Map
{
public:
	//ぷよの色を列挙で設定
	enum Color { NON, RED, GREEN, BLUE, YELLOW, PURPLE };
	Color color;

private:
	//ぷよの枠の大きさ
	static const int Mapx = 6, Mapy = 12;

	//ぷよがどこにいるのか判定用
	Color PuyoData[Mapy][Mapx];
	//つながっていて消えるぷよをtrueに
	bool connectPuyo[Mapy][Mapx];
	bool checkPuyo[Mapy][Mapx];
	bool dousePuyo[Mapy][Mapx];
	//現在のつながりの数またフラグを示す
	int ConnectCount;
	//調べるぷよの色を見る
	Color checkPuyoColor;

	//行うフラグ
	bool douseFlag;
	bool fallFlag;
	bool NewPuyoFlag;

public:
	Map();
	~Map();
	//ぷよにデータを格納

	int GetMapx() { return Mapx; }
	int GetMapy() { return Mapy; }
	bool GetDouseFlag(){ return douseFlag; }
	bool GetFallFlag() { return fallFlag; }
	bool GetNewPuyoFlag() { return NewPuyoFlag; }
	Color GetPuyoData(int x, int y) { return PuyoData[y][x]; }
	

	//動かしていたぷよの最後の座標を格納
	void SetPuyoData(int x, int y, int num);
	//ぷよのデータを読み込み
	void StorePuyoData(Puyo* puyo);
	//つながっているか判断
	void ConnectPuyo();
	void CheckConnectPuyo(int x, int y);

	//つながっているぷよがあった時消す
	void DousePuyo();
	//連鎖に応じての落下
	void mFallPuyo();

	//初期化//リセット用
	void Release();
};
