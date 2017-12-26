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
		//ぷよの色
		int PuyoLeftColor;
		int PuyoRightColor;
		//ぷよの座標
		int PuyoLeftx;
		int PuyoLefty;
		int PuyoRightx;
		int PuyoRighty;
	};
	//横移動
	void SideMovePuyo(int w, Map* map);
	//回転
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
	//新しいぷよを待機しているデータから呼び出し
	//また待機データを新たに作成
	void NewPuyoData();
	//最初に出すぷよのデータを設定
	void Release();
};
