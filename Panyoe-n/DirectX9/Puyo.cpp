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


void Puyo::SideMovePuyo(int w ,Map* map)
{ 
	//移動先が枠外なら行けない
	if ( 0 <= PuyoData[1].PuyoLeftx + w && PuyoData[1].PuyoLeftx + w < map->GetMapx() &&
		0 <= PuyoData[1].PuyoRightx + w && PuyoData[1].PuyoRightx + w < map->GetMapx() &&
		map->GetPuyoData(PuyoData[1].PuyoLeftx + w,PuyoData[1].PuyoLefty) == map->NON &&
		map->GetPuyoData(PuyoData[1].PuyoRightx + w, PuyoData[1].PuyoRighty)== map->NON)
	{
		//移動
		PuyoData[1].PuyoLeftx = PuyoData[1].PuyoLeftx + w;
		PuyoData[1].PuyoRightx = PuyoData[1].PuyoRightx + w;
	}
}

void Puyo::RotaPuyo(int wh ,Map* map, GameManager* gMane)
{
	//初期の状態
	if (PuyoData[1].PuyoLeftx < PuyoData[1].PuyoRightx && PuyoData[1].PuyoLefty == PuyoData[1].PuyoRighty)
	{
		//入る値により上下行けるかを見る
		if (map->GetPuyoData(PuyoData[1].PuyoLeftx, PuyoData[1].PuyoLefty - wh) == map->NON &&
			map->GetPuyoData(PuyoData[1].PuyoLeftx + 1, PuyoData[1].PuyoLefty - wh) == map->NON &&
			PuyoData[1].PuyoLefty < map->GetMapy() - 1)
		{
			PuyoData[1].PuyoLeftx = PuyoData[1].PuyoLeftx + 1;
			PuyoData[1].PuyoLefty = PuyoData[1].PuyoLefty - wh;
		}
	}
	//初期左にあったものが右にある時
	else if (PuyoData[1].PuyoLeftx > PuyoData[1].PuyoRightx && PuyoData[1].PuyoLefty == PuyoData[1].PuyoRighty)
	{
		if (map->GetPuyoData(PuyoData[1].PuyoLeftx, PuyoData[1].PuyoLefty + wh) == map->NON &&
			map->GetPuyoData(PuyoData[1].PuyoLeftx - 1, PuyoData[1].PuyoLefty + wh) == map->NON &&
			PuyoData[1].PuyoLefty < map->GetMapy() - 1)
		{
			PuyoData[1].PuyoLeftx = PuyoData[1].PuyoLeftx - 1;
			PuyoData[1].PuyoLefty = PuyoData[1].PuyoLefty + wh;
		}
	}
	//初期左にあったものが下にある時
	else if (PuyoData[1].PuyoLeftx == PuyoData[1].PuyoRightx && PuyoData[1].PuyoLefty > PuyoData[1].PuyoRighty)
	{
		//移動先が枠外ではないかを判断
		if (0 < PuyoData[1].PuyoLeftx + (wh * -1) && PuyoData[1].PuyoLeftx + (wh * -1) < map->GetMapx() &&
			map->GetPuyoData(PuyoData[1].PuyoLeftx - wh, PuyoData[1].PuyoLefty - 1) == map->NON &&
			map->GetPuyoData(PuyoData[1].PuyoLeftx - wh, PuyoData[1].PuyoLefty) == map->NON)
		{
			PuyoData[1].PuyoLeftx = PuyoData[1].PuyoLeftx + (wh * -1);
			PuyoData[1].PuyoLefty = PuyoData[1].PuyoLefty - 1;
		}
	}
	//初期左にあったものが上にある時
	else if (PuyoData[1].PuyoLeftx == PuyoData[1].PuyoRightx && PuyoData[1].PuyoLefty < PuyoData[1].PuyoRighty)
	{
		if (0 < PuyoData[1].PuyoLeftx + wh && PuyoData[1].PuyoLeftx + wh < map->GetMapx() &&
			map->GetPuyoData(PuyoData[1].PuyoLeftx + wh, PuyoData[1].PuyoLefty + 1) == map->NON &&
			map->GetPuyoData(PuyoData[1].PuyoLeftx + wh, PuyoData[1].PuyoLefty) == map->NON)
		{
			PuyoData[1].PuyoLeftx = PuyoData[1].PuyoLeftx + wh;
			PuyoData[1].PuyoLefty = PuyoData[1].PuyoLefty + 1;
		}
	}
}

