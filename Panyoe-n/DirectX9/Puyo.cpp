#include"Puyo.h"
#include"time.h"
#include"windows.h"
#include"GameManager.h"
#include"Map.h"

Puyo::Puyo()
{
	MaxPuyoColor = 0;

}
Puyo::~Puyo()
{

}

Map map;


void Puyo::SideMovePuyo(int w)
{ 
	//移動先が枠外なら行けない
	if ( 0 < pPuyoColor[1].PuyoLeftx + w && pPuyoColor[1].PuyoRightx + w < map.GetMapx())
	{
		//移動
		pPuyoColor[1].PuyoLeftx = pPuyoColor[1].PuyoLeftx + w;
		pPuyoColor[1].PuyoRightx = pPuyoColor[1].PuyoRightx + w;
	}
}

void Puyo::RotaPuyo(int wh)
{
	//初期の状態
	if (pPuyoColor[1].PuyoLeftx < pPuyoColor[1].PuyoRightx && pPuyoColor[1].PuyoLefty == pPuyoColor[1].PuyoRighty)
	{
			
			pPuyoColor[1].PuyoLeftx = pPuyoColor[1].PuyoLeftx + wh;
			pPuyoColor[1].PuyoLefty = pPuyoColor[1].PuyoLefty + wh;
	}
	//初期左にあったものが右にある時
	else if (pPuyoColor[1].PuyoLeftx > pPuyoColor[1].PuyoRightx && pPuyoColor[1].PuyoLefty == pPuyoColor[1].PuyoRighty)
	{
		pPuyoColor[1].PuyoLeftx = pPuyoColor[1].PuyoLeftx - wh;
		pPuyoColor[1].PuyoLefty = pPuyoColor[1].PuyoLefty - wh;
	}
	//初期左にあったものが上にある時
	else if (pPuyoColor[1].PuyoLeftx == pPuyoColor[1].PuyoRightx && pPuyoColor[1].PuyoLefty > pPuyoColor[1].PuyoRighty)
	{
		//移動先が枠外ではないかを判断
		if (0 < pPuyoColor[1].PuyoLeftx + wh && pPuyoColor[1].PuyoLeftx + wh < map.GetMapx())
		{
			pPuyoColor[1].PuyoLeftx = pPuyoColor[1].PuyoLeftx + wh;
			pPuyoColor[1].PuyoLefty = pPuyoColor[1].PuyoLefty - wh;
		}
	}
	//初期左にあったものが下にある時
	else if (pPuyoColor[1].PuyoLeftx == pPuyoColor[1].PuyoRightx && pPuyoColor[1].PuyoLefty > pPuyoColor[1].PuyoRighty)
	{
		if (0 < pPuyoColor[1].PuyoLeftx + wh && pPuyoColor[1].PuyoLeftx + wh < map.GetMapx())
		{
			//移動先が枠外ではないかを判断
			pPuyoColor[1].PuyoLeftx = pPuyoColor[1].PuyoLeftx - wh;
			pPuyoColor[1].PuyoLefty = pPuyoColor[1].PuyoLefty + wh;
		}
	}
}

void Puyo::FallPuyo(GameManager* gMane)
{
	//ぷよが何かに当たったもしくは下にたどり着いた
	if (pPuyoColor[1].PuyoLefty + 1 == map.GetMapy() || pPuyoColor[1].PuyoRighty + 1 == map.GetMapy())
	{
		//次のぷよ投下処理
		gMane->SetContactPuyoLeft(true);
		gMane->SetContactPuyoRight(true);
	}
	else if ((map.GetPuyoData(pPuyoColor[1].PuyoLeftx, pPuyoColor[1].PuyoLefty + 1) != map.NON ||
		map.GetPuyoData(pPuyoColor[1].PuyoRightx, pPuyoColor[1].PuyoRighty + 1) != map.NON) &&
		pPuyoColor[1].PuyoLeftx != pPuyoColor[1].PuyoRightx)
	{
		//片方のみ当たった場合
		//左のみ落下
		if (map.GetPuyoData(pPuyoColor[1].PuyoLeftx, pPuyoColor[1].PuyoLefty + 1) == map.NON)
		{
			pPuyoColor[1].PuyoLefty = pPuyoColor[1].PuyoLefty + 1;
		}
		else
		{
			//当たっているもしくは下にたどり着いた
			gMane->SetContactPuyoLeft(true);
		}
		//右のみ落下
		if (map.GetPuyoData(pPuyoColor[1].PuyoRightx, pPuyoColor[1].PuyoRighty + 1) == map.NON)
		{
			pPuyoColor[1].PuyoRighty = pPuyoColor[1].PuyoRighty + 1;
		}
		else
		{
			//当たっているもしくは下にたどり着いた
			gMane->SetContactPuyoRight(true);
		}
	}
	else
	{
		pPuyoColor[1].PuyoLefty = pPuyoColor[1].PuyoLefty + 1;
		pPuyoColor[1].PuyoRighty = pPuyoColor[1].PuyoRighty + 1;
	}
}

void Puyo::NewPuyoData()
{
	//待機していたぷよのデータを格納
	pPuyoColor[1] = pPuyoColor[0];
	//最初の初期位置を設定
	pPuyoColor[1].PuyoLeftx = 3;
	pPuyoColor[1].PuyoLefty = 4;
	//新しい色を取得（待機データ）
	pPuyoColor[0].PuyoLeftColor = rand() % MaxPuyoColor;
	pPuyoColor[0].PuyoRightColor = rand() % MaxPuyoColor;
}

void Puyo::Release()
{
	//出るデータも待ちデータも初期化
	for (int i = 0; i < 2; i++)
	{
		//色をランダムに取る
		pPuyoColor[i].PuyoLeftColor = rand() % MaxPuyoColor;
		pPuyoColor[i].PuyoRightColor = rand() % MaxPuyoColor;
		if (i != 0)
		{
			//最初に出るデータの座標を格納
			pPuyoColor[i].PuyoLeftx = 3;
			pPuyoColor[i].PuyoLefty = 0;
			pPuyoColor[i].PuyoRightx = 4;
			pPuyoColor[i].PuyoRighty = 0;
		}
		else
		{
			//待機データを格納
			pPuyoColor[i].PuyoLeftx = 0;
			pPuyoColor[i].PuyoLefty = 0;
			pPuyoColor[i].PuyoRightx = 0;
			pPuyoColor[i].PuyoRighty = 0;
		}
	}
}