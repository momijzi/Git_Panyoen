#include"GameManager.h"
#include"Puyo.h"
#include"Map.h"

GameManager::GameManager()
{
	Release();
}
GameManager:: ~GameManager()
{

}

GameManager gMane;

void GameManager::MovePuyo(Puyo* puyo, Map* map, GameManager* gMane)
{
	CurrentSpeed++;

	if (contactPuyoLeft && contactPuyoRight)
	{
		//ぷよが落ち切ったので他のデータと関連付け
		if (SetFlag != true)
		{
			SetFlag = true;
			//つながっているかどうかの判断
			map->CheckConnectPuyo(puyo);
		}

		if (map->GetDouseFlag() && !map->GetFallFlag())
		{
			//繋がっている要素を確認する
			map->RastaPuyoData(puyo);
			//つながっている箇所を検出したので消す
			map->DousePuyo(puyo);
		}
		else if(map->GetFallFlag())
		{
			//上で消されて落下するぷよを落下させる
			map->mFallPuyo();
		}
		else if (map->GetCheakFlag())
		{
			map->RastaPuyoData(puyo);
		}
		//つながっている箇所を確認できなかった
		//次のぷよを生成
		else
		{
			//両方が何かにぶつかった
			puyo->NewPuyoData();
			contactPuyoLeft = false;
			contactPuyoRight = false;
			SetFlag = false;
			CurrentSpeed = 0;
		}
	}
	else if ((contactPuyoLeft || contactPuyoRight ))
	{
		//どちら片方が何かにぶつかった
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
	}
	else if(CurrentSpeed == SPEED || EnterFlag)
	{
		//次段へ落下
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
		EnterFlag = false;
	}
}

void GameManager::Release()
{
	SPEED = 60;//約1秒
	CurrentSpeed = 0;
	contactPuyoLeft = false;
	contactPuyoRight = false;
	EnterFlag = false;
	SetFlag = false;
}