void Puyo::FallPuyo(Map* map,GameManager* gMane)
{
	//ぷよが何かに当たったもしくは下にたどり着いた
	if (PuyoData[1].PuyoLefty == map->GetMapy() - 1 || PuyoData[1].PuyoRighty == map->GetMapy() - 1)
	{
		//次のぷよ投下処理
		gMane->SetContactPuyoLeft(true);
		gMane->SetContactPuyoRight(true);
	}
	//片方がまだ当たっていない
	else if ((map->GetPuyoData(PuyoData[1].PuyoLeftx, PuyoData[1].PuyoLefty + 1) != map->NON ||
		map->GetPuyoData(PuyoData[1].PuyoRightx, PuyoData[1].PuyoRighty + 1) != map->NON))
	{
		//当たった側の上に存在するため動けなくする
		if (PuyoData[1].PuyoLeftx != PuyoData[1].PuyoRightx)
		{
			if (gMane->GetContactPuyoLeft() != true)
			{
				//片方のみ当たった場合	//左のみ落下
				if (map->GetPuyoData(PuyoData[1].PuyoLeftx, PuyoData[1].PuyoLefty + 1) == map->NON)
				{
					PuyoData[1].PuyoLefty = PuyoData[1].PuyoLefty + 1;
				}
				else
				{
					//当たっているもしくは下にたどり着いた
					gMane->SetContactPuyoLeft(true);
				}
			}
			
			//右のみ落下
			if (gMane->GetContactPuyoRight() != true)
			{
				if (map->GetPuyoData(PuyoData[1].PuyoRightx, PuyoData[1].PuyoRighty + 1) == map->NON)
				{
					PuyoData[1].PuyoRighty = PuyoData[1].PuyoRighty + 1;
				}
				else
				{
					//当たっているもしくは下にたどり着いた
					gMane->SetContactPuyoRight(true);
				}
			}
		}
		else//縦に重なっている場合
		{
			//次のぷよ投下処理
			gMane->SetContactPuyoLeft(true);
			gMane->SetContactPuyoRight(true);
		}
	}
	else
	{		
		PuyoData[1].PuyoLefty = PuyoData[1].PuyoLefty + 1;
		PuyoData[1].PuyoRighty = PuyoData[1].PuyoRighty + 1;
	}
}

void Puyo::NewPuyoData()
{
	//待機していたぷよのデータを格納
	PuyoData[1] = PuyoData[0];
	//最初の初期位置を設定
	PuyoData[1].PuyoLeftx = 2;
	PuyoData[1].PuyoRightx = 3;
	//新しい色を取得（待機データ）
	PuyoData[0].PuyoLeftColor = rand() % MaxPuyoColor;
	PuyoData[0].PuyoRightColor = rand() % MaxPuyoColor;
}

void Puyo::Release()
{
	//出るデータも待ちデータも初期化
	for (int i = 0; i < 2; i++)
	{
		//色をランダムに取る
		PuyoData[i].PuyoLeftColor = rand() % MaxPuyoColor;
		PuyoData[i].PuyoRightColor = rand() % MaxPuyoColor;
		if (i != 0)
		{
			//最初に出るデータの座標を格納
			PuyoData[i].PuyoLeftx = 2;
			PuyoData[i].PuyoLefty = 0;
			PuyoData[i].PuyoRightx = 3;
			PuyoData[i].PuyoRighty = 0;
		}
		else
		{
			//待機データを格納
			PuyoData[i].PuyoLeftx = 0;
			PuyoData[i].PuyoLefty = 0;
			PuyoData[i].PuyoRightx = 0;
			PuyoData[i].PuyoRighty = 0;
		}
	}
}