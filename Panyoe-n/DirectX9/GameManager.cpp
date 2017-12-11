#include"GameManager.h"
#include"Puyo.h"
#include"Map.h"

GameManager::GameManager()
{
	SPEED = 60;//約1秒
	CurrentSpeed = 0;
	contactPuyoLeft = false;
	contactPuyoRight = false;
	EnterFlag = false;
	SetFlag = false;
}
GameManager:: ~GameManager()
{

}

GameManager gMane;

void GameManager::MovePuyo(Puyo* puyo, Map* map, GameManager* gMane)
{
	CurrentSpeed++;

	if (contactPuyoLeft == true && contactPuyoRight == true)
	{
		if (SetFlag != true)
		{
			map->StorePuyoData(puyo);
			SetFlag = true;
		}
		map->ConnectPuyo();
		if (map->GetDouseFlag())
		{
			map->DousePuyo();
		}
		else if (map->GetFallFlag())
		{
			map->mFallPuyo();
		}
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
	else if (CurrentSpeed == SPEED && (contactPuyoLeft == true || contactPuyoRight == true))
	{
		//どちら片方が何かにぶつかった
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
	}
	else if(CurrentSpeed == SPEED || EnterFlag == true)
	{
		//次段へ落下
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
	}
	EnterFlag = false;
}


