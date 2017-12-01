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
	bool connectPuyo[Mapy][Mapx];
	//周りを見る用の配列
	int AroundData[2]{ -1,1 };
	

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
