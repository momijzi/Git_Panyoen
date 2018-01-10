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

	
	if ((contactPuyoLeft != contactPuyoRight ))
	{
		//どちら片方が何かにぶつかった
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
	}
	else if((CurrentSpeed == SPEED || EnterFlag) && !contactPuyoLeft && !contactPuyoRight)
	{
		//次段へ落下
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
		EnterFlag = false;
	}
	
	if (contactPuyoLeft && contactPuyoRight )
	{
		//ぷよが落ち切ったので他のデータと関連付け
		if (SetFlag != true)
		{
			SetPuyoFlag(true);
			SetFlag = true;
			Puyo::PuyoColor pData =
				puyo->GetPuyoInfo(1);

			//ぷよをメインのデータに適応
			map->SetPuyoData(pData.PuyoLeftx, pData.PuyoLefty, pData.PuyoLeftColor);
			map->SetPuyoData(pData.PuyoRightx, pData.PuyoRighty, pData.PuyoRightColor);
		}
		if (CurrentSpeed == SPEED)
		{
			if (!map->GetFallFlag())
			{
				//繋がっている要素を確認する
				map->RastaPuyoData(puyo);
			}

			if (map->GetDouseFlag())
			{
				SetPuyoFlag(false);
				//つながっている箇所を検出したので消す
				map->DousePuyo(puyo);
			}
			else if (map->GetFallFlag())
			{
				//上で消されて落下するぷよを落下させる
				map->mFallPuyo();
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
			}
			CurrentSpeed = 0;
		}
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
	PuyoFlag = false;
}

