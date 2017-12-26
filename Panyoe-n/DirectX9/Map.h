#pragma once
#include<vector>
#include<list>
#include<algorithm>

class Puyo;

class Map
{
public:
	//ぷよの色を列挙で設定
	enum Color {RED, GREEN, BLUE, YELLOW, PURPLE , NON=999	};
	Color color;


	struct ConnectNum
	{
		//つながりの数
		int Connect;
	};
	std::vector<ConnectNum> ConnectData[5];
	ConnectNum ConnectCheck;

	std::list<int> douseData;

	//色のチェック用
	int ColorNum;
	int PuyocheakX;
	int PuyocheakY;

private:
	//ぷよの枠の大きさ
	static const int Mapx = 6, Mapy = 12;

	//ぷよがどこにいるのか判定用
	Color PuyoData[Mapy][Mapx];
	ConnectNum *pConnectNum;
	//ぷよの現在の関連状態を保存

	//つながっていて消えるぷよをtrueに

	//調べるぷよの色を見る
	Color checkPuyoColor;

	//各グループを調べるために必要な変数
	//グループの群指定をする変数
	int groupCount;
	//最小の値を調べるために必要
	int miniNum;
	//ラスタスキャンするように配列作成
	int RasutaData[Mapy][Mapx];
	//複数のラベルを確認しました　最小の数値を返します
	bool SufferLabel;

	//行うフラグ
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
	//ぷよにデータを格納

	int GetMapx() { return Mapx; }
	int GetMapy() { return Mapy; }
	bool GetOverFlag() { return overFlag; }
	bool GetDouseFlag(){ return douseFlag; }
	bool GetFallFlag() { return fallFlag; }
	bool GetNewPuyoFlag() { return NewPuyoFlag; }
	bool GetCheakFlag() { return cheakflag; }
	Color GetPuyoData(int x, int y) { return PuyoData[y][x]; }


	//動かしていたぷよの最後の座標を格納
	void SetPuyoData(int x, int y, int num);
	//ぷよのデータを読み込み
	void StorePuyoData(Puyo* puyo);

	void CheckConnectPuyo(Puyo* puyo);
	//ぷよの関連データを再度チェックする
	void RastaPuyoData(Puyo* puyo);

	//つながっているぷよがあった時消す
	void DousePuyo(Puyo* puyo);
	//連鎖に応じての落下
	void mFallPuyo();

	//初期化//リセット用
	void Release();
};
